cmake_minimum_required(VERSION 3.9)

project(MP3-Player LANGUAGES ASM C CXX)

option(USE_LIBOPECM3 "Use libopencm3 libary" ON)
option(USE_FREERTOS "Use FREERTOS libary" OFF)

# Set compuler optimizations
set(COMPILER_OPTIMIZATION "-O3")

# Can only build with arm-none-eabi
if (NOT CMAKE_SYSTEM_PROCESSOR STREQUAL "arm-none-eabi")
    message(FATAL_ERROR "Invalid CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
endif ()

if (USE_LIBOPENCM3)
    
endif ()

file(GLOB_RECURSE USER_SOURCES ./*.c ./*.cpp)
file(GLOB_RECURSE INC_FILES ${CMAKE_SOURCE_DIR}/Include/*.h "include/*.tpp")

add_executable(${PROJECT_NAME}.elf ${USER_SOURCES})

target_link_libraries(${PROJECT_NAME}.elf opencm3_stm32f7 freertos)