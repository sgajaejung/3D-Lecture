#pragma once


namespace graphic
{
	
	struct sRawMesh
	{
		vector<Vector3> vertices;
		vector<Vector3> normals;
		vector<int> indices;
		string texturePath;
	};

}
