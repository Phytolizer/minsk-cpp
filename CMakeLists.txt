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

set(STE_FILES "mc/include/minsk/syntax/kind.ste")
add_custom_command(
    OUTPUT "target/release/ste" COMMAND "cargo" "build" "--release"
)
foreach(STE_FILE ${STE_FILES})
    string(REGEX REPLACE "\\.ste$" ".hpp" HPP_FILE "${STE_FILE}")
    set(HPP_FILE "${PROJECT_BINARY_DIR}/gen/${HPP_FILE}")
    add_custom_command(
        OUTPUT "${HPP_FILE}"
        COMMAND "target/release/ste" "-f" "${STE_FILE}" "-o" "${HPP_FILE}"
        DEPENDS "${STE_FILE}" "target/release/ste"
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        COMMENT "Generating ${HPP_FILE}"
    )
    list(APPEND HPP_FILES "${HPP_FILE}")
endforeach()

minsk_target(
    TARGET_NAME "mc"
    TARGET_KIND EXECUTABLE
    SOURCES "main.cpp" "lexer.cpp"
    ABSOLUTE_SOURCES ${HPP_FILES}
    LIBRARIES "fmt" "icuuc" "icui18n" "icudata" "icuio"
    INCLUDED_DIRECTORIES "${PROJECT_BINARY_DIR}/gen/mc/include"
)
