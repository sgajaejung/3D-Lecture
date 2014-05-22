
#include "stdafx.h"
#include "indexbuffer.h"

using namespace graphic;


cIndexBuffer::cIndexBuffer() :
	m_pIdxBuff(NULL)
{

}

cIndexBuffer::~cIndexBuffer()
{
	if (m_pIdxBuff)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
}


bool cIndexBuffer::Create(int faceCount)
{
	if (FAILED(graphic::GetDevice()->CreateIndexBuffer(faceCount*3*sizeof(WORD), 
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff, NULL)))
	{
		return false;
	}

	return true;
}


void* cIndexBuffer::Lock()
{
	WORD *indices = NULL;
	m_pIdxBuff->Lock(0, 0, (void**)&indices, 0);
	return indices;
}


void cIndexBuffer::Unlock()
{
	m_pIdxBuff->Unlock();
}


void cIndexBuffer::Bind() const
{
	GetDevice()->SetIndices(m_pIdxBuff);
}

