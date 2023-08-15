
#include <Logger.hpp>


Logger::Logger                      (){

    file_name.append(t.get_date() + "_" + t.get_time() + "_log_file" + file_type);
    file_open( file_old_path + "/" + file_name);
}

Logger::~Logger                     (){

    file_close();
};



void Logger::log                    (const int _head, const string& _msg){
    
    string msg = assemble_msg(_head, _msg);

    ///> terminal
    cout << msg << endl;

    ///> log file
    file_mn << msg << "\n";
}

void Logger::log_terminal           (const int _head, const string& _msg){

    cout << assemble_msg(_head, _msg) << endl;
}

void Logger::auto_save              (){
    
    file_close();
    file_open( file_path + "/" + file_name);
    while(!file_mn.is_open()){}

    // log(INFO, "log file autosave");
}

void Logger::set_paths              (){

    ///> log file management
    /*  DESCRIPTION:
    *   The 'log' file is created at the moment of the log obj. creation so i could add msg right away.
    *   At first the 'log' file placed in the temporary place but as the 'log_path' arrives, i change its location and continue logging there.
    */
    if(string(file_old_path + "/" + file_name).compare(file_path + "/" + file_name) != 0){
        file_close();
        fs::copy_file(file_old_path + "/" + file_name, file_path + "/" + file_name);
        fs::remove(file_old_path + "/" + file_name);
        file_open( file_path + "/" + file_name);
    }
}

void Logger::set_log_path        (const string& _p){

    file_path.append(_p);
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
