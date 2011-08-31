

#ifndef LL_CONVEX_DECOMP_UTIL_H
#define LL_CONVEX_DECOMP_UTIL_H

#include "LLConvexDecomposition.h"

class NDConvexDecompositionHACD : public LLConvexDecomposition
{
	public:

		virtual ~NDConvexDecompositionHACD() {}

		static LLConvexDecomposition* getInstance();
		static LLCDResult initSystem();
		static LLCDResult initThread();
		static LLCDResult quitThread();
		static LLCDResult quitSystem();

		// Generate a decomposition object handle
		void genDecomposition(int& decomp);
		// Delete decomposition object handle
		void deleteDecomposition(int decomp);
		// Bind given decomposition handle
		// Commands operate on currently bound decomposition
		void bindDecomposition(int decomp);

		// Sets *paramsOut to the address of the LLCDParam array and returns
		// the length of the array
		int getParameters(const LLCDParam** paramsOut) 
		{ 
			*paramsOut = NULL; 
			return 0; 
		}

		int getStages(const LLCDStageData** stagesOut) 
		{ 
			*stagesOut = NULL; 
			return 0; 
		}

		// Set a parameter by name. Returns false if out of bounds or unsupported parameter
		LLCDResult	setParam(const char* name, float val);
		LLCDResult	setParam(const char* name, int val);
		LLCDResult	setParam(const char* name, bool val);
		LLCDResult	setMeshData( const LLCDMeshData* data, bool vertex_based );
		LLCDResult	registerCallback(int stage, llcdCallbackFunc callback );

		LLCDResult	executeStage(int stage);
		LLCDResult	buildSingleHull() ;

		int getNumHullsFromStage(int stage);

		LLCDResult	getHullFromStage( int stage, int hull, LLCDHull* hullOut );
		LLCDResult  getSingleHull( LLCDHull* hullOut ) ;
		
		// TODO: Implement lock of some kind to disallow this call if data not yet ready
		LLCDResult	getMeshFromStage( int stage, int hull, LLCDMeshData* meshDataOut);
		LLCDResult	getMeshFromHull( LLCDHull* hullIn, LLCDMeshData* meshOut );

		// For visualizing convex hull shapes in the viewer physics shape display
		LLCDResult generateSingleHullMeshFromMesh( LLCDMeshData* meshIn, LLCDMeshData* meshOut);

		/// Debug
		void loadMeshData(const char* fileIn, LLCDMeshData** meshDataOut);

	private:
		NDConvexDecompositionHACD() {}
};

#endif //LL_CONVEX_DECOMP_UTIL_H
