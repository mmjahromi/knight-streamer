# include "transmission/eeg_messenger.hpp"


EEGMessenger::EEGMessenger
(
    std::string streamName, 
    std::vector<std::string> channelLabels,
    std::string sourceId
)
{
    lsl::stream_info info (
        streamName, "EEG", CHANNEL_COUNT,
        SAMPLE_RATE, lsl::cf_float32, sourceId
    );

    lsl::xml_element description = info.desc();
    description.append_child_value("manufacturer", "NeuroPawn");

    bool channelsLabelled = !channelLabels.empty();
    lsl::xml_element channels = description.append_child("channels");
    for (int i = 0; i < CHANNEL_COUNT; i++)
    {
        if (channelsLabelled && channelLabels[i].empty()) continue;

        lsl::xml_element ch = channels.append_child("channel");
        ch.append_child_value("unit", "microvolts");
        ch.append_child_value("type", "EEG");

        if (channelsLabelled)
        {
            ch.append_child_value("label", channelLabels[i]);
        }
    }

    mOutlet = new lsl::stream_outlet(info);
}

EEGMessenger::~EEGMessenger()
{
    delete mOutlet;
}


void EEGMessenger::onSampleReceived(KnightSample sample)
{
    mLastSampleReceived = sample;
    mOutlet->push_sample(sample.eegChannels);
}

void EEGMessenger::awaitSample(int channelIndex, bool allowZeroValue)
{
    uint8_t lastCounterValue = mLastSampleReceived.counter;
    while (mLastSampleReceived.counter == lastCounterValue);
    if (allowZeroValue) return;
    while (mLastSampleReceived.eegChannels[channelIndex] == 0);
}