cmake_minimum_required(VERSION 3.16)
project(SmartEnergyBESSSimulator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(energy_simulator
    src/main.cpp
    src/bess.cpp
    src/datacenter.cpp
    src/simulator.cpp
)

target_include_directories(energy_simulator PRIVATE include)

if(MSVC)
    target_compile_options(energy_simulator PRIVATE /W4)
else()
    target_compile_options(energy_simulator PRIVATE -Wall -Wextra -Wpedantic)
endif()
