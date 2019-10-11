
add_ov_library(opcuafb FALSE)
ov_library_includes(opcuafb fb opcua)

target_compile_definitions(opcuafb PRIVATE -DPLT_USE_WINSOCK2=1)
