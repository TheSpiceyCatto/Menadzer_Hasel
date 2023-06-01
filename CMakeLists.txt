cmake_minimum_required(VERSION 3.24)
project(Menadzer_Hasel)

set(CMAKE_CXX_STANDARD 23)

add_executable(Menadzer_Hasel
        main.cpp
        FunctionLibrary.h
        FunctionLibrary.cpp
        Password.h
        Password.cpp
        commands/Search.h
        commands/Search.cpp
        commands/AddCategory.h
        commands/AddCategory.cpp
        commands/DeleteCategory.h
        commands/DeleteCategory.cpp
        commands/AddPassword.h
        commands/AddPassword.cpp ChooseFromVector.tpp commands/DeletePassword.cpp)
