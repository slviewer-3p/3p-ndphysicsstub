#include "nd_hacdStructs.h"
#include "LLConvexDecomposition.h"

void DecompHull::clear()
{
    mVertices.clear();
    mTriangles.clear();
    mLLVertices.clear();
    mLLTriangles.clear();
}

void DecompHull::computeLLVertices()
{
    if( mLLVertices.size()*3 != mVertices.size() )
	{
		for( int i = 0; i < mVertices.size(); ++i )
		{
			mLLVertices.push_back( mVertices[i].X() );
			mLLVertices.push_back( mVertices[i].Y() );
			mLLVertices.push_back( mVertices[i].Z() );
		}
	}
}

void DecompHull::computeLLTriangles()
{
    if( mLLTriangles.size()*3 != mTriangles.size() )
	{
		for( int i = 0; i < mTriangles.size(); ++i )
		{
			mLLTriangles.push_back( mTriangles[i].X() );
			mLLTriangles.push_back( mTriangles[i].Y() );
			mLLTriangles.push_back( mTriangles[i].Z() );
		}
	}

}

void DecompHull::toLLHull( LLCDHull *aHull )
{
    computeLLVertices();
	
    aHull->mVertexBase = &mLLVertices[0];
    aHull->mVertexStrideBytes = sizeof(float)*3;
    aHull->mNumVertices = mVertices.size();
}

void DecompHull::toLLMesh( LLCDMeshData *aMesh )
{
    computeLLVertices();
    computeLLTriangles();

    aMesh->mIndexType = LLCDMeshData::INT_32;
    aMesh->mVertexBase = &mLLVertices[0];
    aMesh->mNumVertices = mVertices.size();
    aMesh->mVertexStrideBytes = sizeof(float)*3;

    aMesh->mIndexBase = &mLLTriangles[0];
    aMesh->mIndexStrideBytes = sizeof(hacdUINT32)*3;
    aMesh->mNumTriangles = mTriangles.size();
}

void DecompData::clear()
{
    mHulls.clear();
}

HACDDecoder::HACDDecoder()
{
    mStages.resize( NUM_STAGES );
}

void HACDDecoder::clear()
{
    mVertices.clear();
    mTriangles.clear();

	for( size_t i = 0;  i < mStages.size(); ++i )
		mStages[i].clear();

    mSingleHull.clear();
  }




