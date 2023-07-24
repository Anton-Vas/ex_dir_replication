#pragma once

#include <stdexcept>
#include <signal.h>

#include <Logger.hpp>


using std::runtime_error;


class SignalException : public runtime_error
{
public:
   SignalException(const std::string& _msg)
      : std::runtime_error(_msg)
   {}
};


class SignalHandler
{
protected:
    static bool     mb_got_exit_signal;

public:
    SignalHandler();
    ~SignalHandler();

        /* get flag for exit sig */
    static bool     get_exit_signal     ();
        /* set flag for exit sig */
    static void     set_exit_signal     (bool _bExitSignal);

        /* init exit flag */
    static void     exit_signal_handler     (int _ignored);
        /* setup handler for SIGINT (Ctrl-C) */
    void            setup_signal_handlers   ();


private:
    Logger&         log                 = Logger::get_instance();

};