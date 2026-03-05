# pragma once

using ResultVector = std::vector<serial::IProtocolResult>;


void writeSerialCommand(serial::CSerialPort &port, std::string command);

unsigned int splitBufferIntoMessages(
    const void *buffer, unsigned int bufferSize,
    unsigned int messageLength,
    const unsigned char StartByte,
    const unsigned char EndByte,
    ResultVector &results
);

long long getCurrentTimestamp();