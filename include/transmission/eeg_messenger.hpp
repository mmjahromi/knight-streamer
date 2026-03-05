# pragma once
# include "neuropawn/knight.hpp"


class EEGMessenger : public IKnightSampleListener
{
    lsl::stream_outlet* mOutlet;
    std::vector<int> enabledChannels;

    volatile unsigned char mLatestCounter;
    volatile double mLatestChannelValues[CHANNEL_COUNT];

    public:
    ~EEGMessenger();
    EEGMessenger(
        std::string streamName,
        std::vector<std::string> channelLabels,
        std::string sourceId = "Knight_Streamer"
    );

    std::vector<int> getEnabledChannels() { return enabledChannels; }
    unsigned char getLatestCounter() { return mLatestCounter; }
    double getLatestChannelValue(int channelIndex) { return mLatestChannelValues[channelIndex]; }
    
    void onSampleReceived(KnightSample sample);
};