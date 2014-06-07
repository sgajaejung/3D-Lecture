
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

cRenderer::cRenderer() :
	m_pDevice(NULL)
,	m_font(NULL)
,	m_elapseTime(0)
,	m_fps(0)
{
	m_fpsText = "fps : 0";

}

cRenderer::~cRenderer()
{
	SAFE_RELEASE(m_font);
	SAFE_RELEASE(m_pDevice);
}


// DirectX Device 객체 생성.
bool cRenderer::CreateDirectX(HWND hWnd, const int width, const int height)
{
	if (!InitDirectX(hWnd, width, height, m_pDevice))
		return false;

	HRESULT hr = D3DXCreateFontA( m_pDevice, 18, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, 
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "굴림", &m_font );
	if (FAILED(hr))
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


// FPS 출력.
void cRenderer::RenderFPS()
{
	RET(!m_font);

	RECT rc = {10,10,200,200};
	m_font->DrawTextA( NULL, m_fpsText.c_str(), -1, &rc,
		DT_NOCLIP, D3DXCOLOR( 0.0f, 0.0f, 1.0f, 1.0f ) );
}


// 그리드 출력.
void cRenderer::RenderGrid()
{
	static int gridSize = 0;
	if (m_grid.empty())
	{
		MakeGrid(50, 20, D3DXCOLOR(0.8f,0.8f,0.8f,1), m_grid);
		gridSize = m_grid.size() / 2;
	}

	if (gridSize > 0)
	{
		m_pDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
		Matrix44 identity;
		m_pDevice->SetTransform( D3DTS_WORLD, (D3DXMATRIX*)&identity );
		m_pDevice->SetFVF( sVertexDiffuse::FVF );
		m_pDevice->DrawPrimitiveUP( D3DPT_LINELIST, gridSize, &m_grid[0], sizeof(sVertexDiffuse) );
		m_pDevice->SetRenderState( D3DRS_LIGHTING, TRUE);
	}
}



void cRenderer::Update(const float elapseT)
{
	// fps 계산 ---------------------------------------
	++m_fps;
	m_elapseTime += elapseT;
	if( 1.f <= m_elapseTime )
	{
		m_fpsText = format("fps: %d", m_fps );
		m_fps = 0;
		m_elapseTime = 0;
	}
	//--------------------------------------------------
}


// 격자무늬 버텍스를 만든다. 
// width = 격자 하나의 폭 크기 (정 사각형이므로 인자값은 하나만 받는다)
// count = 격자 가로 세로 갯수
void cRenderer::MakeGrid( const float width, const int count, DWORD color, vector<sVertexDiffuse> &out )
{
	if (out.empty())
	{
		out.reserve(count * 4);
		const Vector3 start(count/2 * -width, 0, count/2 * width);

		for (int i=0; i < count+1; ++i)
		{
			sVertexDiffuse vtx;
			vtx.p = start;
			vtx.p.x += (i * width);
			vtx.c = color;
			out.push_back(vtx);

			vtx.p += Vector3(0,0,-width*count);
			out.push_back(vtx);
		}

		for (int i=0; i < count+1; ++i)
		{
			sVertexDiffuse vtx;
			vtx.p = start;
			vtx.p.z -= (i * width);
			vtx.c = color;
			out.push_back(vtx);

			vtx.p += Vector3(width*count,0,0);
			out.push_back(vtx);
		}
	}
}
