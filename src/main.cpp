# include "arguments.hpp"
# include "utils/print_helpers.hpp"
# include <vector>


int main(int argc, char* argv[])
{
    CommandLineArguments arguments = ParseCommandLineArguments(argc, argv);
    std::string serial_port = arguments.serial_port;

    while (serial_port.empty())
    {
        PRINT("Serial Port not specified.");
        PRINT("\t0) rescan");

        

        std::vector<serial::SerialPortInfo> devices_found
            = serial::CSerialPortInfo::availablePortInfos();
        size_t device_count = devices_found.size();

        int device_index = 1;
        for (const serial::SerialPortInfo& device : devices_found)
        {
            PRINTF(
                "\t {}) {} : {}", device_index++,
                device.portName, device.description
            );
        }
        PRINTF("\t{}+) exit", device_index);
        OUTF("Which do you want to use? [0-{}]\t", device_index);

        try
        {
            std::string input;
            std::cin >> input;
            unsigned int selection = std::stoi(input);

            if ((int)selection >= device_count) exit(0);
            else if (selection > 1)
            {
                serial_port = devices_found[selection - 1].portName;
            }
        }
        catch (const std::exception& err)
        {
            PRINT("Invalid selection, exiting...")
            (void)err; exit(0);
        }
    }
    
}