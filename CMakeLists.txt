cmake_minimum_required(VERSION 3.13)

project(rte_fblib C)

# Include ov core (if it isn't already included)
find_package(RTE)

# Include ov helper functions and definitions
get_target_property(RTE_CMAKE_DIR ov RTE_CMAKE_DIR)
include(${RTE_CMAKE_DIR}/ov_functions.cmake)
include(${RTE_CMAKE_DIR}/ov_definitions.cmake)


# The standard function block libraries
add_subdirectory(iec61131stdfb)
add_subdirectory(vdivde3696)
add_subdirectory(ACPLTlab003lindyn)

# The function block communication libraries
add_subdirectory(fbcomlib)
add_subdirectory(opcuafb)

# Miscellaneous fb/ssc libraries
add_subdirectory(SSChelper)


# Export all targets to make build tree importable via find_package(RTEfblib)
# This does only make sense if this is the root project
get_directory_property(hasParent PARENT_DIRECTORY)
if(NOT hasParent)
    export(EXPORT ${PROJECT_NAME}
        FILE RTEfblibConfig.cmake)
endif()
