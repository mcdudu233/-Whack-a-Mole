cmake_minimum_required(VERSION 3.28)
project(Whack_a_Mole)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
aux_source_directory(src SRC)
aux_source_directory(include INCLUDE)

include_directories(include)
link_directories(${CMAKE_SOURCE_DIR}/lib)
add_executable(Whack_a_Mole ${SRC} ${INCLUDE})

target_link_libraries(Whack_a_Mole easyx)
target_link_libraries(Whack_a_Mole winmm)