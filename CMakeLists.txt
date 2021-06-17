cmake_minimum_required(VERSION 3.15)
project(AutoPyBind11_Example CXX)

include(CMake/GetAutoPyBind11.cmake)

add_library(example src/main.cpp)
target_include_directories(example PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

autopybind11_add_module(exampleMod
                        YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrappers/example_wrap.yml
                        DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                        LINK_LIBRARIES example)


# This is not typical useage of Python Module construction via APB
# and was implemented in this fashion for pure convenience
# Typically a more nuanced approach to the output directories would be
# neccesary.
set(PYBIND11_TEST
                    call_policy.hpp
                    class.hpp
                    eigen.hpp
                    local_bindings.hpp
                    multiple_inheritance.hpp
                    operator_overloading.hpp
                    # stl_binders.hpp
                    # stl_opaque.hpp
                    # stl.hpp
                    test_constants_and_functions.hpp
                    test_enum.hpp
                    virtual.hpp)

set(TEST_WRAPPERS
                    call_policy_wrapper.yml
                    class_wrapper.yml
                    eigen_wrapper.yml
                    local_bindings.yml
                    multiple_inheritance_wrapper.yml
                    operator_overloading_wrapper.yml
                    # stl_binders_wrapper.yml
                    # stl_opaque_wrapper.yml
                    # stl_wrapper.yml
                    test_constants_and_functions.yml
                    test_enum_wrapper.yml
                    virtual_wrapper.yml)

list(LENGTH PYBIND11_TEST tests)
math(EXPR test_list "${tests} - 1")

foreach(val RANGE ${test_list})
    list(GET PYBIND11_TEST ${val} header)
    list(GET TEST_WRAPPERS ${val} wrapper)
    get_filename_component(modname ${header} NAME_WE)
    add_library(${modname} INTERFACE)
    target_sources(${modname} INTERFACE test/${header})
    target_include_directories(${modname} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/test
                                          ${CMAKE_CURRENT_BINARY_DIR}/eigen-3.3.9)
    set(modlib ${modname})
    string(APPEND modname "mod")
    autopybind11_add_module(${modname}
                            YAML_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/wrappers/${wrapper}
                            DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
                            LINK_LIBRARIES ${modlib})
endforeach()
