cmake_minimum_required(VERSION 3.20)
set(CMAKE_PROJECT_NAME grooveboy)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_BUILD_TYPE RelWithDebInfo)

# ---------------------------------------------------------------------------
# DevkitPro environment
# ---------------------------------------------------------------------------
foreach(var DEVKITPRO DEVKITARM GBATM)
    if(NOT DEFINED ENV{${var}})
        message(FATAL_ERROR "${var} environment variable is not set.")
    endif()
endforeach()

set(DEVKITARM "$ENV{DEVKITARM}")
set(DEVKITPRO "$ENV{DEVKITPRO}")

set(CMAKE_CXX_COMPILER "${DEVKITARM}/bin/arm-none-eabi-g++")
set(CMAKE_ASM_COMPILER "${DEVKITARM}/bin/arm-none-eabi-gcc")
set(CMAKE_OBJCOPY      "${DEVKITARM}/bin/arm-none-eabi-objcopy")
set(GBAFIX             "${DEVKITPRO}/tools/bin/gbafix")
set(GBATM              "$ENV{GBATM}")

# Skip compiler checks (cross-compilation)
set(CMAKE_CXX_COMPILER_WORKS 1)
set(CMAKE_ASM_COMPILER_WORKS 1)

project(grooveboy CXX ASM)

# ---------------------------------------------------------------------------
# Language standard & flags
# ---------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(OPTIMIZATION_FLAGS "-fno-exceptions -ffunction-sections -ffast-math")
set(MACHINE_FLAGS      "-marm -mthumb-interwork -mcpu=arm7tdmi -mtune=arm7tdmi -mfloat-abi=softfp -mlong-calls")

set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAGS} ${MACHINE_FLAGS} -Wall -Wextra -Wno-unused -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG   "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_ASM_FLAGS         "")
set(CMAKE_ASM_FLAGS_DEBUG   "")
set(CMAKE_ASM_FLAGS_RELEASE "")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -specs=gba.specs -lm")

# ---------------------------------------------------------------------------
# Directories
# ---------------------------------------------------------------------------
set(SRC_DIR       "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR   "${CMAKE_SOURCE_DIR}/include")
set(RESOURCES_DIR "${CMAKE_SOURCE_DIR}/resources")
set(BIN_DIR       "${CMAKE_BINARY_DIR}/bin")
set(WRAPPERS_DIR  "${CMAKE_BINARY_DIR}/wrappers")

# ---------------------------------------------------------------------------
# Sources
# ---------------------------------------------------------------------------
file(GLOB_RECURSE SOURCES   CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS   CONFIGURE_DEPENDS "${INCLUDE_DIR}/*.h")
file(GLOB_RECURSE RESOURCES CONFIGURE_DEPENDS "${RESOURCES_DIR}/*")

# ---------------------------------------------------------------------------
# GBATM — run at configure time to discover output .bin names,
#         re-runs at build time when any resource changes.
# ---------------------------------------------------------------------------
execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory "${BIN_DIR}"
)

execute_process(
        COMMAND         ${GBATM} -i ${RESOURCES_DIR} -o ${BIN_DIR} -f
        OUTPUT_VARIABLE GBATM_OUTPUT
        ERROR_VARIABLE  GBATM_ERROR
        RESULT_VARIABLE GBATM_RESULT
)
message(STATUS "GBATM raw output: '${GBATM_OUTPUT}'")

if(NOT GBATM_RESULT EQUAL 0)
    message(FATAL_ERROR "GBATM failed:\n${GBATM_ERROR}")
endif()

string(STRIP "${GBATM_OUTPUT}" GBATM_OUTPUT)
string(REPLACE "\n" ";" EXPECTED_BINS "${GBATM_OUTPUT}")

set(GBATM_STAMP "${CMAKE_BINARY_DIR}/gbatm.stamp")

add_custom_command(
        OUTPUT  ${GBATM_STAMP} ${EXPECTED_BINS}
        COMMAND ${CMAKE_COMMAND} -E make_directory "${BIN_DIR}"
        COMMAND ${GBATM} -i ${RESOURCES_DIR} -o ${BIN_DIR} -f
        COMMAND ${CMAKE_COMMAND} -E touch ${GBATM_STAMP}
        DEPENDS ${RESOURCES}
        COMMENT "Running GBATM on resources"
        VERBATIM
)

# ---------------------------------------------------------------------------
# Assembly wrapper generation — one .S per .bin
# ---------------------------------------------------------------------------
set(WRAP_SCRIPT "${CMAKE_BINARY_DIR}/generate_wrapper.cmake")

file(WRITE ${WRAP_SCRIPT} [[
cmake_path(GET BIN_FILE STEM bin_name)
file(WRITE "${WRAPPER_FILE}"
"    .section .data\n\
    .align 2\n\
    .global ${bin_name}_start\n\
    .global ${bin_name}_end\n\
    .global ${bin_name}_size\n\
${bin_name}_start:\n\
    .incbin \"${BIN_FILE}\"\n\
    .align 2\n\
${bin_name}_end:\n\
${bin_name}_size:\n\
    .int ${bin_name}_end - ${bin_name}_start\n"
)
]])

set(WRAPPER_SOURCES)

foreach(bin_file ${EXPECTED_BINS})
    cmake_path(GET bin_file STEM bin_stem)
    set(wrapper "${WRAPPERS_DIR}/${bin_stem}_wrapper.S")
    list(APPEND WRAPPER_SOURCES ${wrapper})

    add_custom_command(
            OUTPUT  ${wrapper}
            COMMAND ${CMAKE_COMMAND} -E make_directory "${WRAPPERS_DIR}"
            COMMAND ${CMAKE_COMMAND}
            -D BIN_FILE=${bin_file}
            -D WRAPPER_FILE=${wrapper}
            -P ${WRAP_SCRIPT}
            DEPENDS ${bin_file} ${GBATM_STAMP}
            COMMENT "Generating wrapper for ${bin_stem}.bin"
            VERBATIM
    )
endforeach()

# ---------------------------------------------------------------------------
# Main target
# ---------------------------------------------------------------------------
add_executable(grooveboy ${SOURCES} ${HEADERS} ${WRAPPER_SOURCES})

set_source_files_properties(${WRAPPER_SOURCES} PROPERTIES GENERATED TRUE)

target_include_directories(grooveboy PRIVATE ${INCLUDE_DIR})

# ---------------------------------------------------------------------------
# Post-build: ELF → GBA ROM → gbafix
# ---------------------------------------------------------------------------
add_custom_command(
        TARGET  grooveboy POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:grooveboy> ${CMAKE_BINARY_DIR}/grooveboy.gba
        COMMENT "Creating GBA ROM"
        VERBATIM
)

add_custom_command(
        TARGET  grooveboy POST_BUILD
        COMMAND ${GBAFIX} ${CMAKE_BINARY_DIR}/grooveboy.gba
        COMMENT "Fixing GBA ROM header"
        VERBATIM
)

# ---------------------------------------------------------------------------
# Clean
# ---------------------------------------------------------------------------
set_directory_properties(PROPERTIES ADDITIONAL_CLEAN_FILES "${BIN_DIR};${WRAPPERS_DIR}")