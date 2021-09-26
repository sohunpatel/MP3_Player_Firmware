set(LIBOPENCM3_DIR ${CMAKE_SOURCE_DIR}/libopencm3)

# Make sure that git submodule is initialized and updated
if (NOT EXISTS ${LIBOPENCM3_DIR}/Makefile)
    message(FATAL_ERROR "libopencm3 submodule not found. Initialize with 'git submodule update --init' in the root directory")
endif()

set(LIBOPENCM3_DIR ${CMAKE_SOURCE_DIR}/libopencm3)
add_custom_target(libopencm3 make TARGETS=stm32/f7 WORKING_DIRECTORY ${LIBOPENCM3_DIR})
link_directories(${LIBOPENCM3_DIR}/lib)