cmake_minimum_required(VERSION 3.0.0)
project(test_veeam VERSION 0.1.0 LANGUAGES C CXX)

# include(CTest)
# enable_testing()

add_executable(test_veeam ${PROJECT_SOURCE_DIR}/main.cpp)


# ~~~~~~ 'root' path ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
set(ROOT /home/dev/Desktop/test_veeam)

# ~~~~~~ C++  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
set(CMAKE_CXX_STANDARD_REQUIRED 17)                             # C++ version

# find_package(Threads REQUIRED)                                  # C++ thread lib
# target_link_libraries(${CMAKE_PROJECT_NAME} Threads::Threads)

# ~~~~~~ CTest ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
# include(CTest)
# enable_testing()

# ~~~~~~ Folders ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
add_subdirectory(src)                                           # sorce code
add_subdirectory(rep)                                           # replica of sorce code
add_subdirectory(media)                                         # different media like the task itself
add_subdirectory(log)                                           # logs

# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
