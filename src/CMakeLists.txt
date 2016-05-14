cmake_minimum_required(VERSION 3.5)
set(PROJECT_NAME src_exe)
project(${PROJECT_NAME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/decorus/Dropbox/CSC/Practice/I/se_engine/")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(SOURCE_FILES main.cpp
                 logger.hpp logger.cpp
                 prepositions_dictionary.hpp prepositions_dictionary.cpp
                 text_analyzer.hpp text_analyzer.cpp
                 yandex_requester.hpp yandex_requester.cpp
        text_analyzer_ru.cpp text_analyzer_ru.hpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries (${PROJECT_NAME} -lcurl -lexpat)

