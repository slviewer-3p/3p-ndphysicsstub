/**
 * copyright 2011 sl.nicky.ml@googlemail.com
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation;
 * version 2.1 of the License only.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <string.h>
#include <memory>
#include "nd_hacdConvexDecomposition.h"

#include "nd_hacdDefines.h"
#include "nd_hacdStructs.h"
#include "nd_hacdUtils.h"

LLConvexDecomposition* nd_hacdConvexDecomposition::getInstance()
{
	static nd_hacdConvexDecomposition sImpl;
	return &sImpl;
}

nd_hacdConvexDecomposition::nd_hacdConvexDecomposition()
{
	mNextId = 0;
	mCurrentDecoder = 0;
	mSingleHullMeshFromMesh = new HACDDecoder();
}

nd_hacdConvexDecomposition::~nd_hacdConvexDecomposition()
{
}

LLCDResult nd_hacdConvexDecomposition::initSystem()
{
	return LLCD_OK;

}

LLCDResult nd_hacdConvexDecomposition::initThread()
{
	return LLCD_OK;
}

LLCDResult nd_hacdConvexDecomposition::quitThread()
{
	return LLCD_OK;
}

LLCDResult nd_hacdConvexDecomposition::quitSystem()
{
	return LLCD_OK;
}

void nd_hacdConvexDecomposition::genDecomposition( int& decomp )
{
	HACDDecoder *pGen = new HACDDecoder();
	decomp = mNextId;
	++mNextId;

	mDecoders[ decomp ] = pGen;
}

void nd_hacdConvexDecomposition::deleteDecomposition( int decomp )
{
	delete mDecoders[ decomp ];
	mDecoders.erase( decomp );
}

void nd_hacdConvexDecomposition::bindDecomposition( int decomp )
{
	mCurrentDecoder = decomp;
}

LLCDResult nd_hacdConvexDecomposition::setParam( const char* name, float val )
{
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult nd_hacdConvexDecomposition::setParam( const char* name, bool val )
{
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult nd_hacdConvexDecomposition::setParam( const char* name, int val )
{
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult nd_hacdConvexDecomposition::setMeshData( const LLCDMeshData* data, bool vertex_based )
{
	HACDDecoder *pC = mDecoders[ mCurrentDecoder ];
	return ::setMeshData( data, vertex_based, pC );
}

LLCDResult nd_hacdConvexDecomposition::registerCallback( int stage, llcdCallbackFunc callback )
{
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult nd_hacdConvexDecomposition::buildSingleHull()
{
	return LLCD_OK;
}

LLCDResult nd_hacdConvexDecomposition::executeStage( int stage )
{
	if ( stage < 0 || stage >= NUM_STAGES )
		return LLCD_INVALID_STAGE;

	HACDDecoder *pC = mDecoders[ mCurrentDecoder ];
	tHACD *pHACD = init( 1, MIN_NUMBER_OF_CLUSTERS, MAX_VERTICES_PER_HULL, CONNECT_DISTS[0], pC );

	DecompData oRes = decompose( pHACD );

	delete pHACD;

	pC->mStages[ stage ] = oRes;

	return LLCD_OK;
}

int nd_hacdConvexDecomposition::getNumHullsFromStage( int stage )
{
	HACDDecoder *pC = mDecoders[ mCurrentDecoder ];

	if ( !pC )
		return 0;

	if ( stage < 0 || static_cast<size_t>(stage) >= pC->mStages.size() )
		return 0;

	return pC->mStages[stage].mHulls.size();
}

DecompData toSingleHull( HACDDecoder *aDecoder, LLCDResult &aRes )
{
	aRes = LLCD_REQUEST_OUT_OF_RANGE;

	for ( int i = 0; i < TO_SINGLE_HULL_TRIES; ++i )
	{
		tHACD *pHACD = init( CONCAVITY_FOR_SINGLE_HULL[i], 1, MAX_VERTICES_PER_HULL, CONNECT_DISTS[i], aDecoder );

		DecompData oRes = decompose( pHACD );
		delete pHACD;

		if ( oRes.mHulls.size() == 1 )
		{
			aRes = LLCD_OK;
			return oRes;
		}
	}

	return DecompData();
}

LLCDResult nd_hacdConvexDecomposition::getSingleHull( LLCDHull* hullOut )
{
	HACDDecoder *pC = mDecoders[ mCurrentDecoder ];

	LLCDResult res;
	DecompData oRes = ::toSingleHull( pC, res );

	if ( LLCD_OK != res || oRes.mHulls.size() != 1 )
		return res;

	pC->mSingleHull = oRes.mHulls[0];
	pC->mSingleHull.toLLHull( hullOut );

	return LLCD_OK;
}

LLCDResult nd_hacdConvexDecomposition::getHullFromStage( int stage, int hull, LLCDHull* hullOut )
{
	HACDDecoder *pC = mDecoders[ mCurrentDecoder ];

	memset( hullOut, 0, sizeof( LLCDHull ) );

	if ( stage < 0 || static_cast<size_t>(stage) >= pC->mStages.size() )
		return LLCD_INVALID_STAGE;

	DecompData &oData = pC->mStages[ stage ];

	if ( hull < 0 ||static_cast<size_t>(hull) >= oData.mHulls.size() )
		return LLCD_REQUEST_OUT_OF_RANGE;

	oData.mHulls[ hull ].toLLHull( hullOut );
	return LLCD_OK;
}

LLCDResult nd_hacdConvexDecomposition::getMeshFromStage( int stage, int hull, LLCDMeshData* meshDataOut )
{
	HACDDecoder *pC = mDecoders[ mCurrentDecoder ];

	memset( meshDataOut, 0, sizeof( LLCDHull ) );

	if ( stage < 0 || static_cast<size_t>(stage) >= pC->mStages.size() )
		return LLCD_INVALID_STAGE;

	DecompData &oData = pC->mStages[ stage ];

	if ( hull < 0 || static_cast<size_t>(hull) >= oData.mHulls.size() )
		return LLCD_REQUEST_OUT_OF_RANGE;

	oData.mHulls[ hull ].toLLMesh( meshDataOut );
	return LLCD_OK;
}

LLCDResult	nd_hacdConvexDecomposition::getMeshFromHull( LLCDHull* hullIn, LLCDMeshData* meshOut )
{
	memset( meshOut, 0, sizeof( LLCDMeshData ) );
	return LLCD_NOT_IMPLEMENTED;
}

LLCDResult nd_hacdConvexDecomposition::generateSingleHullMeshFromMesh( LLCDMeshData* meshIn, LLCDMeshData* meshOut )
{
	memset( meshOut, 0, sizeof( LLCDMeshData ) );
	mSingleHullMeshFromMesh->clear();
	LLCDResult res = ::setMeshData( meshIn, meshIn->mNumVertices > 3, mSingleHullMeshFromMesh );

	if ( LLCD_OK != res )
		return res;

	DecompData oRes = ::toSingleHull( mSingleHullMeshFromMesh, res );

	if ( LLCD_OK != res || oRes.mHulls.size() != 1 )
		return res;

	mSingleHullMeshFromMesh->mSingleHull = oRes.mHulls[0];
	mSingleHullMeshFromMesh->mSingleHull.toLLMesh( meshOut );

	return LLCD_OK;
}

void nd_hacdConvexDecomposition::loadMeshData( const char* fileIn, LLCDMeshData** meshDataOut )
{
	static LLCDMeshData meshData;
	memset( &meshData, 0, sizeof( LLCDMeshData ) );
	*meshDataOut = &meshData;
}

int nd_hacdConvexDecomposition::getParameters( const LLCDParam** paramsOut )
{
	static LLCDParam oParams[1];
	memset( &oParams[0], 0, sizeof( LLCDParam ) );
	oParams[0].mName = "nd_AlwaysNeedTriangles";
	oParams[0].mDescription = 0;
	oParams[0].mType = LLCDParam::LLCD_BOOLEAN;
	oParams[0].mDefault.mBool = true;

	*paramsOut = oParams;
	return 1;
}

int nd_hacdConvexDecomposition::getStages( const LLCDStageData** stagesOut )
{
	static LLCDStageData oStages[2];

	oStages[0].mName = "Decompose";
	oStages[0].mDescription = NULL;

	*stagesOut = oStages;
	return 1;
}
