
#include "stdafx.h"
#include "resourcemanager.h"
#include "../importer/modelimporter.h"


using namespace graphic;


cResourceManager::cResourceManager()
{

}

cResourceManager::~cResourceManager()
{
	Clear();
}


// load model file
sRawMesh* cResourceManager::LoadModel( const string &fileName )
{
	if (sRawMesh *data = FindModel(fileName))
		return data;

	sRawMesh *mesh = new sRawMesh;
	mesh->name = fileName;
	sRawAni *ani = new sRawAni;
	ani->name = fileName;

	if (!importer::ReadRawMeshFile(fileName, *mesh, *ani))
	{
		delete mesh;
		delete ani;
		return NULL;
	}

	// store
	m_meshes[ fileName] = mesh;
	m_anies[ fileName] = ani;
	return m_meshes[ fileName];
}


// find model data
sRawMesh* cResourceManager::FindModel( const string &fileName )
{
	auto it = m_meshes.find(fileName);
	if (m_meshes.end() == it)
		return NULL; // not exist
	return it->second;
}


// find animation data
sRawAni* cResourceManager::FindAni( const string &fileName )
{
	auto it = m_anies.find(fileName);
	if (m_anies.end() == it)
		return NULL; // not exist
	return it->second;
}


// remove all data
void cResourceManager::Clear()
{
	// remove raw mesh
	BOOST_FOREACH (auto kv, m_meshes)
	{
		delete kv.second;
	}
	m_meshes.clear();

	// remove texture
	BOOST_FOREACH (auto kv, m_textures)
	{
		delete kv.second;
	}
	m_textures.clear();

	// remove raw ani
	BOOST_FOREACH (auto kv, m_anies)
	{
		delete kv.second;
	}
	m_anies.clear();

}
