cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)

include(CMakeRC.cmake)
cmrc_add_resource_library(db_res
    ALIAS db::rc
    NAMESPACE csv_res
    address.csv)

project (Generator)
add_executable (Generator main.cpp database.cpp)
target_link_libraries(Generator PRIVATE db::rc)
