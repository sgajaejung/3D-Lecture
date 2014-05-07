#pragma once


// CCrossControlDlg 대화 상자입니다.

class CCrossControlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCrossControlDlg)

public:
	CCrossControlDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CCrossControlDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CROSS_CONTROL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
