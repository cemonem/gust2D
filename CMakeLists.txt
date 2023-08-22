cmake_minimum_required(VERSION 3.25)
project(gust)

set(CMAKE_CXX_STANDARD 14)

find_package(GTest CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
find_package(tinyxml2 CONFIG REQUIRED)

add_library(gust STATIC src/gust/physics/engine2.cpp 
                        src/gust/physics/rigidbody2.cpp
                        src/gust/physics/collider2.cpp)

target_include_directories(gust PUBLIC include)

add_library(apputils STATIC src/apputils/apputils.cpp)
target_include_directories(apputils PUBLIC include)
target_link_libraries(apputils PUBLIC sfml-system sfml-network sfml-graphics sfml-window tinyxml2::tinyxml2)

add_executable(visual_test_generic test/visual_tests/visual_test_generic.cpp)
target_include_directories(visual_test_generic PUBLIC include)
target_link_libraries(visual_test_generic PUBLIC gust apputils)

add_executable(test test/tform2_test.cpp)
target_include_directories(test PUBLIC include GTest::gtest)
target_link_libraries(test PUBLIC gust GTest::gtest_main)
