cmake_minimum_required(VERSION 4.0)
project(budget_pipeline)

set(CMAKE_CXX_STANDARD 20)

include_directories(cpp/include)
include_directories(cpp/include/event_model)
include_directories(cpp/src)
include_directories(cpp/src/event_model)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

include(FetchContent)
FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11
        GIT_TAG v3.0.1
)
FetchContent_MakeAvailable(pybind11)

pybind11_add_module(
        budget_pipeline_native
        python/bindings.cpp
)


add_executable(budget_pipeline
        cpp/include/event_model/transaction_event_v1.h
        cpp/src/event_model/transaction_event_v1.cpp
        python/bindings.cpp)
