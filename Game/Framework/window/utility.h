
#pragma once


namespace framework
{

	// 윈도우 생성
	HWND InitWindow(HINSTANCE hInstance, 
		const string &windowName, 
		const RECT &windowRect,
		int nCmdShow,
		WNDPROC WndProc);

}
