#pragma once


// CTilePanel 대화 상자입니다.

class CTilePanel : public CDialogEx
{
public:
	CTilePanel(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTilePanel();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_TILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
