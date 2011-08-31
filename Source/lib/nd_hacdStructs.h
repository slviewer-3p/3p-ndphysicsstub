#ifndef ND_HACD_DECOMPSTRUCTS_H
#define ND_HACD_DECOMPSTRUCTS_H

#include "nd_hacdDefines.h"
#include <vector>

class LLCDHull;
class LLCDMeshData;

struct DecompHull
{
	std::vector< tVecDbl > mVertices;
	std::vector< tVecLong > mTriangles;

	std::vector< float > mLLVertices;
	std::vector< hacdUINT32 > mLLTriangles;

	void clear();

	void computeLLVertices();

	void computeLLTriangles();

	void toLLHull( LLCDHull *aHull );
	void toLLMesh( LLCDMeshData *aMesh );
};

struct DecompData
{
	std::vector< DecompHull > mHulls;

	void clear();
};

struct HACDDecoder
{
	std::vector< tVecDbl > mVertices;
	std::vector< tVecLong > mTriangles;

	std::vector< DecompData > mStages;
	DecompHull mSingleHull;

	HACDDecoder();
	void clear();
};


#endif
