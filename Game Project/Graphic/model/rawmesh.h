#pragma once


namespace graphic
{
	struct sRawMesh
	{
		string name;
		vector<Vector3> vertices;
		vector<Vector3> normals;
		vector<Vector3> tex;
		vector<int> indices;
		string texturePath;
	};

}
