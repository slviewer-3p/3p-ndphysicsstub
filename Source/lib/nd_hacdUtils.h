#ifndef ND_HACD_UTILS_H
#define ND_HACD_UTILS_H

#include "nd_hacdStructs.h"
#include "LLConvexDecomposition.h"

tHACD* init( int nConcavity, int nClusters, int nMaxVerticesPerHull, HACDDecoder *aData );
DecompData decompose( tHACD *aHACD );

tVecLong fromI16( void *& pPtr, int aStride );
tVecLong fromI32( void *& pPtr, int aStride );

LLCDResult setMeshData( const LLCDMeshData* data, bool vertex_based, HACDDecoder *aDec );

#endif
