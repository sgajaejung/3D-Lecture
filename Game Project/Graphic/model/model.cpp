
#include "stdafx.h"
#include "model.h"
#include "node.h"
#include "../manager/resourcemanager.h"
#include "mesh.h"


using namespace graphic;


cModel::cModel() :
	m_root(NULL)
{
	
}

cModel::~cModel()
{
	Clear();
}


bool cModel::Create(const string &modelName)
{
	sRawMesh *raw = cResourceManager::Get()->LoadModel(modelName);
	RETV(!raw, false);

	SAFE_DELETE(m_root);
	m_root = new cMesh(0, *raw);

	return true;
}


bool cModel::Move(const float elapseTime)
{
	RETV(!m_root, false);
	return m_root->Move(elapseTime);
}


void cModel::Render()
{
	RET(!m_root);
	
	Matrix44 identity;
	GetDevice()->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&identity);

	m_root->Render(m_matTM);
}


// remove all data
void cModel::Clear()
{
	SAFE_DELETE(m_root);
}
