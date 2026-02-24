cmake_minimum_required(VERSION 3.20)

# Set the toolchain before project() call
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_BUILD_TYPE Release)

# DevkitPro environment variables
if (NOT DEFINED ENV{DEVKITPRO})
    message(FATAL_ERROR "DEVKITPRO environment variable is not set. Please set it to your devkitPro installation directory.")
endif ()

if (NOT DEFINED ENV{DEVKITARM})
    message(FATAL_ERROR "DEVKITARM environment variable is not set. Please set it to your devkitARM installation directory.")
endif ()

# Set compilers
set(CMAKE_CXX_COMPILER "$ENV{DEVKITARM}/bin/arm-none-eabi-g++")
set(CMAKE_OBJCOPY "$ENV{DEVKITARM}/bin/arm-none-eabi-objcopy")
set(CMAKE_AS "$ENV{DEVKITARM}/bin/arm-none-eabi-as")
set(GBAFIX "$ENV{DEVKITPRO}/tools/bin/gbafix")
set(RAW2C "$ENV{DEVKITPRO}/tools/bin/raw2c")

# Skip compiler checks (cross-compilation)
set(CMAKE_CXX_COMPILER_WORKS 1)

project(grooveboy CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GBA-specific compiler flags
set(GBA_ARCH_FLAGS "-marm -mthumb-interwork -mcpu=arm7tdmi -mtune=arm7tdmi -mfloat-abi=softfp -mlong-calls -fno-exceptions -ffunction-sections")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GBA_ARCH_FLAGS} -Wall -Wextra -Wno-unused -pedantic -ffast-math -Wl,--verbose")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# GBA-specific linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -specs=gba.specs ${GBA_ARCH_FLAGS} -lm")

# Directories
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(BIN_DIR "${CMAKE_SOURCE_DIR}/bin")
set(BUILD_DIR "${CMAKE_BINARY_DIR}")

# Collect source files
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${INCLUDE_DIR}/*.h")

# Collect binary files
if (EXISTS "${CMAKE_SOURCE_DIR}/grooveboy_cpp_tiles/")
    file(GLOB ORIG_BIN_FILES "${CMAKE_SOURCE_DIR}/grooveboy_cpp_tiles/bin/*.bin")
    file(COPY ${ORIG_BIN_FILES} DESTINATION "${CMAKE_SOURCE_DIR}/bin/")
    file(COPY "${CMAKE_SOURCE_DIR}/grooveboy_cpp_tiles/structure.json" DESTINATION "${CMAKE_SOURCE_DIR}/bin/")
endif ()

file(GLOB BIN_FILES "${BIN_DIR}/*.bin")

# Function to convert binary files to object files with clean symbol names
function(add_binary_data target binary_file)
    get_filename_component(bin_filename ${binary_file} NAME_WE)
    set(output_obj "${BUILD_DIR}/bin_objects/${bin_filename}.o")
    set(wrapper_asm "${BUILD_DIR}/bin_objects/${bin_filename}_wrapper.s")

    # Create assembly wrapper that includes the binary and defines clean symbols
    file(WRITE ${wrapper_asm}
            "    .section .data\n"
            "    .align 2\n"
            "    .global ${bin_filename}_start\n"
            "    .global ${bin_filename}_end\n"
            "    .global ${bin_filename}_size\n"
            "${bin_filename}_start:\n"
            "    .incbin \"${binary_file}\"\n"
            "    .align 2\n"
            "${bin_filename}_end:\n"
            "${bin_filename}_size:\n"
            "    .int ${bin_filename}_end - ${bin_filename}_start\n"
    )

    add_custom_command(
            OUTPUT ${output_obj}
            COMMAND ${CMAKE_COMMAND} -E make_directory "${BUILD_DIR}/bin_objects"
            COMMAND ${CMAKE_AS} -o ${output_obj} ${wrapper_asm}
            DEPENDS ${binary_file}
            COMMENT "Converting ${bin_filename}.bin to object file"
            VERBATIM
    )

    target_sources(${target} PRIVATE ${output_obj})
endfunction()

# Create executable
add_executable(grooveboy ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(grooveboy PRIVATE ${INCLUDE_DIR})

# Add binary data files as embedded resources
foreach (bin_file ${BIN_FILES})
    add_binary_data(grooveboy ${bin_file})
endforeach ()

# Convert ELF to GBA ROM
add_custom_command(
        TARGET grooveboy POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:grooveboy> ${CMAKE_BINARY_DIR}/grooveboy.gba
        COMMENT "Creating GBA ROM: grooveboy.gba"
        VERBATIM
)

add_custom_command(
        TARGET grooveboy POST_BUILD
        COMMAND ${GBAFIX} ${CMAKE_BINARY_DIR}/grooveboy.gba
        COMMENT "Fixing GBA ROM"
        VERBATIM
)

# Custom clean target to remove build directory
set_directory_properties(PROPERTIES ADDITIONAL_CLEAN_FILES "${BUILD_DIR}")