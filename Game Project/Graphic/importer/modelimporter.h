#pragma once

namespace graphic 
{
	struct sRawMesh;

	namespace importer 
	{

		bool ReadRawMeshFile( const string &fileName, 
			OUT sRawMesh &raw, OUT sRawAni &rawAni );

	}
}
