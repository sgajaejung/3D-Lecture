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
		Matrix44 localTm; // only bone
		Matrix44 worldTm; // only bone
	};


	struct sRawMeshGroup
	{
		string name;
		vector<sRawMesh> meshes;
		vector<sRawMesh> bones;
	};

}
