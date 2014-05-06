// EditMatrix4x4.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MatrixCalc.h"
#include "EditMatrix4x4.h"
#include "afxdialogex.h"


// CEditMatrix4x4 대화 상자입니다.

IMPLEMENT_DYNAMIC(CEditMatrix4x4, CDialogEx)

CEditMatrix4x4::CEditMatrix4x4(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEditMatrix4x4::IDD, pParent)
	, m_11(0)
	, m_12(0)
	, m_13(0)
	, m_14(0)
	, m_21(0)
	, m_22(0)
	, m_23(0)
	, m_24(0)
	, m_31(0)
	, m_32(0)
	, m_33(0)
	, m_34(0)
	, m_41(0)
	, m_42(0)
	, m_43(0)
	, m_44(0)
{

}

CEditMatrix4x4::~CEditMatrix4x4()
{
}

void CEditMatrix4x4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_11);
	DDX_Text(pDX, IDC_EDIT2, m_12);
	DDX_Text(pDX, IDC_EDIT3, m_13);
	DDX_Text(pDX, IDC_EDIT4, m_14);

	DDX_Text(pDX, IDC_EDIT5, m_21);
	DDX_Text(pDX, IDC_EDIT6, m_22);
	DDX_Text(pDX, IDC_EDIT7, m_23);
	DDX_Text(pDX, IDC_EDIT8, m_24);

	DDX_Text(pDX, IDC_EDIT9, m_31);
	DDX_Text(pDX, IDC_EDIT10, m_32);
	DDX_Text(pDX, IDC_EDIT11, m_33);
	DDX_Text(pDX, IDC_EDIT12, m_34);

	DDX_Text(pDX, IDC_EDIT13, m_41);
	DDX_Text(pDX, IDC_EDIT14, m_42);
	DDX_Text(pDX, IDC_EDIT15, m_43);
	DDX_Text(pDX, IDC_EDIT16, m_44);

}


BEGIN_MESSAGE_MAP(CEditMatrix4x4, CDialogEx)
END_MESSAGE_MAP()


// CEditMatrix4x4 메시지 처리기입니다.
void CEditMatrix4x4::SetIdentity()
{
	m_11 = m_22 = m_33 = m_44 = 1;
	m_12 = m_13 = m_14 = m_21 = m_23 = m_24 = m_31 = m_32 = m_34 = m_41 = m_42 = m_43 = 0;
	UpdateData(FALSE);
}
