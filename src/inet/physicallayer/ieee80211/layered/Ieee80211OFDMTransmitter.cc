//
// Copyright (C) 2014 OpenSim Ltd.
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program; if not, see <http://www.gnu.org/licenses/>.
//

#include "inet/mobility/contract/IMobility.h"
#include "inet/physicallayer/ieee80211/layered/Ieee80211OFDMTransmitter.h"
#include "inet/physicallayer/common/layered/SignalPacketModel.h"
#include "inet/physicallayer/ieee80211/layered/Ieee80211OFDMPLCPFrame_m.h"
#include "inet/physicallayer/contract/layered/ISignalAnalogModel.h"
#include "inet/physicallayer/analogmodel/layered/ScalarSignalAnalogModel.h"
#include "inet/physicallayer/ieee80211/Ieee80211OFDMModulation.h"
#include "inet/physicallayer/ieee80211/Ieee80211OFDMCode.h"
#include "inet/physicallayer/ieee80211/layered/Ieee80211ConvolutionalCode.h"
#include "inet/physicallayer/ieee80211/layered/Ieee80211OFDMEncoder.h"
#include "inet/physicallayer/ieee80211/layered/Ieee80211OFDMEncoderModule.h"
#include "inet/physicallayer/ieee80211/layered/Ieee80211OFDMModulator.h"
#include "inet/common/serializer/headerserializers/ieee80211/Ieee80211Serializer.h"
#include "inet/physicallayer/common/layered/LayeredTransmission.h"
#include "inet/common/serializer/headerserializers/ieee80211/Ieee80211PhySerializer.h"
#include "inet/physicallayer/ieee80211/layered/Ieee80211OFDMDefs.h"
#include "inet/physicallayer/ieee80211/layered/Ieee80211TimingRelatedParameters.h"
#include "inet/physicallayer/ieee80211/layered/Ieee80211OFDMSymbolModel.h"

