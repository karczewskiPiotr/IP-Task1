cmake_minimum_required(VERSION 3.4)
project(Library)

set(SOURCE_FILES
    include/CImg.h
    include/ArgumentsHandler.h
    include/Error.h
    include/ImageProcesser.h
    src/ArgumentsHandler.cpp
    src/Error.cpp
    src/ImageProcesser.cpp
)

add_library(Library ${SOURCE_FILES})
target_include_directories(Library PUBLIC include)