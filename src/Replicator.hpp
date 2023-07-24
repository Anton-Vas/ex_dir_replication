#pragma once

#include <iostream>
#include <string>
#include <filesystem>

#include <Parser.hpp>


using namespace std;


class Replicator{
public:
    ///> system
        /* standard */
    Replicator                          ();
    ~Replicator                         ();

    ///> interface
    void                copy            ();
    void                gep_paths       (Parser* const _p);


private:
        /* Copy semantics */
    Replicator                          (Replicator& _src) = delete;
    Replicator&         operator=       (Replicator const&) = delete;

        /* Move semantics */
    Replicator                          (Replicator&& _src) = delete;
    Replicator&         operator=       (Replicator const&&) = delete;

    string              src_path        = {""};
    string              rep_path        = {""};

    Logger&             log                 = Logger::get_instance();
};