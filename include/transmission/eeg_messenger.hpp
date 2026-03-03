# pragma once
# include "neuropawn/knight.hpp"


class EEGMessenger : public IKnightSampleListener
{
    lsl::stream_outlet* mOutlet;
    KnightSample mLastSampleReceived;

    public:
    ~EEGMessenger();
    EEGMessenger(
        std::string streamName,
        std::vector<std::string> channelLabels,
        std::string sourceId = "Knight_Streamer"
    );
    
    void onSampleReceived(KnightSample sample);
    void awaitSample(int channelIndex, bool allowZeroValue = false);
};