# Set compiler
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m0)

# Specify cross compiler
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# No standard C library, no OS
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_EXE_LINKER_FLAGS_INIT "")
set(CMAKE_C_FLAGS_INIT "-mcpu=cortex-m0 -mthumb -mfloat-abi=soft -fno-exceptions -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS_INIT "${CMAKE_C_FLAGS_INIT} -fno-rtti")
set(CMAKE_ASM_FLAGS_INIT "-mcpu=cortex-m0 -mthumb")

# Prevent default CMake stdlib linkage
set(CMAKE_CXX_STANDARD_LIBRARIES "")
set(CMAKE_C_STANDARD_LIBRARIES "")