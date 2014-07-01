
#pragma once


class cSkyBox
{
public:
	cSkyBox();
	virtual ~cSkyBox();

	BOOL Init(const string &textureFilePath);
	void Update(int elapseTime);
	void Render();
	void Clear();


protected:
	BOOL CreateVertexBuffer();	
	void SetRenderState();


private:
	enum {FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM, MAX_FACE};
	IDirect3DVertexBuffer9 *m_pVtxBuffer;
	graphic::cTexture m_textures[ MAX_FACE];
};
