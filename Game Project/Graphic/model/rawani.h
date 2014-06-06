#pragma once


namespace graphic
{

	struct sKeyPos
	{
		float t;
		Vector3 p;
	};


	struct sKeyScale
	{
		float t;
		Vector3 s;
	};


	struct sKeyRot
	{
		float t;
		Quaternion q;
	};


	struct sRawAni
	{
		string name;
		vector<sKeyPos> pos;
		vector<sKeyRot> rot;
		vector<sKeyScale> scale;
	};

}
