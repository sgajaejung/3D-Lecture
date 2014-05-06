// DlgCalc4x4.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MatrixCalc.h"
#include "DlgCalc4x4.h"
#include "afxdialogex.h"
#include "EditMatrix4x4.h"
#include "EditVector4.h"


// CDlgCalc4x4 대화 상자입니다.
CDlgCalc4x4::CDlgCalc4x4(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgCalc4x4::IDD, pParent)
{

}

CDlgCalc4x4::~CDlgCalc4x4()
{
}

void CDlgCalc4x4::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_FIRST, m_ComboFirst);
	DDX_Control(pDX, IDC_COMBO_SECOND, m_ComboSecond);
}


BEGIN_MESSAGE_MAP(CDlgCalc4x4, CDialogEx)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_FIRST, &CDlgCalc4x4::OnCbnSelchangeComboFirst)
	ON_CBN_SELCHANGE(IDC_COMBO_SECOND, &CDlgCalc4x4::OnCbnSelchangeComboSecond)
	ON_BN_CLICKED(IDC_BUTTON_CALC, &CDlgCalc4x4::OnBnClickedButtonCalc)
END_MESSAGE_MAP()


// CDlgCalc4x4 메시지 처리기입니다.
BOOL CDlgCalc4x4::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_pResult = new CEditMatrix4x4(this);
	m_pResult->Create(CEditMatrix4x4::IDD, this);
	m_pResult->MoveWindow(CRect(150, 200, 400, 500));
	m_pResult->ShowWindow(SW_SHOW);

	//---------------------------------------------------------------------------------
	// First 
	m_ComboFirst.AddString("Matrix44");
	m_ComboFirst.AddString("Matrix44 Identity");
	m_ComboFirst.AddString("Vector4");
	m_ComboFirst.SetCurSel(0);

	{
		CEditMatrix4x4 *pEditMat44 = new CEditMatrix4x4(this);
		pEditMat44->Create(CEditMatrix4x4::IDD, this);
		pEditMat44->MoveWindow(CRect(10, 40, 200, 200));

		CEditMatrix4x4 *pEditMat44_2 = new CEditMatrix4x4(this);
		pEditMat44_2->Create(CEditMatrix4x4::IDD, this);
		pEditMat44_2->MoveWindow(CRect(10, 40, 200, 200));
		pEditMat44_2->SetIdentity();

		CEditVector4 *pEditVector4 = new CEditVector4(this);
		pEditVector4->Create(CEditVector4::IDD, this);
		pEditVector4->MoveWindow(CRect(10, 40, 200, 200));

		m_First.resize(VAR1_MAX);
		m_First[ VAR1_MATRIX] = pEditMat44;
		m_First[ VAR1_IDENTITY] = pEditMat44_2;
		m_First[ VAR1_VECTOR4] = pEditVector4;

		m_First[0]->ShowWindow(SW_SHOW);
	}
	//---------------------------------------------------------------------------------


	//---------------------------------------------------------------------------------
	// Second
	m_ComboSecond.AddString("Matrix44");
	m_ComboSecond.AddString("Matrix44 Identity");
	m_ComboSecond.SetCurSel(0);

	{		
		CEditMatrix4x4 *pEditMat44 = new CEditMatrix4x4(this);
		pEditMat44->Create(CEditMatrix4x4::IDD, this);
		pEditMat44->MoveWindow(CRect(250, 40, 500, 200));

		CEditMatrix4x4 *pEditMat44_2 = new CEditMatrix4x4(this);
		pEditMat44_2->Create(CEditMatrix4x4::IDD, this);
		pEditMat44_2->MoveWindow(CRect(250, 40, 500, 200));
		pEditMat44_2->SetIdentity();

		m_Second.resize(VAR2_MAX);
		m_Second[ VAR2_MATRIX] = pEditMat44;
		m_Second[ VAR2_IDENTITY] = pEditMat44_2;

		m_Second[0]->ShowWindow(SW_SHOW);
	}
	//---------------------------------------------------------------------------------

	return TRUE;
}


void CDlgCalc4x4::OnDestroy()
{
	CDialogEx::OnDestroy();

	m_pResult->DestroyWindow();
	delete m_pResult;

	for (int i=0; i < (int)m_First.size(); ++i)
	{
		m_First[ i]->DestroyWindow();
		delete m_First[ i];
	}
	m_First.clear();


	for (int i=0; i < (int)m_Second.size(); ++i)
	{
		m_Second[ i]->DestroyWindow();
		delete m_Second[ i];
	}
	m_Second.clear();
}


void CDlgCalc4x4::OnCbnSelchangeComboFirst()
{
	for (int i=0; i < (int)m_First.size(); ++i)
		m_First[ i]->ShowWindow(SW_HIDE);

	if (VAR1_IDENTITY == m_ComboFirst.GetCurSel())
	{
		CommonDataInterface *dataInterface = dynamic_cast<CommonDataInterface *>(m_First[ m_ComboFirst.GetCurSel()]);
		if (NULL != dataInterface)
			dataInterface->SetIdentity();
	}

	m_First[ m_ComboFirst.GetCurSel()]->ShowWindow(SW_SHOW);
}


void CDlgCalc4x4::OnCbnSelchangeComboSecond()
{
	for (int i=0; i < (int)m_Second.size(); ++i)
		m_Second[ i]->ShowWindow(SW_HIDE);

	if (VAR2_IDENTITY == m_ComboSecond.GetCurSel())
	{
		CommonDataInterface *dataInterface = dynamic_cast<CommonDataInterface *>(m_Second[ m_ComboSecond.GetCurSel()]);
		if (NULL != dataInterface)
			dataInterface->SetIdentity();
	}

	m_Second[ m_ComboSecond.GetCurSel()]->ShowWindow(SW_SHOW);
}


void CDlgCalc4x4::OnBnClickedButtonCalc()
{
	FIRST_VARIABLE first = (FIRST_VARIABLE)m_ComboFirst.GetCurSel();
	SECOND_VARIABLE second = (SECOND_VARIABLE)m_ComboSecond.GetCurSel();

	switch (first)
	{
	case VAR1_MATRIX:
	case VAR1_IDENTITY:
		{


		}
		break;
		
	case VAR1_VECTOR4:
		{

		}
		break;
	}	
}
