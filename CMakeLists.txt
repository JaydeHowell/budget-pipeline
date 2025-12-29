cmake_minimum_required(VERSION 3.20)
project(budget_pipeline)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development)

include(FetchContent)
FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11.git
        GIT_TAG v3.0.1
)
FetchContent_MakeAvailable(pybind11)

add_library(budget_pipeline_core
        cpp/src/event_model/transaction_event_v1.cpp
        cpp/src/engine/engine.cpp
)

target_include_directories(budget_pipeline_core PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/cpp/include
)

pybind11_add_module(
        budget_pipeline_native
        python/bindings.cpp
)

target_link_libraries(budget_pipeline_native
        PRIVATE budget_pipeline_core
)