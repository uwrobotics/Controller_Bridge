cmake_minimum_required(VERSION 3.14)
project(MotorControllerLib)

# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Create a static library target
add_library(odrive STATIC
    src/lib.cpp
)

# Expose public headers to users of the library
target_include_directories(odrive PUBLIC ${CMAKE_SOURCE_DIR}/inc)

# Gtest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  utils_test
  test/test_can_header.cpp
  test/test_can_msg.cpp
)

target_include_directories(utils_test PRIVATE ${CMAKE_SOURCE_DIR}/inc)

target_link_libraries(
  utils_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(utils_test)
