#pragma once

#include <iostream>
#include <string>
#include <filesystem>

#include <Timer.hpp>
#include <Logger.hpp>


using namespace std;


class Parser{
public:
    ///> system
        /* standard */
    Parser                              (const int _argc, char* const _argv[]);
    ~Parser                             ();

    ///> interface
    string          get_src_path        ();
    string          get_rep_path        ();

private:
        /* Copy semantics */
    Parser                              (Parser& _src) = delete;
    Parser&         operator=           (Parser const&) = delete;

        /* Move semantics */
    Parser                              (Parser&& _src) = delete;
    Parser&         operator=           (Parser const&&) = delete;

    filesystem::path    path_mn;
    string          src_path            = {""};
    string          rep_path            = {""};
    Logger&         log                 = Logger::get_instance();
    Timer&          t                   = Timer::get_instance();
};