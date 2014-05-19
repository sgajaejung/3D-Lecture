
#include "stdafx.h"
#include "GameApp.h"

INIT_FRAMEWORK(cGameApp)


cGameApp::cGameApp()
{
	m_windowName = "test";
	const RECT r = {0, 0, 800, 600};
	m_windowRect = r;
}

cGameApp::~cGameApp()
{

}

