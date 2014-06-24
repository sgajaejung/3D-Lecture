#pragma once
#include "afxcmn.h"


// CMainPanel 대화 상자입니다.
class CTerrainPanel;
class CTilePanel;
class CMainPanel : public CDialogEx
{
public:
	CMainPanel(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMainPanel();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_MAINPANEL };

	CTerrainPanel *m_pTerrainPanel;
	CTilePanel *m_pTilePanel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CTabCtrl m_Tab;
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
};
