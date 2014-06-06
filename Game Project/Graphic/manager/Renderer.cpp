
#include "stdafx.h"
#include "Renderer.h"
#include "../base/DxInit.h"
#include "resourcemanager.h"

using namespace graphic;


// 렌더러 초기화.
bool graphic::InitRenderer(HWND hWnd, const int width, const int height)
{
	if (!cRenderer::Get()->CreateDirectX(hWnd, width, height))
		return false;

	return true;
}

void graphic::ReleaseRenderer()
{
	cRenderer::Release();
	cResourceManager::Release();
}



////////////////////////////////////////////////////////////////////////////////////////////////
// Renderer

cRenderer::cRenderer()
{

}

cRenderer::~cRenderer()
{

}


// DirectX Device 객체 생성.
bool cRenderer::CreateDirectX(HWND hWnd, const int width, const int height)
{
	if (!InitDirectX(hWnd, width, height, m_pDevice))
		return false;

	return true;
}


// x, y, z 축을 출력한다.
void cRenderer::RenderAxis()
{
	RET(!m_pDevice);

	m_pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

	Matrix44 identity;
	m_pDevice->SetTransform( D3DTS_WORLD, (D3DXMATRIX*)&identity );

	const float length = 500.f;
	const int axis_size = 6;
	sVertexDiffuse axisLine[ axis_size];

	// x axis
	axisLine[ 0].p = Vector3( 0.f, 0.f, 0.f );
	axisLine[ 1].p = Vector3( length, 0.f, 0.f );
	axisLine[ 0].c = D3DXCOLOR( 1, 0, 0, 0 );
	axisLine[ 1].c = D3DXCOLOR( 1, 0, 0, 0 );
	// y axis
	axisLine[ 2].p = Vector3( 0.f, 0.f, 0.f );
	axisLine[ 3].p = Vector3( 0.f, length, 0.f );
	axisLine[ 2].c = D3DXCOLOR( 0, 1, 0, 0 );
	axisLine[ 3].c = D3DXCOLOR( 0, 1, 0, 0 );
	// z axis
	axisLine[ 4].p = Vector3( 0.f, 0.f, 0.f );
	axisLine[ 5].p = Vector3( 0.f, 0.f, length );
	axisLine[ 4].c = D3DXCOLOR( 0, 0, 1, 0 );
	axisLine[ 5].c = D3DXCOLOR( 0, 0, 1, 0 );
	m_pDevice->SetFVF( sVertexDiffuse::FVF );
	m_pDevice->DrawPrimitiveUP( D3DPT_LINELIST, axis_size/2, axisLine, sizeof(sVertexDiffuse) );


	const float w = 5.f;
	sVertexDiffuse tri[ 9];
	tri[ 0].p = Vector3( 0.f, 0.f, 0.f );
	tri[ 0].c = D3DXCOLOR( 1, 0, 0, 0 );
	tri[ 2].p = Vector3( w*2, 0.f, 0.f );
	tri[ 2].c = D3DXCOLOR( 0, 1, 0, 0 );
	tri[ 1].p = Vector3( w, w, 0.f );
	tri[ 1].c = D3DXCOLOR( 0, 0, 1, 0 );

	tri[ 3].p = Vector3( 0.f, 0.f, 0.f );
	tri[ 3].c = D3DXCOLOR( 1, 0, 0, 0 );
	tri[ 5].p = Vector3( -w, w, 0.f );
	tri[ 5].c = D3DXCOLOR( 0, 0, 1, 0 );
	tri[ 4].p = Vector3( -w*w, 0.f, 0.f );
	tri[ 4].c = D3DXCOLOR( 0, 1, 0, 0 );

	tri[ 6].p = Vector3( 0.f, 0.f, 0.f );
	tri[ 6].c = D3DXCOLOR( 1, 0, 0, 0 );
	tri[ 8].p = Vector3( w, w, 0.f );
	tri[ 8].c = D3DXCOLOR( 0, 1, 0, 0 );
	tri[ 7].p = Vector3( -w, w, 0.f );
	tri[ 7].c = D3DXCOLOR( 0, 0, 1, 0 );
	m_pDevice->SetFVF( sVertexDiffuse::FVF );
	m_pDevice->DrawPrimitiveUP( D3DPT_TRIANGLELIST, 3, tri, sizeof(sVertexDiffuse) );

	m_pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}
