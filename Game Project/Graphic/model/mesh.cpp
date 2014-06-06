
#include "stdafx.h"
#include "mesh.h"

using namespace graphic;


cMesh::cMesh(const int id) : cNode(id)
{

}

cMesh::~cMesh()
{

}


bool cMesh::Move(const float elapseTime)
{

	return true;
}


void cMesh::Render()
{
	m_vtxBuff.Bind();
	m_idxBuff.Bind();
}


void cMesh::RenderBBox()
{

}
