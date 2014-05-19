
#include "stdafx.h"
#include "GameMain.h"
#include <MMSystem.h>
#include "../window/utility.h"


using namespace framework;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//------------------------------------------------------------------------
// WindowMain 함수
//------------------------------------------------------------------------
int framework::FrameWorkWinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPSTR lpCmdLine, 
	int nCmdShow)
{
	const HWND hWnd = InitWindow(hInstance, 
		cGameMain::Get()->GetWindowName(), 
		cGameMain::Get()->GetWindowRect(), 
		nCmdShow,
		WndProc);

	if (hWnd == NULL)
		return 0;

	cGameMain::Get()->Init(hWnd);
	cGameMain::Get()->Run();
	cGameMain::Get()->ShutDown();
	return 0;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	cGameMain::Get()->MessageProc(message, wParam, lParam);

	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		case VK_RETURN:
			break;
		}
		break;

	case WM_DESTROY:
		cGameMain::Get()->ShutDown();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}




/////////////////////////////////////////////////////////////////////////////////////////////
cGameMain *cGameMain::m_pInstance = NULL;
cGameMain::cGameMain()
{

}


cGameMain::~cGameMain()
{

}

// singleton function
cGameMain* cGameMain::Get()
{
	if (!m_pInstance)
		m_pInstance = CreateFrameWork();
	return m_pInstance;
}


void cGameMain::Init(HWND hWnd)
{
	m_state = INIT;
	m_hWnd = hWnd;
}


void cGameMain::ShutDown()
{
	m_state = SHUTDOWN;
}


void cGameMain::Run()
{
	m_state = RUN; // Framework 실행

	MSG msg;
	while (RUN == m_state)
	{
		if (PeekMessage( &msg, m_hWnd, 0, 0, PM_NOREMOVE ))
		{
			GetMessage(&msg, NULL, 0, 0);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		const int curT = timeGetTime();
		static int oldT = curT;
		const int elapseT = curT - oldT;
		const float t = elapseT * 0.001f;
		oldT = curT;

		Update(t);
		Render(t);
	}
}


void cGameMain::Update(const float elapseT)
{

}


void cGameMain::Render(const float elapseT)
{

}


void	cGameMain::MessageProc( UINT message, WPARAM wParam, LPARAM lParam)
{

}


const string& cGameMain::GetWindowName()
{
	return m_windowName;
}
const RECT& cGameMain::GetWindowRect()
{
	return m_windowRect;
}
