# test_veeam
## Task
[Link](media/Internal_Development_in_QA_SDET_Team_tesk_task.pdf)
## Implementation
The source code has detailed commentaries for every action. Answering every logical key point and choice the code encounters. So this section is more of a general overview.

___Logger___ is the singleton class responsible for logging (file and terminal), log file management and a few necessary functions, like _msg_ assembly.

___Parser___ is the class responsible for parsing _ARGV/ARGC_ and some management in case of an empty argument.

___SignalHandler___ is the class responsible for handling Linux-type signals. Although, it has only the _SIGINT_ (Ctrl+C) handler it is possible to extend the list of signals.

___Replicator___ is the class responsible for the copying process. It`s based on the recursion throughout '_src_' folder, managing all present and missing files/folders. It relies on the _container_file.txt_ and _std::map_ allowing the re-run without manually removing previous files/folders.

___Timer___ is a class responsible for counting time for the Replicator interval copying and logging date.

Q: Why singletons ?
>A: Both Logger and Timer are quite simple classes that play a supporting role so their lifetime/inheritance is not so important in my implementation

Q: Why do some of the above classes have _filesystem/fstream_ ?
>A: It is temporary. The proper way is to implement a custom class 'Files' with all necessary operations on files to simplify general code.

Q: Can i replicate any folder ?
>A: I wrote the code as universally as possible, taking into account the possibility of manipulating files outside the project. But this behavior wasn`t tested properly, so i suggest moving the _TXT.txt_ or _FOLDER-ONE/TWO_ files/folders around to check _copy/remove/logging_ execution.

## Usage
The stages below are based on my development process. To avoid any possible errors, follow my specifications:

__configure/build__ : built with CMake (min 3.0.0), C++17, VSCode Active Kit GCC 11.3.0 x86_64-linux-gnu.

__run__: the user has two options to select:

1. Auto

```
<path_to>/test_veeam/build/test_veeam
```

This option initiates standard paths:

```
rep_path    <path_to>/test_veeam/rep
src_path    <path_to>/test_veeam/media
log_path    <path_to>/test_veeam/log
``` 
The time interval will be 5 sec.

2. Manual

```
<path_to>/test_veeam/build/test_veeam <path_to>/src_pace <path_to>/rep_place <path_to>/log_place <time_interval_in_seconds>
```
The time interval will be yours and counts in _seconds_. Any float/double values will be changed to the _long long_, while ZERO and negative values will be changed to 1 second.

## Testing

Well, this was the reason to add _AUTO_ mode. I left a few folders and a file for you to play with.
```
test_veeam
    |--media
    |   |--FOLDER_ONE
    |   |   |--FOLDER_TWO
    |   |       |--TXT.txt
```
I followed the next sequence:
1. Config/build project;
2. Run (this will demonstrate copy and ignore functionalities);
3. Init _SIGINT_;
4. Manually remove or change the location of the '*/FOLDER_TWO*' with _TXT.txt_ in it;
5. Rerun the solution (this will demonstrate the removal action);

If you`re too busy to test it yourself i made a screenshot to demonstrate the sequences above.

![IMG](/media/log_examples.png)
