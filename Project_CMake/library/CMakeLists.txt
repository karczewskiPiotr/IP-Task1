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
    src/BasicImageTransformations.cpp
    src/HelperMethods.cpp
    src/ImageAnalyzers.cpp
    src/ImageFilters.cpp
)

add_library(Library ${SOURCE_FILES})
target_include_directories(Library PUBLIC include)