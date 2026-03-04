# include "neuropawn/knight.hpp"
# include "utils/cast.h"


KnightSample::KnightSample(const unsigned char* data, int gain)
{
    counter = data[1];

    const unsigned char* exgData = data + EXG_DATA_OFFSET;
    double eegScale = BASE_EEG_SCALE / gain;

    for (int i = 0; i < CHANNEL_COUNT; i++)
    {
        const unsigned char* channelData = exgData + 2 * i;
        int channelValue = castTwoByteInteger(channelData);
        eegChannels[i] = channelValue * eegScale;
    }

    lOffStatP = data[LOffStatP_DATA_OFFSET];
    lOffStatN = data[LOffStatN_DATA_OFFSET];
}


KnightIMUSample::KnightIMUSample(const unsigned char* data, int gain)
: KnightSample(data, gain)
{
    const unsigned char* imuData = data + IMU_DATA_OFFSET;

    acceleration = castVector3(imuData);
    gyro = castVector3(imuData + 12);
    mag = castVector3(imuData + 24);
}


KnightSample KnightSample::parse(const unsigned char* data, int gain)
{
    return KnightSample(data, gain);
}

KnightSample KnightIMUSample::parse(const unsigned char* data, int gain)
{
    return KnightIMUSample(data, gain);
}