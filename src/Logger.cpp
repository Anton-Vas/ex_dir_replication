
#include <Logger.hpp>


Logger::Logger                      (){
    
    ///> log file management
    file_name.append(t.get_date() + "_" + t.get_time() + "_log_file" + file_type);
    file_open( get_file_path() + file_name);

}

Logger::~Logger                     (){

    file_close();
};



void Logger::log                    (const int _head, const string& _msg){
    
    string msg = assemble_msg(_head, _msg);

    ///> terminal
    cout << msg << endl;

    ///> log file
    file_log(msg);
}

void Logger::log_terminal           (const int _head, const string& _msg){

    cout << assemble_msg(_head, _msg) << endl;
}

void Logger::auto_save              (){
    
    file_close();
    file_open(get_file_path() + file_name);

    log(INFO, "Log file AUTO_SAVE sequence");
}



bool Logger::file_is_open           (){

    if(file_mn.is_open()){
        return true;
    }
    else{
        return false;
    }
}

void Logger::file_open              (const string& _file_name){
    
    file_mn.open(_file_name, fstream::in | fstream::out | fstream::app);

}

void Logger::file_close             (){
    
    if(file_is_open()){
        file_mn.close();
    }
}

void Logger::file_log               (const string& _msg){
    
    file_mn << _msg << "\n";
}

string  Logger::get_file_path       (){
    
    file_path_mn.clear();
    file_path_mn = (file_path);

    return absolute(file_path_mn);
}


string Logger::assemble_msg         (const int _head, const string& _msg){

    ///> msg init/msg
    string msg {t.get_date() + " " + t.get_time() + " "};
    
    ///> header
    if(_head >= HEAD_TYPE::OK && _head < HEAD_TYPE::EMPTY ){
        msg.append(log_header.at(_head));
    }
    else{
        msg.append(log_header.at(HEAD_TYPE::EMPTY));
    }

    ///> message
    msg.append(_msg);

    return msg;
}
