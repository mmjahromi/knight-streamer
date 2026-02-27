# include "interaction/arguments.hpp"
# include "interaction/port_selection.hpp"
# include "utils/print_helpers.hpp"


int main(int argc, char* argv[])
{
    CommandLineArguments arguments = ParseCommandLineArguments(argc, argv);

    if (arguments.montage.empty())
    {
        PRINT("Montage not specified, stream will be missing channel label metadata.");
    }
    const char* port_name = selectPort(arguments.serialPort);

    serial::CSerialPort port(port_name);
    port.setBaudRate(115200);
    port.setStopBits(serial::StopBits::StopTwo);
}