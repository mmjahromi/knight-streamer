# include "interaction/arguments.hpp"
# include "interaction/port_selection.hpp"
# include "interaction/ellipsis_display.hpp"
# include "neuropawn/knight_serial_interface.hpp"
# include "transmission/eeg_messenger.hpp"
# include "utils/io_helpers.hpp"


void HandleInterrupt(int);
static bool interrupted = false;

KnightBoardSerialInterface *boardInterfaceHandle;

EllipsisDisplay ellipsisDisplay;
void startWaitDisplay() { ellipsisDisplay.start(); }
void pauseWaitDisplay() { ellipsisDisplay.pauseAndClearLine(); }


int main(int argc, char* argv[])
{
    CommandLineArguments arguments = ParseCommandLineArguments(argc, argv);
    std::string portName = selectPort(arguments.serialPort);

    PRINT("---");
    OUTF("Initializing Board Interface");
    startWaitDisplay();

    KnightBoardSerialInterface boardInterface(
        startWaitDisplay, pauseWaitDisplay
    );

    EEGMessenger messenger {
        arguments.streamName,
        arguments.channelLabels
    };

    boardInterface.initialize(
        portName,
        arguments.gain,
        arguments.useIMUProtocol,
        &messenger
    );

    pauseWaitDisplay();
    OUTF("Opening serial port {}", portName);
    startWaitDisplay();

    if (!boardInterface.openPort())
    {
        ellipsisDisplay.stop();
        clear_line();
        PRINTERR("Failed to open serial port " << portName);
        exit(1);
    }
    pauseWaitDisplay();
    PRINTF("Opened serial port {}.", portName);
    
    boardInterfaceHandle = &boardInterface;
    signal(SIGINT, HandleInterrupt);
    signal(SIGTERM, HandleInterrupt);
    
    OUTF("Waiting for board response")
    if (!boardInterface.awaitBoardResponse())
    {
        PRINTERR("Board is not responding.");
        exit(1);
    }

    boardInterface.activateChannels(messenger.getEnabledChannels());

    COUT("Streaming Data");
    startWaitDisplay();

    while (true) {
        sleep(100);
    }
}


void HandleInterrupt(int s)
{
    if (!interrupted)
    {
        interrupted = true;
        ellipsisDisplay.stop();
        PRINT(std::endl << "-!-");
        PRINT("Closing port.")
        boardInterfaceHandle->closePort();
        exit(0);
    }
    signal(s, HandleInterrupt);
}