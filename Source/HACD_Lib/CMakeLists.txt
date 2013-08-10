project(HACD_LIB CXX C)

if( MSVC )
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_SCL_SECURE_NO_WARNINGS=1" )
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO  "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -D_SECURE_STL=0" )
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -D_SECURE_STL=0 -D_HAS_ITERATOR_DEBUGGING=0 -D_SECURE_SCL=0" )
  add_definitions( "/Oy-" )
endif( MSVC )

set (SOURCE_FILES src/hacdGraph.cpp  src/hacdHACD.cpp  src/hacdICHull.cpp  src/hacdManifoldMesh.cpp src/hacdMeshDecimator.cpp src/hacdMicroAllocator.cpp src/hacdRaycastMesh.cpp )
file (GLOB INCLUDE_FILES inc/*.h )

add_library(hacd STATIC ${SOURCE_FILES} ${INCLUDE_FILES} )

install( TARGETS hacd DESTINATION ${ND_LIBDIR} )
