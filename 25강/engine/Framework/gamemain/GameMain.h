
#pragma once


namespace framework
{

	class cGameMain
	{
	public:
		cGameMain();
		virtual ~cGameMain();
		
		enum STATE
		{
			INIT,
			RUN,
			SHUTDOWN,
		};

		virtual bool Init(HWND hWnd);
		virtual void ShutDown();
		virtual void Run();
		virtual void Update(const float elapseT);
		virtual void Render(const float elapseT);
		virtual void Exit();

		const wstring& GetWindowName();
		const RECT& GetWindowRect();		
		virtual void MessageProc( UINT message, WPARAM wParam, LPARAM lParam);


	protected:
		virtual bool OnInit() { return true; }
		virtual void OnUpdate(const float elapseT) {}
		virtual void OnRender(const float elapseT) {}
		virtual void OnShutdown() {}


	protected:
		STATE m_state;
		HWND m_hWnd;
		wstring m_windowName;
		RECT m_windowRect;


	// singleton
	protected:
		static cGameMain* m_pInstance;
	public:
		static cGameMain* Get();
		static void Release();
	};


	// 프레임워크 매인 함수.
	int FrameWorkWinMain(HINSTANCE hInstance, 
		HINSTANCE hPrevInstance, 
		LPSTR lpCmdLine, 
		int nCmdShow);

	// 프레임워크 인스턴스를 생성한다. 반드시 이 함수를 구현해야 한다.
	cGameMain* CreateFrameWork();
}
