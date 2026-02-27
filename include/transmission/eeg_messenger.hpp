# pragma once
# include "neuropawn/knight.hpp"


class EEGMessenger : public IKnightSampleListener
{
    lsl::stream_outlet* mOutlet;

    public:
    ~EEGMessenger();
    EEGMessenger(
        std::string streamName,
        std::string sourceId = "Knight_Streamer"
    );
    
    void onSampleReceived(KnightSample sample);
};