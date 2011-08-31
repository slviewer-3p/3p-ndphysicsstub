
#include <string.h>
#include <memory>
#include "NDConvexDecompositionHACD.h"

LLConvexDecomposition* NDConvexDecompositionHACD::getInstance()
{
	return NULL;
}

LLCDResult NDConvexDecompositionHACD::initSystem()
{
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult NDConvexDecompositionHACD::initThread()
{
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult NDConvexDecompositionHACD::quitThread()
{
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult NDConvexDecompositionHACD::quitSystem()
{
	return LLCD_NOT_IMPLEMENTED;
}

void NDConvexDecompositionHACD::genDecomposition(int& decomp)
{

}

void NDConvexDecompositionHACD::deleteDecomposition(int decomp)
{

}

void NDConvexDecompositionHACD::bindDecomposition(int decomp)
{

}

LLCDResult NDConvexDecompositionHACD::setParam(const char* name, float val)
{
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult NDConvexDecompositionHACD::setParam(const char* name, bool val)
{
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult NDConvexDecompositionHACD::setParam(const char* name, int val)
{
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult NDConvexDecompositionHACD::setMeshData( const LLCDMeshData* data, bool vertex_based )
{
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult NDConvexDecompositionHACD::registerCallback(int stage, llcdCallbackFunc callback )
{
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult NDConvexDecompositionHACD::buildSingleHull()
{
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult NDConvexDecompositionHACD::executeStage(int stage)
{
	return LLCD_NOT_IMPLEMENTED;
}

int NDConvexDecompositionHACD::getNumHullsFromStage(int stage)
{
	return 0;
}

LLCDResult NDConvexDecompositionHACD::getSingleHull( LLCDHull* hullOut ) 
{
	memset( hullOut, 0, sizeof(LLCDHull) );
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult NDConvexDecompositionHACD::getHullFromStage( int stage, int hull, LLCDHull* hullOut )
{
	memset( hullOut, 0, sizeof(LLCDHull) );
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult NDConvexDecompositionHACD::getMeshFromStage( int stage, int hull, LLCDMeshData* meshDataOut )
{
	memset( meshDataOut, 0, sizeof(LLCDMeshData) );
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult	NDConvexDecompositionHACD::getMeshFromHull( LLCDHull* hullIn, LLCDMeshData* meshOut )
{
	memset( meshOut, 0, sizeof(LLCDMeshData) );
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult NDConvexDecompositionHACD::generateSingleHullMeshFromMesh(LLCDMeshData* meshIn, LLCDMeshData* meshOut)
{
	memset( meshOut, 0, sizeof(LLCDMeshData) );
	return LLCD_NOT_IMPLEMENTED;
}

void NDConvexDecompositionHACD::loadMeshData(const char* fileIn, LLCDMeshData** meshDataOut)
{
	static LLCDMeshData meshData;
	memset( &meshData, 0, sizeof(LLCDMeshData) );
	*meshDataOut = &meshData;
}
