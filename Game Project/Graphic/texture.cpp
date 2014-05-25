
#include "stdafx.h"
#include "texture.h"


using namespace graphic;


cTexture::cTexture() :
	m_texture(NULL)
{

}

cTexture::~cTexture()
{
	SAFE_RELEASE(m_texture);

}


void cTexture::Create(const string &fileName)
{
	D3DXCreateTextureFromFileA(GetDevice(), fileName.c_str(), &m_texture);
}


void cTexture::Bind(int stage)
{
	GetDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	GetDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
	GetDevice()->SetTexture(stage, m_texture);
}
