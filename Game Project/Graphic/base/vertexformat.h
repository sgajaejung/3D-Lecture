#pragma once


namespace graphic
{

	struct sVertexNormTex
	{
		Vector3 p;
		Vector3 n;
		float u,v;

		static const DWORD FVF;
	};
}
