// CrossControlDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "VectorCalc.h"
#include "CrossControlDlg.h"
#include "afxdialogex.h"


// CCrossControlDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CCrossControlDlg, CDialogEx)

CCrossControlDlg::CCrossControlDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCrossControlDlg::IDD, pParent)
{

}

CCrossControlDlg::~CCrossControlDlg()
{
}

void CCrossControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCrossControlDlg, CDialogEx)
END_MESSAGE_MAP()


// CCrossControlDlg 메시지 처리기입니다.
