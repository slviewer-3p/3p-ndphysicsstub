cmake_minimum_required(VERSION 2.6.4)

set( CMAKE_PROJECT_NAME ndPhysicsStub )

include_directories( Source/HACD_Lib/inc )

add_subdirectory(Source/lib)
add_subdirectory(Source/HACD_Lib)
add_subdirectory(Source/Pathing)

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY 0)
set(CPACK_GENERATOR "TBZ2")
set(CPACK_STRIP_FILES TRUE )
include(CPack)
