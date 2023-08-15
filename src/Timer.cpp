
#include <Timer.hpp>


Timer::Timer                        (){
    
    rep_start = high_resolution_clock::now();
    rep_last_call = rep_start;
    file_start = high_resolution_clock::now();
    file_last_call = file_start;

}

Timer::~Timer                       (){};



string Timer::get_time              (){
    time_now = time(0);
    itm = localtime(&time_now);
    return to_string(itm->tm_hour) + "-" + to_string(itm->tm_min) + "-" + to_string(itm->tm_sec);
}

string Timer::get_date              (){
    time_now = time(0);
    itm = localtime(&time_now);
    return to_string(itm->tm_mday) + "-" + to_string(1 + itm->tm_mon) + "-" + to_string(1900 + itm->tm_year);
}

void Timer::set_rep_interval        (const long long _sec){
    rep_interval = chrono::seconds(_sec);
}

void Timer::set_file_interval       (const long long _sec){
    file_interval = chrono::seconds(_sec);
}

long long Timer::get_rep_interval   (){
    return rep_interval.count();
}

bool Timer::rep_elapsed             (){
    
    rep_now = high_resolution_clock::now();
    auto rep_since_last_call = rep_now - rep_last_call;

    if(rep_since_last_call >= rep_interval){

        rep_last_call = rep_now;
        return true;
    }
    return false;
}

bool Timer::file_elapsed            (){
    
    file_now = high_resolution_clock::now();
    auto file_since_last_call = file_now - file_last_call;

    if(file_since_last_call >= file_interval){

        file_last_call = file_now;
        return true;
    }
    return false;
}
