cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(GraphingCalculator)

#. . . . . . . . . . . . . . . . . . . .
include(GNUInstallDirs)

if(MSVC)
    add_compile_options(/W4)
    add_link_options(/W4)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin)
    # message("compiler: MSVC")
else()
    # message("compiler: NOT MSVC")
    # add_compile_options(-Wall -Wextra -pedantic -Werror -Wl,--fatal-warnings)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()


# place binaries and libraries according to GNU standards
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})


# ------------------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

enable_testing()

# ------------------------------------

# Find the SFML package
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Include SFML directories
include_directories(${SFML_INCLUDE_DIRS})

# Grab all cpp files from includes folder
set(INCLUDES_FOLDER includes)
FILE(GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "${INCLUDES_FOLDER}/*.cpp")

ADD_EXECUTABLE(main
    main.cpp
    ${SOURCE_FILES}
)

ADD_EXECUTABLE(basic_test
    _tests/_test_files/basic_test.cpp
    ${SOURCE_FILES}
)

ADD_EXECUTABLE(testQueue
    _tests/_test_files/testQueue.cpp
    ${SOURCE_FILES}
)

ADD_EXECUTABLE(testStack
    _tests/_test_files/testStack.cpp
    ${SOURCE_FILES}
)

ADD_EXECUTABLE(testSHRPN
    _tests/_test_files/testSHRPN.cpp
    ${SOURCE_FILES}
)

# Link SFML libraries to the executables
target_link_libraries(main sfml-graphics sfml-window sfml-system)
target_link_libraries(basic_test gtest sfml-graphics sfml-window sfml-system)
target_link_libraries(testStack gtest sfml-graphics sfml-window sfml-system)
target_link_libraries(testQueue gtest sfml-graphics sfml-window sfml-system)
target_link_libraries(testSHRPN gtest gtest_main sfml-graphics sfml-window sfml-system)

