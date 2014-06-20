
#pragma once
#include "afxcmn.h"


class CModelView;
class CViewer2Dlg : public CDialogEx
{
public:
	CViewer2Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	virtual ~CViewer2Dlg();
	enum { IDD = IDD_VIEWER2_DIALOG };

	void MainLoop();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	CModelView *m_pView;
	bool m_loop;
	bool m_dxInit;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnItemchangedFileList(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_FileList;
	afx_msg void OnDropFiles(HDROP hDropInfo);
	BOOL m_WireFrame;
	afx_msg void OnBnClickedCheckWireframe();
};
