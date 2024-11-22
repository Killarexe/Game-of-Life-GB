file(GLOB_RECURSE cmake_generated
    ${CMAKE_BINARY_DIR}/CMakeFiles/*.cmake
    ${CMAKE_BINARY_DIR}/Makefile
    ${CMAKE_BINARY_DIR}/cmake_install.cmake
    ${CMAKE_BINARY_DIR}/CMakeCache.txt
)
file(REMOVE_RECURSE ${cmake_generated})

file(GLOB_RECURSE compiled_objects
    ${CMAKE_BINARY_DIR}/*.o
    ${CMAKE_BINARY_DIR}/*.gb
)
file(REMOVE ${compiled_objects})
