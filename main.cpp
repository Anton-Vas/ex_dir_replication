#include <iostream>
#include <fstream>

#include <Timer.hpp>
#include <Logger.hpp>
#include <Parser.hpp>
#include <Replicator.hpp>
#include <Signal.hpp>

using namespace std;

int main(int argc, char* argv[]){
    
    ///> setup/init
    Logger&     log     = Logger::get_instance();
    Timer&      t       = Timer::get_instance();
    Parser      parser  (argc, argv);
    Replicator  rep;
    SignalHandler   sig;
    
    ///> pass paths
    rep.set_paths(&parser);
    log.set_paths();

    ///> LINUX signal setup
    sig.setup_signal_handlers();
    
    ///> loop
    try{
        while(!sig.get_exit_signal())
        {
            ///> replication
            if(t.rep_elapsed()){
                rep.copy();
            }

            ///> file auto saving (in case of a critical error - we will save some of logs)
            if(t.file_elapsed()){
                log.auto_save();
            }
        }
    }
    catch(SignalException& e){
        log.log(log.WARN, "Exception: " + string(e.what()));
    }
}