namespace inet {

namespace physicallayer {

Define_Module(Ieee80211OFDMTransmitter);

using namespace serializer;

void Ieee80211OFDMTransmitter::initialize(int stage)
{
    if (stage == INITSTAGE_LOCAL)
    {
        isCompliant = par("isCompliant").boolValue();
        encoder = dynamic_cast<const IEncoder *>(getSubmodule("encoder"));
        signalEncoder = dynamic_cast<const IEncoder *>(getSubmodule("signalEncoder"));
        modulator = dynamic_cast<const IModulator *>(getSubmodule("modulator"));
        signalModulator = dynamic_cast<const IModulator *>(getSubmodule("signalModulator"));
        pulseShaper = dynamic_cast<const IPulseShaper *>(getSubmodule("pulseShaper"));
        digitalAnalogConverter = dynamic_cast<const IDigitalAnalogConverter *>(getSubmodule("digitalAnalogConverter"));
        channelSpacing = Hz(par("channelSpacing"));
        if (isCompliant && (encoder || signalEncoder || modulator || signalModulator
                            || pulseShaper || digitalAnalogConverter || !isNaN(channelSpacing.get()))) // TODO: check modulations
        {
            throw cRuntimeError("In compliant mode it is forbidden to set any kind of parameters.");
        }
        if (!isCompliant)
        {
            signalModulation = APSKModulationBase::findModulation(par("signalModulation"));
            dataModulation = APSKModulationBase::findModulation(par("dataModulation"));
        }
        power = W(par("power"));
        bandwidth = Hz(par("bandwidth"));
        carrierFrequency = Hz(par("carrierFrequency"));
        const char *levelOfDetailStr = par("levelOfDetail").stringValue();
        if (strcmp("bit", levelOfDetailStr) == 0)
            levelOfDetail = BIT_DOMAIN;
        else if (strcmp("symbol", levelOfDetailStr) == 0)
            levelOfDetail = SYMBOL_DOMAIN;
        else if (strcmp("sample", levelOfDetailStr) == 0)
            levelOfDetail = SAMPLE_DOMAIN;
        else if (strcmp("packet", levelOfDetailStr) == 0)
            levelOfDetail = PACKET_DOMAIN;
        else
            throw cRuntimeError("Unknown level of detail='%s'", levelOfDetailStr);
    }
}

BitVector *Ieee80211OFDMTransmitter::serialize(const cPacket* packet) const
{
    Ieee80211PhySerializer phySerializer;
    BitVector *serializedPacket = new BitVector();
    const Ieee80211OFDMPLCPFrame *phyFrame = check_and_cast<const Ieee80211OFDMPLCPFrame*>(packet);
    phySerializer.serialize(phyFrame, serializedPacket);
    unsigned int byteLength = phyFrame->getLength();
    unsigned int rate = phyFrame->getRate();
    int dataBitsLength = 6 + byteLength * 8 + 16;
    padding(serializedPacket, dataBitsLength, rate);
    return serializedPacket;
}

const ITransmissionPacketModel* Ieee80211OFDMTransmitter::createPacketModel(const cPacket* macFrame) const
{
    int rate = 0; // in non-compliant mode rate is 0.
    if (isCompliant)
    {
        Ieee80211OFDMModulation ofdmModulation(netDataBitrate, channelSpacing);
        rate = ofdmModulation.getSignalRateField();
    }
    // The PLCP header is composed of RATE (4), Reserved (1), LENGTH (12), Parity (1),
    // Tail (6) and SERVICE (16) fields.
    int plcpHeaderLength = 4 + 1 + 12 + 1 + 6 + 16;
    Ieee80211OFDMPLCPFrame * phyFrame = new Ieee80211OFDMPLCPFrame();
    phyFrame->setRate(rate);
    phyFrame->setLength(macFrame->getByteLength());
    phyFrame->encapsulate(const_cast<cPacket *>(macFrame));
    phyFrame->setBitLength(phyFrame->getLength()*8 + plcpHeaderLength);
    BitVector *serializedPacket = serialize(phyFrame);
    return new TransmissionPacketModel(phyFrame, serializedPacket, netDataBitrate);
}

const ITransmissionAnalogModel* Ieee80211OFDMTransmitter::createScalarAnalogModel(const ITransmissionPacketModel *packetModel, const ITransmissionBitModel *bitModel) const
{
    int headerBitLength = -1;
    int dataBitLength = -1;
    if (levelOfDetail > PACKET_DOMAIN)
    {
        headerBitLength = bitModel->getHeaderBitLength();
        dataBitLength = bitModel->getPayloadBitLength();
    }
    else
    {
        if (isCompliant)
        {
            uint8_t rate = getRate(packetModel->getSerializedPacket());
            const Ieee80211OFDMCode *code = new Ieee80211OFDMCode(rate, channelSpacing);
            const ConvolutionalCode *convCode = code->getConvCode();
            headerBitLength = ENCODED_SIGNAL_FIELD_LENGTH;
            dataBitLength = convCode->getEncodedLength((packetModel->getSerializedPacket()->getSize() - DECODED_SIGNAL_FIELD_LENGTH));
            delete code;
        }
        else
        {
            throw cRuntimeError("Unimplemented");
        }
    }
    Ieee80211TimingRelatedParameters timing(channelSpacing);
    simtime_t preambleDuration = timing.getPreambleDuration();
    simtime_t headerDuration = 0;
    if (!isCompliant)
    {
        unsigned int headerCodeWordSize = signalModulation->getCodeWordSize();
        ASSERT(headerBitLength % headerCodeWordSize == 0);
        unsigned int numberOfSignalAPSKSymbols = headerBitLength / headerCodeWordSize;
        unsigned int numberOfSignalOFDMSymbols = numberOfSignalAPSKSymbols / NUMBER_OF_OFDM_DATA_SUBCARRIERS;
        headerDuration = numberOfSignalOFDMSymbols * timing.getSymbolInterval();
    }
    else
        headerDuration = timing.getSignalDuration();
    unsigned int dataCodeWordSize = dataModulation->getCodeWordSize();
    ASSERT(dataBitLength % dataCodeWordSize == 0);
    unsigned int numberOfDataAPSKSymbols = dataBitLength / dataCodeWordSize;
    unsigned int numberOfDataOFDMSymbols = numberOfDataAPSKSymbols / NUMBER_OF_OFDM_DATA_SUBCARRIERS;
    simtime_t dataDuration = numberOfDataOFDMSymbols * timing.getSymbolInterval();
    simtime_t duration = preambleDuration + headerDuration + dataDuration;
    return new ScalarTransmissionSignalAnalogModel(duration, carrierFrequency, bandwidth, power);
}

// TODO: copy
uint8_t Ieee80211OFDMTransmitter::getRate(const BitVector* serializedPacket) const
{
    ShortBitVector rate;
    for (unsigned int i = 0; i < 4; i++)
        rate.appendBit(serializedPacket->getBit(i));
    return rate.toDecimal();
}

const ITransmissionPacketModel* Ieee80211OFDMTransmitter::createSignalFieldPacketModel(const ITransmissionPacketModel* completePacketModel) const
{
    // The SIGNAL field is composed of RATE (4), Reserved (1), LENGTH (12), Parity (1), Tail (6),
    // fields, so the SIGNAL field is 24 bits (OFDM_SYMBOL_SIZE / 2) long.
    BitVector *signalField = new BitVector();
    const BitVector *serializedPacket = completePacketModel->getSerializedPacket();
    for (unsigned int i = 0; i < NUMBER_OF_OFDM_DATA_SUBCARRIERS / 2; i++)
        signalField->appendBit(serializedPacket->getBit(i));
    return new TransmissionPacketModel(nullptr, signalField, bps(NaN));
}

const ITransmissionPacketModel* Ieee80211OFDMTransmitter::createDataFieldPacketModel(const ITransmissionPacketModel* completePacketModel) const
{
    BitVector *dataField = new BitVector();
    const BitVector *serializedPacket = completePacketModel->getSerializedPacket();
    for (unsigned int i = NUMBER_OF_OFDM_DATA_SUBCARRIERS / 2; i < serializedPacket->getSize(); i++)
        dataField->appendBit(serializedPacket->getBit(i));
    return new TransmissionPacketModel(nullptr, dataField, bps(NaN));
}

void Ieee80211OFDMTransmitter::encodeAndModulate(const ITransmissionPacketModel* packetModel, const ITransmissionBitModel *&fieldBitModel, const ITransmissionSymbolModel *&fieldSymbolModel, const IEncoder *encoder, const IModulator *modulator, bool isSignalField) const
{
    uint8_t rate = getRate(packetModel->getSerializedPacket());
    const ITransmissionPacketModel *fieldPacketModel = nullptr;
    if (isSignalField)
        fieldPacketModel = createSignalFieldPacketModel(packetModel);
    else
        fieldPacketModel = createDataFieldPacketModel(packetModel);
    if (levelOfDetail >= BIT_DOMAIN)
    {
        if (fieldPacketModel)
        {
            if (encoder) // non-compliant mode
                fieldBitModel = encoder->encode(fieldPacketModel);
            else // compliant mode
            {
                const Ieee80211OFDMCode *code = nullptr;
                if (isSignalField)
                    code = new Ieee80211OFDMCode(channelSpacing);
                else // data
                    code = new Ieee80211OFDMCode(rate, channelSpacing);
                const Ieee80211OFDMEncoder encoder(code);
                if (isSignalField)
                    grossHeaderBitrate = convertToNetBitrateToGrossBitrate(netHeaderBitrate, &encoder);
                else
                    grossDataBitrate = convertToNetBitrateToGrossBitrate(netDataBitrate, &encoder);
                fieldBitModel = encoder.encode(fieldPacketModel);
            }
        }
        else
            throw cRuntimeError("Encoder needs packet representation");
    }
    if (levelOfDetail >= SYMBOL_DOMAIN)
    {
        if (fieldBitModel)
        {
            if (modulator) // non-compliant mode
                fieldSymbolModel = modulator->modulate(fieldBitModel);
            else // compliant mode
            {
                const Ieee80211OFDMModulation *ofdmModulation;
                if (isSignalField)
                    ofdmModulation = new Ieee80211OFDMModulation(channelSpacing);
                else // data
                    ofdmModulation = new Ieee80211OFDMModulation(rate, channelSpacing);
                Ieee80211OFDMModulator modulator(ofdmModulation);
                fieldSymbolModel = modulator.modulate(fieldBitModel);
            }
        }
        else
            throw cRuntimeError("Modulator needs bit representation");
    }
    delete fieldPacketModel;
}

const ITransmissionSymbolModel* Ieee80211OFDMTransmitter::createSymbolModel(const ITransmissionSymbolModel* signalFieldSymbolModel, const ITransmissionSymbolModel* dataFieldSymbolModel) const
{
    if (levelOfDetail >= SYMBOL_DOMAIN)
    {
        const std::vector<const ISymbol *> *signalSymbols = signalFieldSymbolModel->getSymbols();
        std::vector<const ISymbol *> *mergedSymbols = new std::vector<const ISymbol *>();
        const Ieee80211OFDMSymbol *ofdmSymbol = nullptr;
        for (unsigned int i = 0; i < signalSymbols->size(); i++)
        {
            ofdmSymbol = dynamic_cast<const Ieee80211OFDMSymbol *>(signalSymbols->at(i));
            mergedSymbols->push_back(new Ieee80211OFDMSymbol(*ofdmSymbol));
        }
        const std::vector<const ISymbol *> *dataSymbols = dataFieldSymbolModel->getSymbols();
        for (unsigned int i = 0; i < dataSymbols->size(); i++)
        {
            ofdmSymbol = dynamic_cast<const Ieee80211OFDMSymbol *>(dataSymbols->at(i));
            mergedSymbols->push_back(new Ieee80211OFDMSymbol(*ofdmSymbol));
        }
        Ieee80211TimingRelatedParameters timing(channelSpacing);
        const Ieee80211OFDMTransmissionSymbolModel *transmissionSymbolModel = new Ieee80211OFDMTransmissionSymbolModel(1, 1.0 / timing.getSignalDuration(), mergedSymbols->size() - 1, 1.0 / timing.getSymbolInterval(), mergedSymbols, signalFieldSymbolModel->getHeaderModulation(), dataFieldSymbolModel->getPayloadModulation());
        delete signalFieldSymbolModel;
        delete dataFieldSymbolModel;
        return transmissionSymbolModel;
    }
    return new Ieee80211OFDMTransmissionSymbolModel(-1, NaN, -1, NaN, nullptr, signalModulation, dataModulation);
}

const ITransmissionBitModel* Ieee80211OFDMTransmitter::createBitModel(const ITransmissionBitModel* signalFieldBitModel, const ITransmissionBitModel* dataFieldBitModel, const ITransmissionPacketModel *packetModel) const
{
    if (levelOfDetail >= BIT_DOMAIN)
    {
        BitVector *encodedBits = new BitVector(*signalFieldBitModel->getBits());
        unsigned int signalBitLength = signalFieldBitModel->getBits()->getSize();
        const BitVector *dataFieldBits = dataFieldBitModel->getBits();
        unsigned int dataBitLength = dataFieldBits->getSize();
        for (unsigned int i = 0; i < dataFieldBits->getSize(); i++)
            encodedBits->appendBit(dataFieldBits->getBit(i));
        const TransmissionBitModel *transmissionBitModel = new TransmissionBitModel(signalBitLength, grossHeaderBitrate, dataBitLength, grossDataBitrate, encodedBits, dataFieldBitModel->getForwardErrorCorrection(), dataFieldBitModel->getScrambling(), dataFieldBitModel->getInterleaving());
        delete signalFieldBitModel;
        delete dataFieldBitModel;
        return transmissionBitModel;
    }
    return new TransmissionBitModel(-1, grossHeaderBitrate, -1, grossDataBitrate, nullptr, nullptr, nullptr, nullptr);
}

void Ieee80211OFDMTransmitter::padding(BitVector* serializedPacket, unsigned int dataBitsLength, uint8_t rate) const
{
    // TODO: in non-compliant mode: header padding.
    unsigned int codedBitsPerOFDMSymbol = dataModulation->getCodeWordSize() * NUMBER_OF_OFDM_DATA_SUBCARRIERS;
    const ConvolutionalCode *fec = nullptr;
    const Ieee80211OFDMCode *code = nullptr;
    if (isCompliant)
    {
        code = new Ieee80211OFDMCode(rate, channelSpacing);
        fec = code->getConvCode();
    }
    else
    {
        ASSERT(encoder != NULL);
        const Ieee80211OFDMEncoderModule *encoderModule = check_and_cast<const Ieee80211OFDMEncoderModule *>(encoder);
        const Ieee80211OFDMCode *code = encoderModule->getCode();
        ASSERT(code != nullptr);
        fec = code->getConvCode();
    }
    unsigned int dataBitsPerOFDMSymbol = codedBitsPerOFDMSymbol;
    if (fec)
       dataBitsPerOFDMSymbol = fec->getDecodedLength(codedBitsPerOFDMSymbol);
    unsigned int appendedBitsLength = dataBitsPerOFDMSymbol - dataBitsLength % dataBitsPerOFDMSymbol;
    serializedPacket->appendBit(0, appendedBitsLength);
    delete code;
}

bps Ieee80211OFDMTransmitter::computeNonCompliantBitrate(const APSKModulationBase *modulation, double codeRate) const
{
    int codedBitsPerOFDMSymbol = modulation->getCodeWordSize() * NUMBER_OF_OFDM_DATA_SUBCARRIERS;
    double dataBitsPerOFDMSymbol = codedBitsPerOFDMSymbol * codeRate; // It need not to be an integer
    // FIXME: If channelSpacing is not 5, 10, or 20 MHz then Ieee80211TimingRelatedParameters may give wrong data.
    Ieee80211TimingRelatedParameters timing(channelSpacing);
    simtime_t symbolDuration = timing.getSymbolInterval();
    return bps(dataBitsPerOFDMSymbol / symbolDuration);
}

bps Ieee80211OFDMTransmitter::computeNonCompliantGrossBitrate(const APSKModulationBase *modulation) const
{
    return computeNonCompliantBitrate(modulation, 1);
}

bps Ieee80211OFDMTransmitter::computeNonCompliantNetBitrate(const APSKModulationBase *modulation, const IEncoder *encoder) const
{
    double codeRate = getCodeRate(encoder);
    return computeNonCompliantBitrate(modulation, codeRate);
}

const ITransmissionSampleModel* Ieee80211OFDMTransmitter::createSampleModel(const ITransmissionSymbolModel *symbolModel) const
{
    if (levelOfDetail >= SAMPLE_DOMAIN)
    {
        throw cRuntimeError("This level of detail is unimplemented.");
//        if (symbolModel)
//        {
//            if (pulseShaper) // non-compliant mode
//                sampleModel = pulseShaper->shape(symbolModel);
//            else // compliant mode
//            {
//            }
//        }
//        else
//            throw cRuntimeError("Pulse shaper needs symbol representation");
    }
    else
        return nullptr;
}

const ITransmissionAnalogModel* Ieee80211OFDMTransmitter::createAnalogModel(const ITransmissionPacketModel *packetModel, const ITransmissionBitModel* bitModel, const ITransmissionSymbolModel* symbolModel, const ITransmissionSampleModel* sampleModel) const
{
    const ITransmissionAnalogModel *analogModel = nullptr;
    if (digitalAnalogConverter)
    {
        if (!sampleModel)
            analogModel = digitalAnalogConverter->convertDigitalToAnalog(sampleModel);
        else
            throw cRuntimeError("Digital/analog converter needs sample representation");
    }
    else // TODO: Analog model is obligatory, currently we use scalar analog model as default analog model
        analogModel = createScalarAnalogModel(packetModel, bitModel);
    return analogModel;
}

void Ieee80211OFDMTransmitter::computeChannelSpacingAndBitrates(const cPacket* macFrame) const
{
    if (isCompliant)
    {
//        const RadioTransmissionRequest *controlInfo = dynamic_cast<const RadioTransmissionRequest *>(macFrame->getControlInfo());
//        TODO:
//        if (controlInfo)
//        {
//            dataBitrate = controlInfo->getBitrate();
//            channelSpacing = controlInfo->...;
//
//            computeHeaderBitrate();
//        }
//        else
//            throw cRuntimeError("");
        netDataBitrate = bps(36000000); // FIXME: Kludge
        netHeaderBitrate = bps(6000000);
        grossHeaderBitrate = netHeaderBitrate;
        grossDataBitrate = netDataBitrate;
        channelSpacing = Hz(20000000);
        Ieee80211OFDMModulation signalOFDMModulation(channelSpacing);
        Ieee80211OFDMModulation dataOFDMModulation(netDataBitrate, channelSpacing);
        signalModulation = signalOFDMModulation.getModulationScheme();
        dataModulation = dataOFDMModulation.getModulationScheme();
    }
    else // non-compliant
    {
        netDataBitrate = computeNonCompliantNetBitrate(dataModulation, encoder);
        netHeaderBitrate = computeNonCompliantNetBitrate(signalModulation, signalEncoder);
        grossDataBitrate = computeNonCompliantGrossBitrate(dataModulation);
        grossHeaderBitrate = computeNonCompliantGrossBitrate(signalModulation);
    }
}

bps Ieee80211OFDMTransmitter::convertToNetBitrateToGrossBitrate(bps netBitrate, const IEncoder* encoder) const
{
    double codeRate = getCodeRate(encoder);
    return netBitrate / codeRate;
}

double Ieee80211OFDMTransmitter::getCodeRate(const IEncoder* encoder) const
{
    const ConvolutionalCode *convCode = nullptr;
    if (encoder)
    {
        const Ieee80211OFDMEncoderModule *ofdmEncoderModule = dynamic_cast<const Ieee80211OFDMEncoderModule *>(encoder);
        if (ofdmEncoderModule)
            convCode = ofdmEncoderModule->getCode()->getConvCode();
        else
        {
            const Ieee80211OFDMEncoder *ofdmEncoder = dynamic_cast<const Ieee80211OFDMEncoder *>(encoder);
            convCode = ofdmEncoder->getCode()->getConvCode();
        }
    }
    double codeRate = 1;
    if (convCode)
        codeRate = 1.0 * convCode->getCodeRatePuncturingK() / convCode->getCodeRatePuncturingN();
    return codeRate;
}

const ITransmission *Ieee80211OFDMTransmitter::createTransmission(const IRadio *transmitter, const cPacket *macFrame, const simtime_t startTime) const
{
    const ITransmissionBitModel *bitModel = nullptr;
    const ITransmissionBitModel *signalFieldBitModel = nullptr;
    const ITransmissionBitModel *dataFieldBitModel = nullptr;
    const ITransmissionSymbolModel *symbolModel = nullptr;
    const ITransmissionSymbolModel *signalFieldSymbolModel = nullptr;
    const ITransmissionSymbolModel *dataFieldSymbolModel = nullptr;
    const ITransmissionSampleModel *sampleModel = nullptr;
    const ITransmissionAnalogModel *analogModel = nullptr;
    computeChannelSpacingAndBitrates(macFrame);
    const ITransmissionPacketModel *packetModel = createPacketModel(macFrame);
    encodeAndModulate(packetModel, signalFieldBitModel, signalFieldSymbolModel, signalEncoder, signalModulator, true);
    encodeAndModulate(packetModel, dataFieldBitModel, dataFieldSymbolModel, encoder, modulator, false);
    bitModel = createBitModel(signalFieldBitModel, dataFieldBitModel, packetModel);
    symbolModel = createSymbolModel(signalFieldSymbolModel, dataFieldSymbolModel);
    sampleModel = createSampleModel(symbolModel);
    analogModel = createAnalogModel(packetModel, bitModel, symbolModel, sampleModel);
    IMobility *mobility = transmitter->getAntenna()->getMobility();
    // assuming movement and rotation during transmission is negligible
    const simtime_t endTime = startTime + analogModel->getDuration();
    const Coord startPosition = mobility->getCurrentPosition();
    const Coord endPosition = mobility->getCurrentPosition();
    const EulerAngles startOrientation = mobility->getCurrentAngularPosition();
    const EulerAngles endOrientation = mobility->getCurrentAngularPosition();
    return new LayeredTransmission(packetModel, bitModel, symbolModel, sampleModel, analogModel, transmitter, macFrame, startTime, endTime, startPosition, endPosition, startOrientation, endOrientation);
}

} // namespace physicallayer

} // namespace inet
