cmake_minimum_required(VERSION 2.8)

set (SOURCE_FILES LLConvexDecomposition.cpp LLConvexDecompositionStubImpl.cpp )

add_library( nd_convexdecompositionHACD STATIC ${SOURCE_FILES} )

install( TARGETS nd_convexdecompositionHACD DESTINATION lib )
install( FILES LLConvexDecomposition.h RENAME llconvexdecomposition.h DESTINATION include )