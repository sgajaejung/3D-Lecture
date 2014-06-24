// TerrainPanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MiniFrame.h"
#include "TerrainPanel.h"
#include "afxdialogex.h"


// CTerrainPanel 대화 상자입니다.

CTerrainPanel::CTerrainPanel(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTerrainPanel::IDD, pParent)
{

}

CTerrainPanel::~CTerrainPanel()
{
}

void CTerrainPanel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTerrainPanel, CDialogEx)
END_MESSAGE_MAP()


// CTerrainPanel 메시지 처리기입니다.
