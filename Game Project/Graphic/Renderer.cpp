
#include "stdafx.h"
#include "Renderer.h"
#include "DxInit.h"

using namespace graphic;


// ·»´õ·¯ ÃÊ±âÈ­.
bool graphic::InitRenderer(HWND hWnd, const int width, const int height)
{
	if (!cRenderer::Get()->CreateDirectX(hWnd, width, height))
		return false;

	return true;
}

void graphic::ReleaseRenderer()
{
	cRenderer::Release();
}

cRenderer* graphic::GetRenderer()
{
	return cRenderer::Get();
}

LPDIRECT3DDEVICE9 graphic::GetDevice()
{
	return cRenderer::Get()->GetDevice();
}



////////////////////////////////////////////////////////////////////////////////////////////////
// Renderer

cRenderer::cRenderer()
{

}

cRenderer::~cRenderer()
{

}


// DirectX Device °´Ã¼ »ý¼º.
bool cRenderer::CreateDirectX(HWND hWnd, const int width, const int height)
{
	if (!InitDirectX(hWnd, width, height, m_DxDevice))
		return false;

	return true;
}

