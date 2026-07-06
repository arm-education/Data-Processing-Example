cmake_minimum_required(VERSION 3.22)

project(Distribution_Example VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# create cmake options - USE_ARMPL
option(USE_APL "Whether to build using Arm Performance libraries or not (default = off)" OFF)
option(BUILD_TESTS "Whether to build the helper tests, to sweep through values and generate visualizations" OFF)

set(ARMPL_DIR "$ENV{ARMPL_DIR}" CACHE PATH "Path to Arm Performance Libraries root")


# set variables
set(MAIN_EXECUTABLE main)
set(SWEEP_TEST_EXECUTABLE sweep_microbench_baseline)
set(GENERATE_VISUALIZATION_EXECUTABLE generate_visualization_baseline)
set(CORE_LIBRARY core_library)


# Just need to build the CORE LIBRARY with Arm Performance Library Support
if(USE_APL)
    if(NOT ARMPL_DIR)
        message(FATAL_ERROR
            "USE_APL=ON but ARMPL_DIR is not set. "
            "run module load <armpl> or pass -DARMPL_DIR=/path/to/armpl")
    endif()
            
    message(STATUS "using Arm Performance Libraries")
    set(MAIN_EXECUTABLE main_with_apl)
    set(SWEEP_TEST_EXECUTABLE sweep_microbench_with_apl)
    set(GENERATE_VISUALIZATION_EXECUTABLE generate_visualization_with_apl)
    add_subdirectory(src)
else()
    message(STATUS "NOT using Arm Performance Libraries")
    add_subdirectory(src)

endif()


# add subdirectories (src needs to go before include)
add_subdirectory(include)


if(BUILD_TESTS)
    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(googletest)

    add_subdirectory(test)
endif()