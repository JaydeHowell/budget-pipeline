cmake_minimum_required(VERSION 4.0)
project(budget_pipeline)

set(CMAKE_CXX_STANDARD 20)

include_directories(cpp/include)
include_directories(cpp/include/event_model)
include_directories(cpp/src)
include_directories(cpp/src/event_model)

add_executable(budget_pipeline
        cpp/include/event_model/transaction_event_v1.h
        cpp/src/event_model/transaction_event_v1.cpp)
