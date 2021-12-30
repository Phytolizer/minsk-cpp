function(minsk_target)
    cmake_parse_arguments(
        PARSE_ARGV 0 "MINSK" "" "TARGET_NAME;TARGET_KIND"
        "SOURCES;LIBRARIES;INCLUDED_DIRECTORIES"
    )
    string(TOLOWER "${MINSK_TARGET_KIND}" MINSK_TARGET_KIND)
    if(MINSK_TARGET_KIND STREQUAL "static_library")
        set(MINSK_TARGET_KIND "library")
        set(MINSK_PRIVACY PUBLIC)
    elseif(MINSK_TARGET_KIND STREQUAL "shared_library")
        set(MINSK_TARGET_KIND "library")
        set(MINSK_SHARED SHARED)
        set(MINSK_PRIVACY PUBLIC)
    else()
        set(MINSK_PRIVACY PRIVATE)
    endif()
    list(TRANSFORM MINSK_SOURCES PREPEND "minsk/source/")
    cmake_language(
        CALL "add_${MINSK_TARGET_KIND}" "${MINSK_TARGET_NAME}" ${MINSK_SHARED}
        ${MINSK_SOURCES}
    )
    target_include_directories(
        "${MINSK_TARGET_NAME}" ${MINSK_PRIVACY} ${MINSK_INCLUDED_DIRECTORIES}
    )
    target_link_libraries(
        "${MINSK_TARGET_NAME}" ${MINSK_PRIVACY} ${MINSK_LIBRARIES}
    )
    target_compile_features(
        "${MINSK_TARGET_NAME}" ${MINSK_PRIVACY} "cxx_std_20"
    )
endfunction()
