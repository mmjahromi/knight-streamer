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
    const char* port_name = select_port(arguments.serial_port);

    serial::CSerialPort serial_connection(port_name);
    serial_connection.init(port_name, 115200);
}