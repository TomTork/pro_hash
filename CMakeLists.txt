cmake_minimum_required(VERSION 3.30)
project(pro_hash)

set(CMAKE_CXX_STANDARD 26)

add_executable(pro_hash main.cpp
        types/Client.h
        types/SimCard.h
        types/Status.h
        helper/readLinesFromFile.h
        helper/getInitialData.h
        helper/split.h
)
