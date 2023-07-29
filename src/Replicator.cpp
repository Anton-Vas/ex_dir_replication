
#include <Replicator.hpp>


Replicator::Replicator              (){}

Replicator::~Replicator             (){}


void Replicator::copy               (){

    log.log(log.INFO, "replication start................");

    ///> get list of files from the last run (+reboot)
        /* check/create reboot container */
    file_mn.open(container_files, fstream::in | fstream::out | fstream::app);
    while(!file_mn.is_open()){}

    ///> is file empty?
    /*  DESCRIPTION:
    *   Place the read pos to the last char
    *   if 'length' between start and the last char >0 -> file has some paths
    */
    file_mn.seekg(0, ios::end);
    int length = file_mn.tellg();
    if(length == 0){
        first_run = true;
    }
    else{
        file_mn.seekg(0, ios::beg);
        first_run = false;
    }
    
    ///> choose appropriate mode 
    if(first_run == false){
        
        ///> place all paths to the 'runtime container'
        string line;
        while(getline(file_mn, line)){
            map_files.insert(pair<string, bool>(line, false));
        }
        
        ///> erase 'container_file' for the upcoming usage
        file_mn.close();
        file_mn.open(container_files, std::ofstream::out | std::ofstream::trunc);
        while(!file_mn.is_open()){}
    }


    ///> use recursion to copy
    recursion_copy(src_path);
    

    ///> set 'container_file' with necessary paths & delete from 'rep' accordingly to the 'runtime_container'
    for(const auto& [key, val] : map_files){
        if(val == true){
            file_mn << key << "\n";
        }
        else{
            ///> important to specify for non-empty folders
            if(fs::is_directory(key)){
                fs::remove_all(key);
                log.log(log.OK, "fold was removed : " + key);
            }
            else{
                fs::remove(key);
                log.log(log.OK, "file was removed : " + key);
            }
        }
    }
    map_files.clear();
    file_mn.close();  
}

string Replicator::recursion_copy   (const string& _path){
    
    ///> 'src' file tree recursion 
    for (const auto & entry : fs::directory_iterator(_path)){

        ///> it`s a file
        if(!fs::is_directory(entry)){
        
            ///> create a path similar to 'src' but in 'rep' dir
            string tmp_entry = fs::path(entry).string();
            string::size_type i = tmp_entry.find(src_path);
            if(i != string::npos){
                tmp_entry.erase(i, src_path.length());
            }
            const string tmp_rep_file{fs::path(rep_path).string() + tmp_entry};

            ///> something new in 'src' that has to be copied to 'rep'
            if(!fs::exists(tmp_rep_file) && fs::exists(entry)){
                
                ///> if we copy the log file
                log.auto_save();

                ///> save for reboot
                if (first_run){
                    ///> new file -> add to the map
                    map_files.insert(pair<string, bool>(tmp_rep_file, true));
                }
                else if(map_files.at(tmp_rep_file) == false){
                    ///> existing file -> switch the flag
                    map_files.at(tmp_rep_file) = true;
                }
                
                fs::copy_file(entry, tmp_rep_file);

                log.log(log.OK, "file was copied :  " + tmp_rep_file);
            }
            ///> something that was copied into 'rep' but we need to check for 'src'
            else if  (fs::exists(tmp_rep_file) && fs::exists(entry)){

                ///> if we copy the log file
                log.auto_save();

                ///> save for reboot
                if(map_files.at(tmp_rep_file) == false){
                    ///> it`s exists 100% -> switch the flag
                    map_files.at(tmp_rep_file) = true;
                }

                log.log(log.OK, "no need to copy :  " + tmp_rep_file);
            }
        }

        ///> it`s a folder & recursion
        if(fs::is_directory(entry)){
            
            ///> create a path similar to 'src' but in 'rep' dir
            string tmp_entry = fs::path(entry).string();
            string::size_type i = tmp_entry.find(src_path);
            if(i != string::npos){
                tmp_entry.erase(i, src_path.length());
            }
            const string tmp_folder_path{fs::path(rep_path).string() + tmp_entry};

            if(!fs::exists(tmp_folder_path) && fs::exists(entry)){

                if (first_run){
                    ///> new folder -> add to the map
                    map_files.insert(pair<string, bool>(tmp_folder_path, true));
                }
                else if(map_files.at(tmp_folder_path) == false){
                    ///> existing folder -> switch the flag
                    map_files.at(tmp_folder_path) = true;
                }

                ///> copy dir to the 'rep'
                fs::create_directory(tmp_folder_path);

                log.log(log.OK, "fold was copied :  " + tmp_folder_path);
            }
            ///> something that was copied into 'rep' but we need to check for 'src'
            else if  (fs::exists(tmp_folder_path) && fs::exists(entry)){

                ///> if we copy the log file
                log.auto_save();

                ///> save for reboot
                if(map_files.at(tmp_folder_path) == false){
                    ///> it`s exists 100% -> switch the flag
                    map_files.at(tmp_folder_path) = true;
                }

                log.log(log.OK, "no need to copy :  " + tmp_folder_path);
            }

            ///> enter the recursion with 'src' path as a target
            recursion_copy(fs::absolute(entry));
        }
    }

    ///> unlike in the Fibonacci seq. i don`t need to return val
    ///>    as i travel throughout the 'src' dir.
    return "";
}


void Replicator::set_paths          (Parser* const _p){

    ///> get paths
    src_path.append(_p->get_src_path());
    rep_path.append(_p->get_rep_path());

    ///> targeted 'rep' exist?
    if(!fs::exists(rep_path)){
        fs::create_directory(rep_path);
        log.log(log.INFO, "'rep' path is created");
    }
    else{
        log.log(log.OK, "'rep' path exists");
    }

    ///> create specific folder for the replica (in case the user wants to save in non-vacant folder)
    rep_new_fld.append("/" + fs::path(src_path).filename().string());
    rep_path.append(rep_new_fld);
    
    if(!fs::exists(rep_path)){
        fs::create_directory(rep_path);
        log.log(log.OK, "'src' folder is created in 'rep'");
    }
    else{
        log.log(log.OK, "'src' folder exists in 'rep'");
    }
}