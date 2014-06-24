// BoxDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MiniFrame.h"
#include "BoxDlg.h"
#include "afxdialogex.h"


// CBoxDlg 대화 상자입니다.

CBoxDlg::CBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CBoxDlg::IDD, pParent)
{

}

CBoxDlg::~CBoxDlg()
{
}

void CBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBoxDlg, CDialogEx)
END_MESSAGE_MAP()


// CBoxDlg 메시지 처리기입니다.
