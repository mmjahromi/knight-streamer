# pragma once
# include "knight_protocol_constants.h"
# include "utils/serial_helpers.hpp"
# include "utils/vector3.hpp"

using namespace KnightProtocolConstants;


struct KnightSample
{
    uint8_t counter;
    double eegChannels[CHANNEL_COUNT];
    double lOffStatP;
    double lOffStatN;

    KnightSample() {}
    KnightSample(const unsigned char* data, int gain);
    static KnightSample parse(const unsigned char* data, int gain);
    double& operator[](int i) { return eegChannels[i]; }
};

struct KnightIMUSample : KnightSample
{
    Vector3 acceleration;
    Vector3 mag;
    Vector3 gyro;

    KnightIMUSample(const unsigned char* data, int gain);
    static KnightSample parse(const unsigned char* data, int gain);
};


class IKnightSampleListener
{
    public:
    virtual void onSampleReceived(KnightSample) {}
};


class KnightProtocolParser : public serial::IProtocolParser
{
    protected:
    int mMessageLength;
    int mGain;
    KnightSample (*mSampleConstructor)(const unsigned char* data, int gain);
    IKnightSampleListener* mListener;

    public:
    KnightProtocolParser() {}
    KnightProtocolParser(
        KnightSample (*sampleConstructor)(const unsigned char*, int),
        int messageLength = MESSAGE_LENGTH, int gain = 12
    ):
        mMessageLength(messageLength), mGain(gain),
        mSampleConstructor(sampleConstructor)
    {}

    unsigned int parse(const void *buffer, unsigned int size, ResultVector &results);
    void onProtocolEvent(ResultVector &results);

    void setListener(IKnightSampleListener* listener);
    void removeListener();
};