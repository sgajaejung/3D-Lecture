#pragma once

namespace graphic 
{

	namespace importer 
	{

		bool ReadRawMeshFile( const string &fileName, 
			OUT sRawMeshGroup &raw, OUT sRawAniGroup &rawAnies );

	}
}
