
#include <Signal.hpp>


bool SignalHandler::mb_got_exit_signal = false;


SignalHandler::SignalHandler            (){}

SignalHandler::~SignalHandler           () {}



bool SignalHandler::get_exit_signal     ()
{
    return mb_got_exit_signal;
}

void SignalHandler::set_exit_signal     (bool _bExitSignal)
{
    mb_got_exit_signal = _bExitSignal;
}

/**
* @param[in] _ignored Not used but required by function prototype
*                     to match required handler.
*/
void SignalHandler::exit_signal_handler     (int _ignored)
{
    mb_got_exit_signal = true;
}

void SignalHandler::setup_signal_handlers   ()
{
    if (signal((int) SIGINT, SignalHandler::exit_signal_handler) == SIG_ERR)
    {
        throw SignalException("SIGINT (Ctrl-C)");
    }
}