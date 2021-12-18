cmake_minimum_required(VERSION 3.12...3.22)

project(
    "Minsk"
    LANGUAGES "CXX"
    VERSION "0.1.0"
    DESCRIPTION "Have you ever considered Minsk?"
    HOMEPAGE_URL "https://github.com/Phytolizer/minsk-cpp"
)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(PushDirectory)

push_directory_executable(
    TARGET_NAME "Minsk"
    SOURCE_FILES "Main.cpp"
    LINKED_LIBRARIES "fmt"
)
