
#include "stdafx.h"
#include "mesh.h"

using namespace graphic;


cMesh::cMesh(const int id, const sRawMesh &raw) : 
	cNode(id)
,	m_track(NULL)
,	m_aniTime(0)
,	m_aniStart(0)
,	m_aniEnd(0)
,	m_aniFrame(0)
{
	// 버텍스 버퍼 생성.
	if (m_vtxBuff.Create(raw.vertices.size(), sizeof(sVertexNormTex), sVertexNormTex::FVF))
	{
		sVertexNormTex* vertices = (sVertexNormTex*)m_vtxBuff.Lock();
		for (u_int i = 0; i < raw.vertices.size(); i++)
		{
			vertices[ i].p = raw.vertices[ i];
			vertices[ i].n = raw.normals[ i];
		}
		m_vtxBuff.Unlock();
	}

	// 인덱스 버퍼 생성.
	if (m_idxBuff.Create(raw.indices.size()))
	{
		WORD *indices = (WORD*)m_idxBuff.Lock();
		for (u_int i = 0; i < raw.indices.size(); ++i)
			indices[ i] = raw.indices[ i];
		m_idxBuff.Unlock();
	}

	m_mtrl.InitWhite();
}

cMesh::~cMesh()
{
	SAFE_DELETE(m_track);
}


// Animation
bool cMesh::Move(const float elapseTime)
{
	RETV(!m_track, false);

	//  프레임 단위로 변환한다.
	m_aniTime += elapseTime;
	m_aniFrame = (int)(m_aniTime * 30.f);

	if (m_aniFrame > m_aniEnd)
	{
		m_aniTime = m_aniStart * 30.f;
		m_aniFrame = m_aniStart;
		m_track->InitAnimation();
	}

	m_aniTM.SetIdentity();
	m_track->Move(m_aniFrame, m_aniTM);
	return true;
}


// Render
void cMesh::Render(const Matrix44 &parentTm)
{
	m_mtrl.Bind();
	m_vtxBuff.Bind();
	m_idxBuff.Bind();

	const Matrix44 tm = m_aniTM * m_TM * m_localTM * parentTm;
	//GetDevice()->MultiplyTransform( D3DTS_WORLD, (D3DXMATRIX*)&tm );
	GetDevice()->SetTransform( D3DTS_WORLD, (D3DXMATRIX*)&tm );
	GetDevice()->DrawIndexedPrimitive( 
		D3DPT_TRIANGLELIST, 0, 0, 
		m_vtxBuff.GetVertexCount(), 0, m_idxBuff.GetFaceCount());
}


// Render Bounding Box
void cMesh::RenderBBox()
{

}


// Load Animation
void cMesh::LoadAnimation( const sRawAni &rawAni )
{
	SAFE_DELETE(m_track);

	m_track = new cTrack(rawAni);
	m_aniStart = (int)rawAni.start;
	m_aniEnd = (int)rawAni.end;
	m_aniFrame = (int)rawAni.start;
}
