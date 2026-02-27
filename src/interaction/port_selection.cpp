# include "interaction/port_selection.hpp"
# include "utils/print_helpers.hpp"


const char* selectPort(std::string portName)
{
    while (portName.empty())
    {
        PRINT("Serial Port not specified.");
        PRINT("\t0) rescan");

        auto availableDevices = serial::CSerialPortInfo::availablePortInfos();
        int deviceCount = (int)availableDevices.size();

        int deviceIndex = 1;
        for (const serial::SerialPortInfo& device : availableDevices)
        {
            PRINTF(
                "\t {}) {} : {}", deviceIndex++,
                device.portName, device.description
            );
        }
        PRINTF("\t{}+) exit", deviceIndex);
        OUTF("Which do you want to use? [0-{}]\t", deviceIndex);

        try
        {
            std::string input;
            std::cin >> input;
            int selection = std::stoi(input);

            if (selection < 0) throw std::exception("invalid input");
            if (selection > 0 && selection >= deviceCount) exit(0);
            else if (selection > 1)
            {
                portName = availableDevices[selection - 1].portName;
            }
        }
        catch (const std::exception& err)
        {
            PRINT("Invalid selection, exiting...")
            (void)err; exit(0);
        }

        if (portName.empty()) clear_lines(deviceCount + 5);
    }
    return portName.c_str();
}