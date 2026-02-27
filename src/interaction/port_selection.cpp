# include "interaction/port_selection.hpp"
# include "utils/print_helpers.hpp"


const char* select_port(std::string port_name)
{
    while (port_name.empty())
    {
        PRINT("Serial Port not specified.");
        PRINT("\t0) rescan");

        auto devices_found = serial::CSerialPortInfo::availablePortInfos();
        int device_count = (int)devices_found.size();

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
            int selection = std::stoi(input);

            if (selection < 0) throw std::exception("invalid input");
            if (selection > 0 && selection >= device_count) exit(0);
            else if (selection > 1)
            {
                port_name = devices_found[selection - 1].portName;
            }
        }
        catch (const std::exception& err)
        {
            PRINT("Invalid selection, exiting...")
            (void)err; exit(0);
        }

        if (port_name.empty()) clear_lines(device_count + 5);
    }
    return port_name.c_str();
}