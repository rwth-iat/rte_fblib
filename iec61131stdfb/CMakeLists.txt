
add_ov_library(iec61131stdfb)
ov_library_includes(iec61131stdfb fb)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(iec61131stdfb PRIVATE -lm)
endif()
