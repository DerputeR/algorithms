cmake_minimum_required(VERSION 3.15.0...3.31)
project(algorithms  VERSION 0.1.0
                    DESCRIPTION "C++ programs demonstrating various algorithms"
                    LANGUAGES CXX)

add_executable(transformations transformations/vec.cpp transformations/quat.cpp)

add_executable(bits bitflipping/bits.cpp)

set_target_properties(transformations PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(bits PROPERTIES CXX_EXTENSIONS OFF)

# To run:
# mkdir -p build
# cd build
# cmake .. -G Ninja
# ninja