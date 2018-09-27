cmake_minimum_required(VERSION 3.5)
#set(CMAKE_C_COMPILER    $RISCV/bin/riscv64-unknown-elf-gcc)
#set(CMAKE_CXX_COMPILER  $RISCV/bin/riscv64-unknown-elf-gcc)
set(CMAKE_C_COMPILER    /riscv-gnu-toolchain_c3ad555__newlib__rv64gc_lp64/bin/riscv64-unknown-elf-gcc)
set(CMAKE_CXX_COMPILER  /riscv-gnu-toolchain_c3ad555__newlib__rv64gc_lp64/bin/riscv64-unknown-elf-g++)

set(NVDLA_DIR ../nvdla)

project(nvdla)
set(CMAKE_CXX_STANDARD 11)

enable_language(C)
enable_language(ASM)

set(SOURCE_FILES
        ./startup.S
        ./helpers.S
        ./main.c
        ./port/std_syscall.c
        ./interrupt.c
    )
set(NVDLA_SRC_FILES
    ${NVDLA_DIR}/firmware/scheduler.c
    ${NVDLA_DIR}/firmware/engine.c
    ${NVDLA_DIR}/firmware/bdma.c
    ${NVDLA_DIR}/firmware/conv.c
    ${NVDLA_DIR}/firmware/sdp.c
    ${NVDLA_DIR}/firmware/cdp.c
    ${NVDLA_DIR}/firmware/pdp.c
    ${NVDLA_DIR}/firmware/rubik.c
    ${NVDLA_DIR}/firmware/cache.c
    ${NVDLA_DIR}/firmware/common.c
    ${NVDLA_DIR}/firmware/engine_data.c
    ${NVDLA_DIR}/firmware/engine_isr.c
    ${NVDLA_DIR}/firmware/engine_debug.c

    ${NVDLA_DIR}/port/riscv/nvdla_core_callbacks.c
    )

include_directories(${NVDLA_DIR}/firmware)
include_directories(${NVDLA_DIR}/firmware/include)
include_directories(${NVDLA_DIR}/include)
include_directories(${NVDLA_DIR}/port/riscv/include)

#include_directories(../inc)
#include_directories(../inc/riscv)

#include_directories(../src/lib)


#SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
#for compiler
#set(CMAKE_C_FLAGS "-march=rv64imc -mabi=lp64")
#set(CMAKE_ASM_FLAGS "-march=rv64imc -mabi=lp64")
set(CMAKE_C_FLAGS "-march=rv64im -mabi=lp64")
set(CMAKE_ASM_FLAGS "-march=rv64im -mabi=lp64")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-pic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --specs=nano.specs")         #uncomment this for using nano stdlib
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostartfiles")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstack-protector-all")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,--relax")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,--gc-sections")

if(PLAT STREQUAL "nvdla")
    #list(APPEND SOURCE_FILES console/console.c)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -T ${PROJECT_SOURCE_DIR}/nvdla.ld")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-Map,${EXECUTABLE_OUTPUT_PATH}/nvdla.map")
    #add_definitions(-D__LCC__)
else()
    list(APPEND SOURCE_FILES spike/htif.c)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -T ${PROJECT_SOURCE_DIR}/link.ld")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-Map,${EXECUTABLE_OUTPUT_PATH}/spike.map")
endif()

#for linker
message("PLAT: " ${PLAT})
message("C_FLAGS: " ${CMAKE_C_FLAGS})

message("PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}")
message("PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}")
message("EXECUTABLE_OUTPUT_PATH=${EXECUTABLE_OUTPUT_PATH}")

if(PLAT STREQUAL "nvdla")
    add_executable(nvdla.elf ${SOURCE_FILES} ${NVDLA_SRC_FILES})
else()
    add_executable(spike.elf ${SOURCE_FILES})
endif()
