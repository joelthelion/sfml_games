cmake_minimum_required(VERSION 2.8)
project(sf1)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SFML REQUIRED system window graphics network audio)
find_package(Boost COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

subdirs(utils)
include_directories(utils)

add_executable(road road.cpp)
target_link_libraries(road ${SFML_LIBRARIES})

add_executable(basic basic.cpp)
target_link_libraries(basic ${SFML_LIBRARIES})

add_executable(wrap wrap.cpp)
target_link_libraries(wrap ${SFML_LIBRARIES})

add_executable(car car.cpp)
target_link_libraries(car ${SFML_LIBRARIES})

add_executable(count count.cpp)
target_link_libraries(count utils ${SFML_LIBRARIES} ${Boost_LIBRARIES})

add_executable(letters letters.cpp)
target_link_libraries(letters ${SFML_LIBRARIES} ${Boost_LIBRARIES})

add_executable(words words.cpp)
target_link_libraries(words ${SFML_LIBRARIES} ${Boost_LIBRARIES})

add_executable(type type.cpp)
target_link_libraries(type utils ${SFML_LIBRARIES} ${Boost_LIBRARIES})

add_executable(dice dice.cpp )
target_link_libraries(dice utils ${SFML_LIBRARIES} ${Boost_LIBRARIES})
