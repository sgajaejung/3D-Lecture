
#include "stdafx.h"
#include "skinnedmesh.h"

using namespace graphic;


cSkinnedMesh::cSkinnedMesh(const int id, const vector<Matrix44> &palette, const sRawMesh &raw) : 
	cMesh(id, raw)
,	m_palette(palette)
{

}

cSkinnedMesh::~cSkinnedMesh()
{

}


void cSkinnedMesh::Render(const Matrix44 &parentTm)
{

}


// ÆÈ·¹Æ® Àû¿ë.
void cSkinnedMesh::ApplyPalette()
{

}
