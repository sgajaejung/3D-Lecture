
// Viewer2Dlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"


class CModelView;
// CViewer2Dlg 대화 상자
class CViewer2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CViewer2Dlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_VIEWER2_DIALOG };

	void MainLoop();



protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;
	bool m_loop;
	CModelView *m_pModelView;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	CListCtrl m_FileList;
	afx_msg void OnKeydownFileList(NMHDR *pNMHDR, LRESULT *pResult);
};
