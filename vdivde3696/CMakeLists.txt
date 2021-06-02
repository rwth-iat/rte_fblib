
add_ov_library(vdivde3696)
ov_library_includes(vdivde3696 fb)

if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(vdivde3696  PRIVATE -lm)
endif()
