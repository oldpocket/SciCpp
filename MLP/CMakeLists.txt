cmake_minimum_required(VERSION 3.1)
project(mlp_classregre)

set (CMAKE_CXX_STANDARD 11)

file(GLOB source_files
        "*.h"
        "*.cpp"
        "data/*.txt"
        "mlp/*.h"
        "mlp/*.cpp"
        "util/*.h"
        "util/*.cpp"
)

add_executable( mlp_classregre main.cpp ${source_files} )

install(TARGETS mlp_classregre RUNTIME DESTINATION bin)
