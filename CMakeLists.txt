cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0167 NEW)

project(NativePythonCore)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Boost configuration
if(WIN32)
    set(Boost_USE_STATIC_LIBS OFF)
    set(Boost_USE_MULTITHREADED ON)
    set(Boost_USE_STATIC_RUNTIME OFF)

    # Allow for VCPKG toolchain file
    if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
                CACHE STRING "")
    endif()
endif()


# Find Boost package with unit_test_framework component
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Hovedbiblioteket
add_library(NativePythonCore SHARED src/library.cpp)

# Konfigurer eksport-makroer for Windows
if(WIN32)
    target_compile_definitions(NativePythonCore
            PRIVATE NATIVEPYTHONCORE_EXPORTS
            PUBLIC NATIVEPYTHONCORE_IMPORTS
    )
endif()

# Opprett testkatalogen
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Aktiver testing
enable_testing()

# Test executable
add_executable(unit_tests tests/test_dummy.cpp)

# Sett output-katalog for tester på Windows
if(WIN32)
    set_target_properties(unit_tests PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
            RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}
            RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}
    )
endif()

# Koble mot biblioteker
target_link_libraries(unit_tests
        PRIVATE
        Boost::unit_test_framework
        NativePythonCore
)

# Legg til test
add_test(NAME unit_tests
        COMMAND unit_tests
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})



