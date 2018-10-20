cmake_minimum_required(VERSION 3.4)
project(IP_Task_1_217862_217846)
set(SOURCE_FILES
        src/main.cpp
   )
add_executable(IP_Task_1_217862_217846 ${SOURCE_FILES})
target_link_libraries(IP_Task_1_217862_217846 Library)
target_include_directories(IP_Task_1_217862_217846 PUBLIC include)