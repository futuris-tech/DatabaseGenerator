cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 20)
project (Generator)

include(CMakeRC.cmake)
cmrc_add_resource_library(db_res
	ALIAS db::rc
	NAMESPACE csv_res
	address_spb2.csv)

add_executable (Generator main.cpp database.cpp database_reader.cpp)
target_link_libraries(Generator PRIVATE db::rc)

file (COPY
	${CMAKE_CURRENT_SOURCE_DIR}/operator.csv
	${CMAKE_CURRENT_SOURCE_DIR}/phone.csv
	${CMAKE_CURRENT_SOURCE_DIR}/job.csv
	${CMAKE_CURRENT_SOURCE_DIR}/job_proportion.csv
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
