# include "neuropawn/knight_serial_interface.hpp"
# include "utils/io_helpers.hpp"
# include "utils/serial_helpers.hpp"


bool KnightBoardSerialInterface::openPort(std::string portName)
{
    mPort.init(portName.c_str(), BAUD_RATE);
    return mPort.open();
}

void KnightBoardSerialInterface::closePort()
{
    mPort.close();
}


void KnightBoardSerialInterface::initialize
(
    int gain, bool useIMUProtocol,
    EEGMessenger *messenger
)
{
    mGain = gain;
    mMessenger = messenger;
    mParser = useIMUProtocol
        ? KnightProtocolParser(KnightSample::parse, IMU_MESSAGE_LENGTH, gain)
        : KnightProtocolParser(KnightIMUSample::parse, MESSAGE_LENGTH, gain);

    mParser.setListener(mMessenger);
    mPort.setProtocolParser(&mParser);
    awaitAnySample();
}

void KnightBoardSerialInterface::activateChannels(std::vector<int> channelIndices)
{
    for (int channelIndex : channelIndices)
    {
        int pinIndex = channelIndex + 1;

        OUTF("Activating Channel {}", pinIndex);
        writeSerialCommand(mPort, std::format("chon_{}_{}", pinIndex, mGain));
        awaitSample(channelIndex);

        OUTF("Adding channel {} to Right Leg Drive", pinIndex);
        writeSerialCommand(mPort, std::format("rldadd_{}", pinIndex));
        awaitSample(channelIndex);
    }
}


void KnightBoardSerialInterface::awaitSample(int channelIndex)
{
    if (mOnWaitStarted) mOnWaitStarted();
    mPort.flushReadBuffers();

    unsigned char lastCounterValue = mMessenger->getLatestCounter();
    while (mMessenger->getLatestCounter() == lastCounterValue);
    while (mMessenger->getLatestChannelValue(channelIndex) == 0);
    if (mOnWaitCompleted) mOnWaitCompleted();
}

void KnightBoardSerialInterface::awaitAnySample()
{
    if (mOnWaitStarted) mOnWaitStarted();
    while (mMessenger->getLatestCounter() != 0);
    if (mOnWaitCompleted) mOnWaitCompleted();
}