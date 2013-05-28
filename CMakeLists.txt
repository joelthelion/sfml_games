cmake_minimum_required(VERSION 2.8)
project(sf1)

find_package(SFML REQUIRED system window graphics network audio)
add_executable(road road.cpp)
target_link_libraries(road ${SFML_LIBRARIES})

add_executable(basic basic.cpp)
target_link_libraries(basic ${SFML_LIBRARIES})
