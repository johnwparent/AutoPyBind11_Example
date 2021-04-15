cmake_minimum_required(VERSION 3.15)
project(AutoPyBind11_Example CXX)

include(CMake/GetAutoPyBind11.cmake)

add_library(example src/main.cpp)
target_include_directories(example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

autopybind11_add_module(PyBind11_Example
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrappers/example_wrap.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES example)
