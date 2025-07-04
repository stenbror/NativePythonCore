cmake_minimum_required(VERSION 3.31.6)
project(NativePythonCore)

set(CMAKE_CXX_STANDARD 26)

# Finn Boost-pakken med nødvendige komponenter
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