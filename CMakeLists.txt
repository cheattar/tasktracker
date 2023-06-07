cmake_minimum_required(VERSION 3.1)
project(TaskTracker LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
cmake_policy(SET CMP0135 NEW)

include(FetchContent)

FetchContent_Declare(fmt URL https://github.com/fmtlib/fmt/releases/download/10.0.0/fmt-10.0.0.zip)
FetchContent_MakeAvailable(fmt)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(tasktracker tasktracker.cpp)
target_link_libraries(tasktracker PRIVATE nlohmann_json::nlohmann_json fmt::fmt)
