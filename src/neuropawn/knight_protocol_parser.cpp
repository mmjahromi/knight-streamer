# include "neuropawn/knight.hpp"
# include "utils/io_helpers.hpp"


unsigned int KnightProtocolParser::parse
(
    const void *buffer, unsigned int size,
    ResultVector &results
)
{
    return splitBufferIntoMessages(
        buffer, size,
        mMessageLength,
        START_BYTE, END_BYTE,
        results
    );
}


void KnightProtocolParser::onProtocolEvent(ResultVector &results)
{
    for (const serial::IProtocolResult& result : results)
    {
        KnightSample sample = mSampleConstructor(result.data, mGain);
        if (mListener) mListener->onSampleReceived(sample);
    }
}


void KnightProtocolParser::setListener(IKnightSampleListener* listener)
{
    mListener = listener;
}
void KnightProtocolParser::removeListener()
{
    mListener = nullptr;
}