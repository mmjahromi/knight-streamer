# pragma once


struct CommandLineArguments {
    std::string serialPort = "";
    std::string montage = "";
    std::string streamName = "";
};

CommandLineArguments ParseCommandLineArguments(int argc, char* argv[]);