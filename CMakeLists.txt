cmake_minimum_required(VERSION 3.1)
project(scicpp)

set (CMAKE_CXX_STANDARD 11)

file(GLOB source_files
        "*.h"
        "*.cpp"
        "Integrator/*.h"
        "MathLib/vector_3d.h"
        "Laboratory/*.h"
        "Laboratory/*.cpp"
        "PhysLib/*.h"
        "Simulations/*.cpp"
        "Util/general.h"
)

add_executable( scicpp main.cpp ${source_files} )

install(TARGETS scicpp RUNTIME DESTINATION bin)
