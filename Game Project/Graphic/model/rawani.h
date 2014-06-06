#pragma once


namespace graphic
{

	struct sKeyPos
	{
		float t; // frame 단위
		Vector3 p;
	};


	struct sKeyScale
	{
		float t; // frame 단위
		Vector3 s;
	};


	struct sKeyRot
	{
		float t; // frame 단위
		Quaternion q;
	};


	struct sRawAni
	{
		string name;
		float start; // frame 단위
		float end; // frame 단위
		vector<sKeyPos> pos;
		vector<sKeyRot> rot;
		vector<sKeyScale> scale;
	};

}
