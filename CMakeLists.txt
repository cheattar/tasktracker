cmake_minimum_required(VERSION 3.1)
project(TaskTracker LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(tasktracker tasktracker.cpp)
target_link_libraries(tasktracker PRIVATE nlohmann_json::nlohmann_json)
