

# include <Parser.hpp>


Parser::Parser                      (const int _argc, char* const _argv[]){
    
    if(_argc == 1){
        log.log(log.WARN, "Arguments are NOT received");
        log.log(log.COM, "Initiate autofill");

        //.. replicator pass paths
        src_path.append("src");
        rep_path.append("rep");
        
        t.set_rep_interval(5);
    }
    else if(_argc >= 2){
        log.log(log.INFO, "Arguments are received");
        for(int i = 0; i < _argc; i++){
            switch (i){
            
            case 0:
                log.log(log.COM, "abs path: " + string(_argv[i]));
                break;
            case 1:
                src_path = string(_argv[i]);
                break;

            case 2:
                rep_path = string(_argv[i]);
                break;

            case 3:
                t.set_rep_interval(stoi(string(_argv[i])));
                break;
            
            default:
                log.log(log.WARN, "Invalid args!");
                break;
            }
        }
    }

    ///> log
    log.log(log.COM, "src path: " + src_path);
    log.log(log.COM, "rep path: " + rep_path);
    log.log(log.COM, "interval: " + to_string(t.get_rep_interval()) + " sec");

    
    ///> file autosave
    t.set_file_interval(t.get_rep_interval() + 10);
}

Parser::~Parser                     (){
    //..
}


string Parser::get_src_path         (){
    return src_path;
}

string Parser::get_rep_path         (){
    return rep_path;
}