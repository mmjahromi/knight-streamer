# pragma once


struct CommandLineArguments {
    std::string serial_port = "";
    std::string montage = "";
    std::string stream_name = "";
};

CommandLineArguments ParseCommandLineArguments(int argc, char* argv[]);