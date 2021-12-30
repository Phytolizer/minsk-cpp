cmake_minimum_required(VERSION 3.12...3.22)

project(
    "Minsk"
    LANGUAGES "CXX"
    VERSION "0.1.0"
    DESCRIPTION "Have you ever considered Minsk?"
    HOMEPAGE_URL "https://github.com/Phytolizer/minsk-cpp"
)

find_package(fmt REQUIRED)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(MinskTarget)

minsk_target(
    TARGET_NAME "Minsk"
    TARGET_KIND EXECUTABLE
    SOURCES "main.cpp"
    LIBRARIES "fmt"
)
