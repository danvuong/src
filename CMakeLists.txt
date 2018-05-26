cmake_minimum_required(VERSION 3.10)
project(src)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(src
        admin.cpp
        admin.h
        dialog.cpp
        dialog.h
        main.cpp
        MyFileCache.cpp
        MyFileCache.h
        MySocketClient.cpp
        MySocketClient.h
        MySocketServer.cpp
        MySocketServer.h
        Server_stat.cpp
        server_stat.h
        serverobject.cpp
        serverobject.h
        testducul.cpp
        testducul.h)
