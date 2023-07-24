#pragma once

#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <filesystem>

#include <Timer.hpp>


using namespace std;


class Logger{
public:

        /* construct */
    static Logger&  get_instance        (){
        static Logger _instance;
        return _instance;
    }
    ~Logger                             ();


    ///> interface
    void            log                 (const int _head, const string& _msg);
    void            log_terminal        (const int _head, const string& _msg);
    void            auto_save           ();
        

        /* log style */
    enum HEAD_TYPE{
        OK,
        WARN,
        ERR,
        INFO,
        COM,
        EMPTY,

        END
    };
    array<string, HEAD_TYPE::END> log_header = {
            /* OK */        "[ OK   ] ",
            /* WARN */      "[ WARN ] ",
            /* ERR */       "[ ERR  ] ",
            /* INFO */      "[ INFO ] ",
            /* COM */       "       - ",
            /* EMPTY */     "         "
    };


private:
        /* standard */
    Logger                              ();

        /* Copy semantics */
    Logger                              (Logger& _src) = delete;
    Logger&         operator=           (Logger const&) = delete;

        /* Move semantics */
    Logger                              (Logger&& _src) = delete;
    Logger&         operator=           (Logger const&&) = delete;


        /* log file */
    const string    file_path           = {"log/"};
    string          file_name           = {""};
    const string    file_type           = {".txt"};
    filesystem::path    file_path_mn    = {""};
    fstream         file_mn;
    bool            file_is_open        ();
    void            file_create         (const string& _file_name);
    void            file_open           (const string& _file_name);
    void            file_close          ();
    void            file_log            (const string& _msg);
    string          get_file_path       ();

    string          assemble_msg        (const int _head, const string& _msg);
    Timer&          t                   = Timer::get_instance();

};