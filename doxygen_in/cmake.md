A c++ cmake using the installation {#cmake}
==================================

[TOC]

# Common cmake {#cmakesec1}
The tutorials in this documentation were built on Linux and Window with this *CMakeLists.txt* file:

(assuming a sub directory named *tutorials* with a target per cpp file)

```
cmake_minimum_required(VERSION 3.0.2)

project (canvascv-tutorials)

find_package(OpenCV 3.1.0 REQUIRED)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

# add include directories to the project
include_directories(
    ${PROJECT_SOURCE_DIR}/tutorials
    ${OpenCV_INCLUDE_DIRS}
)

file(GLOB_RECURSE TUTORIAL_SRCS
    "tutorials/*.cpp"
)

if(WIN32)
    find_library(CanvasCV_LIB canvascv "C:/Program Files/canvascv 1.0.0/lib")
    include_directories("C:/Program Files/canvascv 1.0.0/include")
else()
    find_library(CanvasCV_LIB canvascv "/usr/local/lib")
    include_directories(/usr/local/include)
endif()

message ("Building these tutorials:")
foreach ( file ${TUTORIAL_SRCS} )
    get_filename_component( target_name ${file} NAME_WE )
    message ( "Example '${target_name}' will be created")
    add_executable(${target_name} ${file})
    target_link_libraries (${target_name} ${CanvasCV_LIB} ${OpenCV_LIBS})
endforeach()
```
<BR>

# Linux command line {#cmakesec2}

    cd projectDir
    mkdir build
    cd build
    cmake ..
    make
    ls
<BR>

# Windows command line {#cmakesec3}

This should be done from a **Developer Command Prompt for VS2015** (Open it from the *Start* menu):

    cd projectDir
    mkdir build
    cd build
    cmake -G "Visual Studio 14 2015 Win64" ..

Now depending if you're linking with a *Debug* or *Release* version (usually *Release*):

    msbuild ALL_BUILD.vcxproj /p:Configuration=Release
    dir Release\*.exe

OR

    msbuild ALL_BUILD.vcxproj /p:Configuration=Debug
    dir Debug\*.exe


