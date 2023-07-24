#pragma once

#include <iostream>
#include <ctime>
#include <chrono>


using namespace std;
using namespace chrono;


class Timer{
public:

        /* construct */
    // static Timer*   get_instance        ();
    static Timer&  get_instance        (){
        static Timer _instance;
        return _instance;
    }
    ~Timer                              ();


    ///> interface
    string          get_time            ();
    string          get_date            ();
    void            set_rep_interval    (const long long _sec);
    void            set_file_interval   (const long long _sec);
    long long       get_rep_interval    ();
    bool            rep_elapsed         ();
    bool            file_elapsed        ();


private:
        /* standard */
    Timer                               ();

        /* Copy semantics */
    Timer                               (Timer& _src) = delete;
    Timer&          operator=           (Timer const&) = delete;

        /* Move semantics */
    Timer                               (Timer&& _src) = delete;
    Timer&          operator=           (Timer const&&) = delete;


        /* timestamp */
    time_t          time_now            = time(0);
    tm*             itm;
    

        /* countdown: replication interval */
    time_point< high_resolution_clock>  rep_now;
    time_point< high_resolution_clock>  rep_start;
    time_point< high_resolution_clock>  rep_last_call;
    chrono::seconds                     rep_interval;
        /* countdown: file man-t interval */
    time_point< high_resolution_clock>  file_now;
    time_point< high_resolution_clock>  file_start;
    time_point< high_resolution_clock>  file_last_call;
    chrono::seconds                     file_interval;
};