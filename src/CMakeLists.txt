cmake_minimum_required(VERSION 3.5)
set(CMAKE_C_COMPILER    riscv64-unknown-elf-gcc)
set(CMAKE_CXX_COMPILER  riscv64-unknown-elf-g++)

# macro controls
add_definitions(-DUSE_HW_IO_CFG=0) # this means whether a hw patch is added to config mmio space as uncacheable

# Note 1: __man_mb() exists non-empty when at least one of the following is 0
# Note 2: if -DUSE_HW_IO_CFG=1 all barriers regarded as empty defines
add_definitions(-DUSE_R_MB=1) # read memory barrier
add_definitions(-DUSE_W_MB=1) # write memory barrier

# log controls
add_definitions(-DMAIN=1) #-DMAIN=0 to remove log
add_definitions(-DATOMIC=1)
add_definitions(-DTRAP=1)
add_definitions(-DIRQ0=1)
add_definitions(-DDLA_REG_TEST=1)

set(NVDLA_DIR ../nvdla)
set(STARTUP_DIR ./env)
set(TEST_SEARCH_DIR ./test)
set(RUNTIME_SEARCH_DIR ./)

project(nvdla)
set(CMAKE_CXX_STANDARD 11)

enable_language(C)
enable_language(ASM)

set(SOURCE_FILES
    ./riscv/main.c
    ./port/std_syscall.c
    ./arch/riscv/device.c
    ./arch/riscv/csr.c
    ./arch/riscv/csr_mmio.c
    ./arch/riscv/trap.c
    ./drivers/htif.c
    #${STARTUP_DIR}/common/constants.S
    #${STARTUP_DIR}/common/crtm.S
    #${STARTUP_DIR}/common/rv64/macros.S
    ${STARTUP_DIR}/ariane/crt.S
    ${STARTUP_DIR}/ariane/setup.c
    ./test/test_util.c
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
include_directories(${STARTUP_DIR}/ariane)
include_directories(${STARTUP_DIR}/common)
include_directories(${STARTUP_DIR}/common/rv64)
include_directories(./include)
include_directories(./include/arch/riscv)
include_directories(./test)



SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
#for compiler
#set(CMAKE_C_FLAGS "-march=rv64imc -mabi=lp64")               #for compress compile
#set(CMAKE_ASM_FLAGS "-march=rv64imc -mabi=lp64")
set(CMAKE_C_FLAGS "-march=rv64ima -mabi=lp64")
set(CMAKE_ASM_FLAGS "-march=rv64ima -mabi=lp64")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-pic")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Os")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --specs=nano.specs")      #uncomment this for using nano stdlib
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -nostartfiles")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fstack-protector-all")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,--relax")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,--gc-sections")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcmodel=medany")


message("PLAT : " ${PLAT})
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -T ${PROJECT_SOURCE_DIR}/env/ariane/default.ld")
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -T ${PROJECT_SOURCE_DIR}/env/ariane/default_qemu.ld")

# Note: the file name should include its parent dir
string(CONCAT BIN_SRC_FILE_NAME "${PLAT}/${BIN_NAME}" ".c")
find_file(BIN_SRC_FILE NAMES ${BIN_SRC_FILE_NAME} PATHS ${TEST_SEARCH_DIR} ${RUNTIME_SEARCH_DIR} NO_DEFAULT_PATH)
if (BIN_SRC_FILE)
    message("FILE : ${BIN_SRC_FILE}")
    add_executable(nvdla.elf ${SOURCE_FILES} ${NVDLA_SRC_FILES} ${BIN_SRC_FILE})
else ()
    message("cannot find binary file, check the search dir.")
endif()
