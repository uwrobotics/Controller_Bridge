option(TARGET_STM "Build for STM32F0 using ARM toolchain" OFF)

cmake_minimum_required(VERSION 3.14)
project(MotorControllerLib)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(TARGET_STM)
  message(STATUS "Configuring build for STM32F0")
  set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/arm-gcc-toolchain.cmake")
  set(CMAKE_CXX_STANDARD 17)
else()
  message(STATUS "Configuring build for native Linux")
  set(CMAKE_CXX_STANDARD 17)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

# === Library Target ===
add_library(Odrive STATIC
    src/lib.cpp
)

target_include_directories(Odrive PUBLIC ${CMAKE_SOURCE_DIR}/inc)

# === Install Targets ===
install(TARGETS Odrive
        ARCHIVE DESTINATION lib)

install(DIRECTORY inc/ DESTINATION include)

if(NOT CMAKE_CROSSCOMPILING)
  # === Enable Testing ===
  include(CTest)  # enables BUILD_TESTING option
  if(BUILD_TESTING)

      # Fetch GoogleTest
      include(FetchContent)
      FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
      )
      set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
      FetchContent_MakeAvailable(googletest)

      # === Test Executable ===
      add_executable(utils_test
          test/test_can_header.cpp
          test/test_can_msg.cpp
      )

      target_include_directories(utils_test PRIVATE ${CMAKE_SOURCE_DIR}/inc)

      target_link_libraries(utils_test
          PRIVATE
          Odrive         # <-- your library
          GTest::gtest_main
      )

      include(GoogleTest)
      gtest_discover_tests(utils_test)

  endif()

endif()