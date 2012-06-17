#include "llpathinglib.h"

void LLPathingLib::initSystem()
{
}

LLPathingLib* LLPathingLib::getInstance()
{
	static LLPathingLib sObj;
	return &sObj;
}

void LLPathingLib::extractNavMeshSrcFromLLSD( std::vector< unsigned char > const &aMeshData, int aNavigation )
{
}

LLPathingLib::LLPLResult LLPathingLib::generatePath( PathingPacket const& )
{
	return LLPL_NO_PATH;
}

void LLPathingLib::cleanupResidual()
{
}

// void LLPathingLib::setRenderWorld( bool aRender )
// {
// }

void LLPathingLib::stitchNavMeshes( )
{
}

void LLPathingLib::renderNavMesh( void )
{
}

void LLPathingLib::renderNavMeshShapesVBO( unsigned int aShapeTypeBitmask )
{
}

void LLPathingLib::renderPath()
{
}

void LLPathingLib::cleanupVBOManager()
{
}

void LLPathingLib::setNavMeshColors( NavMeshColors const &aColors )
{
}

void LLPathingLib::setNavMeshMaterialType( LLPLCharacterType aType )
{
}

void LLPathingLib::renderNavMeshEdges()
{
}

void LLPathingLib::renderPathBookend( LLRender&, LLPLRenderType )
{
}

void LLPathingLib::renderSimpleShapes( LLRender&, float )
{
}

void LLPathingLib::createPhysicsCapsuleRep( float, float, bool, LLVector3 const, LLUUID const& )
{
}

void LLPathingLib::cleanupPhysicsCapsuleRepResiduals()
{
}

void LLPathingLib::processNavMeshData()
{
}

void LLPathingLib::renderSimpleShapeCapsuleID( LLRender&, LLUUID const&, LLVector3 const&, LLQuaternion const& )
{
}
