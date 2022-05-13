cmake_minimum_required(VERSION 3.12)
project(CSV-handler VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost 1.58 REQUIRED COMPONENTS program_options)

add_executable(csv-handler
        main.cpp
        )

target_link_libraries(csv-handler Boost::program_options)

