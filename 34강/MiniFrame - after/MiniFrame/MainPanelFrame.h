#pragma once


// CMainPanel 프레임입니다.

class CMainPanelFrame : public CMiniFrameWnd
{
public:
	CMainPanelFrame();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CMainPanelFrame();
	void Init();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


