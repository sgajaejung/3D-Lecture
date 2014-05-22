
#pragma once


class cGameApp : public framework::cGameMain
{
public:
	cGameApp();
	virtual ~cGameApp();

	virtual bool OnInit() override;
	virtual void OnUpdate(const float elapseT) override;
	virtual void OnRender(const float elapseT) override;
	virtual void OnShutdown() override;
	virtual void MessageProc( UINT message, WPARAM wParam, LPARAM lParam) override;


protected:
	bool ReadModelFile( const string &fileName, 
		LPDIRECT3DVERTEXBUFFER9 &vtxBuff, int &vtxSize,  
		LPDIRECT3DINDEXBUFFER9 &idxBuff, int &faceSize );

	void ComputeNormals(LPDIRECT3DVERTEXBUFFER9 vtxBuff, int vtxSize,  
		LPDIRECT3DINDEXBUFFER9 idxBuff, int faceSize);


private:
	LPDIRECT3DVERTEXBUFFER9 m_pVB; // 버텍스 버퍼
	LPDIRECT3DINDEXBUFFER9 m_pIB; // 인덱스 버퍼
	int m_VtxSize;
	int m_FaceSize;
	//D3DMATERIAL9 m_Mtrl;
	graphic::cMaterial m_mtrl;

	D3DLIGHT9 m_Light;
};
