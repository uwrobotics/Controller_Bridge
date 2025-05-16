cmake_minimum_required(VERSION 3.14)
project(LibExample)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the library manually
add_library(libOdrive STATIC IMPORTED GLOBAL)
set_target_properties(libOdrive PROPERTIES
    IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/lib/odrive/lib/libOdrive.a
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_SOURCE_DIR}/lib/odrive/include
)

# Create your executable
add_executable(exec main.cpp)

# Link the imported static lib
target_link_libraries(exec PRIVATE libOdrive)