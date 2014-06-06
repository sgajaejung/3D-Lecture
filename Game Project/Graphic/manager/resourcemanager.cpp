
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

	sRawMesh raw;
	if (!ReadRawMeshFile(fileName, raw))
		return NULL;

	// store
	m_meshes[ fileName] = new sRawMesh;
	*m_meshes[ fileName] = raw;
	return NULL;
}


// find model
sRawMesh* cResourceManager::FindModel( const string &fileName )
{
	auto it = m_meshes.find(fileName);
	if (m_meshes.end() == it)
		return NULL; // not exist
	return it->second;
}


// remove all data
void cResourceManager::Clear()
{
	BOOST_FOREACH (auto kv, m_meshes)
	{
		delete kv.second;
	}
	m_meshes.clear();
}
