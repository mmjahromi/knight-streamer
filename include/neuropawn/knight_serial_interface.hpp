# pragma once
# include "neuropawn/knight.hpp"
# include "transmission/eeg_messenger.hpp"


class KnightBoardSerialInterface
{
    private:
    static const unsigned int BUFFER_LENGTH = 4096;
    static const unsigned char MAXIMUM_MESSAGE_LENGTH = IMU_MESSAGE_LENGTH;

    serial::CSerialPort mPort;
    KnightProtocolParser mParser;
    EEGMessenger *mMessenger;
    int mGain;

    std::function<void()> mOnWaitStarted;
    std::function<void()> mOnWaitCompleted;

    bool alignData(int timeout = 100);
    void ensureChannelConfiguration(
        int channelIndex, std::string command,
        std::string commandDescription
    );
    bool awaitChannelValue(int channelIndex, int timeout = 2000);
    bool awaitCondition(std::function<bool()> predicate, int timeout);
    unsigned int readAndParseUsedBuffer();

    public:
    KnightBoardSerialInterface(
        std::function<void()> onWaitStarted,
        std::function<void()> onWaitCompleted
    ):
        mOnWaitStarted(onWaitStarted),
        mOnWaitCompleted(onWaitCompleted)
    {}

    inline bool openPort() { return mPort.open(); }
    inline void closePort() { mPort.close(); }
    inline bool isConnected() { return mPort.isOpen(); }

    void initialize(
        std::string portName,
        int gain, bool useIMUProtocol,
        EEGMessenger *messenger
    );
    void swapProtocolFormat(bool useIMUProtocol);

    bool awaitSerialData(int timeout = 8000);
    bool awaitParsedData(int timeout = 500);

    void streamData();

    void activateChannels(std::vector<int> channelIndices);
};