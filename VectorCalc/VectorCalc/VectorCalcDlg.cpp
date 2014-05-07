

#include "stdafx.h"
#include "VectorCalc.h"
#include "VectorCalcDlg.h"
#include "afxdialogex.h"
#include "DotProductView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CVectorCalcDlg::CVectorCalcDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVectorCalcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVectorCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_CALC, m_TabCtrl);
}

BEGIN_MESSAGE_MAP(CVectorCalcDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CVectorCalcDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CVectorCalcDlg::OnBnClickedCancel)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CALC, &CVectorCalcDlg::OnSelchangeTabCalc)
END_MESSAGE_MAP()


// CVectorCalcDlg 메시지 처리기
BOOL CVectorCalcDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	m_TabCtrl.InsertItem(0, "Dot Product" );
	m_TabCtrl.InsertItem(1, "Cross Product" );

	m_pView = new CDotProductView();
	m_pView->Create(NULL, "CDotProductView",  WS_CHILDWINDOW, CRect(100, 100, 500, 500), this, 1000);
	m_pView->ShowWindow(SW_SHOW);

	return TRUE;
}


void CVectorCalcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CVectorCalcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CVectorCalcDlg::OnBnClickedOk()
{
	//CDialogEx::OnOK();
}


void CVectorCalcDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}


void CVectorCalcDlg::OnSelchangeTabCalc(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;


	int n = m_TabCtrl.GetCurSel();
}


BOOL CVectorCalcDlg::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::OnWndMsg(message, wParam, lParam, pResult);
}
