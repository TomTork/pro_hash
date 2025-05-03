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
        helper/directSearch.h
        simcard-hash-table/SimCardHashTable.cpp
        simcard-hash-table/SimCardHashTable.h
        status-list/StatusList.cpp
        status-list/StatusList.h
        client-avl-tree/ClientAvlTree.cpp
        client-avl-tree/ClientAvlTree.h
        helper/checkPassport.h
        helper/input.h
        helper/checkNumber.h
        helper/checkTariff.h
        helper/isNumber.h
)
