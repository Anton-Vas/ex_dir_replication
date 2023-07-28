# test_veeam
## Task
[link_to_file](media/Internal_Development_in_QA_SDET_Team_tesk_task.pdf)
## Implementation
The source code has detailed commentaries for every action. Answering every logical key point and choice the code encounters. So this section is more of a general overview.

___Logger___ is a singleton class responsible for logging (file and terminal), log file management and a few necessary functions, like _msg_ assembly.

___Parser___ is a singleton class responsible for parsing _ARGV/ARGC_ and some management in case of an empty argument.

___SignalHandler___ is a class responsible for handling the Linux-type signals. Although, it has only the _SIGINT_ (Ctrl+C) handler it is possible to extend the list of signals.

___Replicator___ is a class responsible for the copying process. It`s based on the recursion throughout '_src_' folder, managing all present and missing files/folders. It relies on the _container_file.txt_ and _std::map_ to initiate a re-run without manually removing previous files/folders.

___Timer___ is a class responsible for counting time for the Replicator interval copying and logging date.

Q: Why singletons ?
>A: Both Logger and Parser are quite simple classes that play a supporting role so their lifetime/inheritance is not so important in my implementation

Q: Why do some of the above classes have _filesystem/fstream_ ?
>A: It is temporary. The proper way is to implement a custom class 'Files' with all necessary operations on files to simplify general code.

Q: Can i replicate any folder ?
>A: I wrote the code as universally as possible, taking into account the possibility of manipulating files outside the project. But this behaviour wasn`t tested properly, so i suggest moving the _TXT.txt_ file around to check _copy/remove/logging_ execution.

## Usage
The stages below are based on my development process. To avoid any possible errors, follow my specifications:

__configure/build__ : built with CMake (min 3.0.0), C++17, VSCode Active Kit GCC 11.3.0 x86_64-linux-gnu.

__run__: the user has two options to select:

1. Auto

```
<path_to_code>/test_veeam/build/test_veeam
```

This option initiates standard paths:

```
rep_path    <path_to_code>/test_veeam/rep
src_path    <path_to_code>/test_veeam/media
log_path    <path_to_code>/test_veeam/log
``` 
The time interval will be 5 sec.

2. Manual

```
<path_to_code>/test_veeam/build/test_veeam <path_to_code>/src_pace <path_to_code>/rep_place <path_to_code>/log_place <time_interval_in_seconds>
```
The time interval will be yours and counts in _seconds_. Any float/double values will be changed to the _long long_, while ZERO will be changed to 1 second.



