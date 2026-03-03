# pragma once


struct CommandLineArguments {
    std::string serialPort = "";
    bool useIMUProtocol = false;

    static const std::set<int> validGainValues;
    int gain = 12;

    std::string streamName = "";
    std::vector<std::string> channelLabels;
};

CommandLineArguments ParseCommandLineArguments(int argc, char* argv[]);
void ValidateCommandLineArguments(CommandLineArguments arguments);
std::vector<std::string> ParseChannelLabels(std::string montageString);