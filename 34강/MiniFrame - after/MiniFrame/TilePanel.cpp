// TilePanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MiniFrame.h"
#include "TilePanel.h"
#include "afxdialogex.h"


// CTilePanel 대화 상자입니다.
CTilePanel::CTilePanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTilePanel::IDD, pParent)
{

}

CTilePanel::~CTilePanel()
{
}

void CTilePanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTilePanel, CDialogEx)
END_MESSAGE_MAP()


// CTilePanel 메시지 처리기입니다.
