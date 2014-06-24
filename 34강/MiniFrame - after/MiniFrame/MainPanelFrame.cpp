// MainPanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MiniFrame.h"
#include "MainPanelFrame.h"
#include "MainPanel.h"


// CMainPanel

CMainPanelFrame::CMainPanelFrame()
{
	
}

CMainPanelFrame::~CMainPanelFrame()
{
}


BEGIN_MESSAGE_MAP(CMainPanelFrame, CMiniFrameWnd)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMainPanel 메시지 처리기입니다.
void CMainPanelFrame::Init()
{
	CMainPanel *panel = new CMainPanel();
	panel->Create(CMainPanel::IDD, this);
	panel->ShowWindow(SW_SHOW);

}


void CMainPanelFrame::OnSize(UINT nType, int cx, int cy)
{
	CMiniFrameWnd::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
