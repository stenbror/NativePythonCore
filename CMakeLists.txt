cmake_minimum_required(VERSION 3.10)

cmake_policy(SET CMP0167 NEW)

project(Test)

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

# Opprett testkatalogen hvis den ikke eksisterer
file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Legg til testkatalogen
enable_testing()

# Opprett test executable
add_executable(unit_tests tests/test_dummy.cpp)

# Koble test executable mot Boost Test og hovedbiblioteket
target_link_libraries(unit_tests 
    PRIVATE 
    Boost::unit_test_framework
    NativePythonCore
)

# Legg til testen i CTest
add_test(NAME unit_tests COMMAND unit_tests)
