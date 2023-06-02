cmake_minimum_required(VERSION 3.1)
project(TaskTracker LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent
  GIT_PROGRESS TRUE
  GIT_SHALLOW TRUE
  GIT_TAG v3.11.2)

FetchContent_MakeAvailable(json)

add_executable(tasktracker tasktracker.cpp)
target_link_libraries(tasktracker PRIVATE nlohmann_json::nlohmann_json)
