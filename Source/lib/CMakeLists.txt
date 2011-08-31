cmake_minimum_required(VERSION 2.8)

set (SOURCE_FILES LLConvexDecomposition.cpp nd_hacdConvexDecomposition.cpp nd_hacdStructs.cpp nd_hacdUtils.cpp )
file(GLOB HEADER_FILES *.h)

add_library( nd_hacdConvexDecomposition STATIC ${SOURCE_FILES} ${HEADER_FILES})

install( TARGETS nd_hacdConvexDecomposition DESTINATION lib )
install( FILES LLConvexDecomposition.h RENAME llconvexdecomposition.h DESTINATION include )