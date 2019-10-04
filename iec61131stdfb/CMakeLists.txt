
add_ov_library(iec61131stdfb FALSE)
ov_library_includes(iec61131stdfb fb)

if(UNIX)
    target_link_libraries(iec61131stdfb -lm)
endif()