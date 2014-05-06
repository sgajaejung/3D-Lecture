// EditVector4.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MatrixCalc.h"
#include "EditVector4.h"
#include "afxdialogex.h"


// CEditVector4 대화 상자입니다.

//IMPLEMENT_DYNAMIC(CEditVector4, CDialogEx)

CEditVector4::CEditVector4(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEditVector4::IDD, pParent)
{

}

CEditVector4::~CEditVector4()
{
}

void CEditVector4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CEditVector4, CDialogEx)
END_MESSAGE_MAP()


// CEditVector4 메시지 처리기입니다.
