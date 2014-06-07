
#include "stdafx.h"
#include "model.h"
#include "node.h"
#include "../manager/resourcemanager.h"
#include "mesh.h"


using namespace graphic;


cModel::cModel()
{
	
}

cModel::~cModel()
{
	Clear();
}


bool cModel::Create(const string &modelName)
{
	sRawMeshGroup *rawMeshes = cResourceManager::Get()->LoadModel(modelName);
	RETV(!rawMeshes, false);

	Clear();

	//LoadSkeletone(*rawMeshes);

	BOOST_FOREACH (auto &mesh, rawMeshes->meshes)
	{
		cMesh *p = new cMesh(0, mesh);
		if (sRawAni *rawAni = cResourceManager::Get()->FindAni(modelName))
		{
			p->LoadAnimation(*rawAni);
		}
		m_meshes.push_back(p);
	}

	return true;
}


// 뼈대 메쉬를 화면에 출력한다.
void cModel::LoadSkeletone(const sRawMeshGroup &rawMeshes)
{
	BOOST_FOREACH (auto &bone, rawMeshes.bones)
	{
		cMesh *p = new cMesh(0, bone);

		Matrix44 w = bone.worldTm;
		Matrix44 iw = w.Inverse();
		Matrix44 tm = iw;
		p->SetLocalTM(tm);
		m_meshes.push_back(p);
	}
}


bool cModel::Move(const float elapseTime)
{
	BOOST_FOREACH (auto node, m_meshes)
		return node->Move(elapseTime);
	return true;
}


void cModel::Render()
{
	Matrix44 identity;
	GetDevice()->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&identity);

	BOOST_FOREACH (auto node, m_meshes)
		node->Render(m_matTM);
}


// remove all data
void cModel::Clear()
{
	BOOST_FOREACH (auto mesh, m_meshes)
	{
		SAFE_DELETE(mesh);
	}
	m_meshes.clear();
}
