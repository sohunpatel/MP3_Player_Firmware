cmake_minimum_required(VERSION 3.20)
set(CROSS_TARGET_TRIPLET "arm-none-eabi-")
set(MCU "STM32F746")

set(PRJ_NAME MP3-Player)
set(MCU_FAMILY STM32F7)
set(MCU_LINE STM32F746NG)
# set(MCU_LINKER_SCRIPT STM32F746NGHx_FLASH.ld)
set(MCU_LINKER_SCRIPT stm32f4.ld)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)


project(${PRJ_NAME} C ASM)

# Compiler Settings

# Prepend the cross-compiler prefix to the used tools.
set(CMAKE_C_COMPILER "${CROSS_TARGET_TRIPLET}gcc")
set(CMAKE_CXX_COMPILER "${CROSS_TARGET_TRIPLET}g++")
set(CMAKE_ASM_COMPILER "${CROSS_TARGET_TRIPLET}as")
SET(CMAKE_OBJCOPY "${CROSS_TARGET_TRIPLET}objcopy")
SET(CMAKE_SIZE "${CROSS_TARGET_TRIPLET}size")

# Be verbose when compiling.
set(FLAGS_WARNING "-Wextra -Wshadow -Wredundant-decls -Wall -Wno-unused-parameter")
set(CFLAGS_WARNING "${FLAGS_WARNING} -Wimplicit-function-declaration -Wmissing-prototypes -Wstrict-prototypes")
set(CXXFLAGS_WARNING "${FLAGS_WARNING} -Weffc++")


# Flags which are required for gcc, g++ and as.
set(CFLAGS_CORTEX "-mthumb -mcpu=cortex-m7 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -fno-common -ffunction-sections -fdata-sections")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CFLAGS_CORTEX} ${CFLAGS_WARNING} -DSTM32F4")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CFLAGS_CORTEX} ${CXXFLAGS_WARNING} -DSTM32F4")
set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${CFLAGS_CORTEX} -DSTM32F4")

# execute_process(COMMAND sh -c "${CMAKE_C_COMPILER} ${CFLAGS_CORTEX} ${DEFS} -P -E ${CMAKE_SOURCE_DIR}/${MCU_LINKER_SCRIPT} -o ${CMAKE_BINARY_DIR}/${MCU}.ld")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --static -nostartfiles -specs=nosys.specs -Wl,--gc-sections -Wl,-Map=${PROJECT_NAME}.map -Wl,--undefined=uxTopUsedPriority -Wl,--print-memory-usage  -T ${CMAKE_SOURCE_DIR}/${MCU_LINKER_SCRIPT}")


add_library(libopencm3 STATIC IMPORTED)
set_target_properties(libopencm3 PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/libopencm3/lib/libopencm3_stm32f4.a"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/libopencm3/include"
)
add_custom_target(
  libopencm3-build
  COMMAND make lib/stm32/f4
  WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/libopencm3"
)

file(GLOB_RECURSE USER_SOURCES src/*.c)
file(GLOB FREERTOS_SOURCES FreeRTOS/*.c FreeRTOS/portable/GCC/ARM_CM7/r0p1/port.c FreeRTOS/portable/MemMang/heap_3.c)
#file(GLOB LWMEM_SOURCES lib/lwmem/src/*.c)
set(SOURCE_FILES ${USER_SOURCES} ${FREERTOS_SOURCES} ${LWMEM_SOURCES})

include_directories("${CMAKE_SOURCE_DIR}/include")
include_directories("${CMAKE_SOURCE_DIR}/FreeRTOS/include")
#include_directories(lib/lwmem/include)


add_executable(${PROJECT_NAME}.elf ${SOURCE_FILES})
add_dependencies(${PROJECT_NAME}.elf libopencm3-build)
target_link_libraries(${PROJECT_NAME}.elf libopencm3)

set(HEX_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.hex)
set(BIN_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.bin)
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
        COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf
        COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")


# The following is required to get rid of the (not supported) -rdynamic flag
# when linking the final binary.
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "" )
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "" )