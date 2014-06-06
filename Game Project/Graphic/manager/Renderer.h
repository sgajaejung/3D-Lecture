#pragma once

namespace graphic
{

	class cRenderer : public common::cSingleton<cRenderer>
	{
	public:
		cRenderer();
		virtual ~cRenderer();

		bool CreateDirectX(HWND hWnd, const int width, const int height);
		LPDIRECT3DDEVICE9 GetDevice() { return m_pDevice; }
		void RenderAxis();


	protected:


	private:
		LPDIRECT3DDEVICE9 m_pDevice;
	};


	// 렌더러 초기화.
	bool InitRenderer(HWND hWnd, const int width, const int height);
	void ReleaseRenderer();
	inline cRenderer* GetRenderer() { return cRenderer::Get(); }
	inline LPDIRECT3DDEVICE9 GetDevice() { return cRenderer::Get()->GetDevice(); }
}
