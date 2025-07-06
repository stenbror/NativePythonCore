
cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0167 NEW)

project(NativePythonCore)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows-spesifikk konfigurasjon
if(WIN32)
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)

    # Sett CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS for å generere eksport-bibliotek
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

    # Sett output-kataloger
    foreach(OUTPUT_CONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${OUTPUT_CONFIG} OUTPUT_CONFIG)
        set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${CMAKE_BINARY_DIR})
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${CMAKE_BINARY_DIR})
        set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUT_CONFIG} ${CMAKE_BINARY_DIR})
    endforeach()

    # Tillat VCPKG toolchain
    if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
                CACHE STRING "")
    endif()
endif()

# Finn Boost
find_package(Boost REQUIRED COMPONENTS unit_test_framework)
find_package(fmt CONFIG REQUIRED)

# Hovedbiblioteket
add_library(NativePythonCore SHARED src/library.cpp
        src/parser/Symbol.cpp
        src/parser/Symbol.h
        src/parser/Lexer.cpp
        src/parser/Lexer.h)

target_include_directories(NativePythonCore
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if(MSVC)
    # Sett spesifikke egenskaper for MSVC
    set_target_properties(NativePythonCore PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
            ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
            PREFIX ""
    )
endif()

# Opprett testkatalogen
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Aktiver testing
enable_testing()

# Test executable
add_executable(unit_tests tests/test_dummy.cpp
        tests/parser/test_symbols_and_trivia.cpp
        tests/parser/test_lexical_analyzer.cpp)

if(MSVC)
    # Sett spesifikke egenskaper for test executable
    set_target_properties(unit_tests PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
            RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}
            RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}
    )
endif()

# Koble mot biblioteker
target_link_libraries(unit_tests
        PRIVATE
        NativePythonCore
        Boost::unit_test_framework
        fmt::fmt
)

# Legg til test
add_test(NAME unit_tests
        COMMAND unit_tests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

# Debug-utskrift for Windows
if(WIN32)
    add_custom_command(TARGET NativePythonCore POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E echo "Library output dir: $<TARGET_FILE_DIR:NativePythonCore>"
            COMMAND ${CMAKE_COMMAND} -E echo "Library name: $<TARGET_FILE_NAME:NativePythonCore>"
    )
endif()