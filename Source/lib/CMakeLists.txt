cmake_minimum_required(VERSION 2.6.4)

if( MSVC )
   add_definitions(-D_SECURE_STL=0 -D_HAS_ITERATOR_DEBUGGING=0 -D_SECURE_SCL=0)
endif( MSVC )

set (SOURCE_FILES LLConvexDecomposition.cpp nd_hacdConvexDecomposition.cpp nd_hacdStructs.cpp nd_hacdUtils.cpp nd_EnterExitTracer.cpp nd_StructTracer.cpp )
file(GLOB HEADER_FILES *.h)

add_library( nd_hacdConvexDecomposition STATIC ${SOURCE_FILES} ${HEADER_FILES})

install( TARGETS nd_hacdConvexDecomposition DESTINATION lib/release )
install( FILES LLConvexDecomposition.h RENAME llconvexdecomposition.h DESTINATION include )
install( FILES ndConvexDecomposition.h DESTINATION include )
