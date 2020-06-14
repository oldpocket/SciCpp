cmake_minimum_required(VERSION 3.1)
project(scicpp)

set (CMAKE_CXX_STANDARD 11)

FIND_PACKAGE ( FLTK )
IF ( FLTK_FOUND )
    INCLUDE_DIRECTORIES( ${FLTK_INCLUDE_DIR} )
    LINK_DIRECTORIES(${FLTK_LIBRARY_DIR} )
ENDIF ( FLTK_FOUND )

file(GLOB source_files
        "*.h"
        "*.cpp"
        "GUI/*.h"
        "GUI/*.cpp"
        "Integrator/*.h"
        "MathLib/vector_3d.h"
        "PhysLib/*.h"
        "Simulations/*.cpp"
        "Util/general.h"
)

add_executable( scicpp main.cpp ${source_files} )

TARGET_LINK_LIBRARIES (scicpp ${FLTK_LIBRARIES} )

install(TARGETS scicpp RUNTIME DESTINATION bin)
