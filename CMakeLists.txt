cmake_minimum_required(VERSION 3.5.0)
project(algorithms VERSION 0.1.0 LANGUAGES CXX)
project(transformations VERSION 0.1.0 LANGUAGES CXX)

add_executable(transformations transformations/vec.cpp transformations/quat.cpp)

# To run:
# mkdir -p build
# cd build
# cmake .. -G Ninja
# ninja