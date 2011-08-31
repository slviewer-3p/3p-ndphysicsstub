project(HACD_LIB CXX C)

set (SOURCE_FILES src/hacdGraph.cpp  src/hacdHACD.cpp  src/hacdICHull.cpp  src/hacdManifoldMesh.cpp )
file (GLOB INCLUDE_FILES inc/*.h )

add_library(hacd STATIC ${SOURCE_FILES} ${INCLUDE_FILES} )

install( TARGETS hacd DESTINATION lib )