#pragma once

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <map>

#include <Parser.hpp>


using namespace std;
namespace fs = std::filesystem;


class Replicator{
public:
    ///> system
    Replicator                          ();
    ~Replicator                         ();

    ///> interface
    void                copy            ();
    string              recursion_copy  (const string& _path);
    void                set_paths       (Parser* const _p);


private:
        /* Copy&Move semantics */
    Replicator                          (Replicator& _src) = delete;
    Replicator&         operator=       (Replicator const&) = delete;
    Replicator                          (Replicator&& _src) = delete;
    Replicator&         operator=       (Replicator const&&) = delete;
    

    string              src_path        {""};
    string              rep_path        {""};
    string              rep_new_fld     {""};

    fstream             file_mn;
    const string        container_files {"/home/dev/Desktop/ex_dir_replication/rep/container_files.txt"};
    map<string, bool>   map_files;
    bool                first_run       = true;

    Logger&             log                 = Logger::get_instance();
};