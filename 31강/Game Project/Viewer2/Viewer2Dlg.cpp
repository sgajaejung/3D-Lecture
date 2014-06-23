
// Viewer2Dlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Viewer2.h"
#include "Viewer2Dlg.h"
#include "afxdialogex.h"
#include "ModelView.h"




#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CViewer2Dlg 대화 상자


CViewer2Dlg::CViewer2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CViewer2Dlg::IDD, pParent)
,	m_loop(true)
{
//	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CViewer2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FILE_LIST, m_FileList);
}

BEGIN_MESSAGE_MAP(CViewer2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CViewer2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CViewer2Dlg::OnBnClickedCancel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_FILE_LIST, OnItemchangedList)
	ON_NOTIFY(LVN_KEYDOWN, IDC_FILE_LIST, &CViewer2Dlg::OnKeydownFileList)
END_MESSAGE_MAP()


// CViewer2Dlg 메시지 처리기

BOOL CViewer2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_pModelView = new CModelView();
	m_pModelView->Create(NULL, L"CModelView", WS_CHILDWINDOW, 
		CRect(0, 0, 300, 300), this, 0);

	graphic::cRenderer::Get()->CreateDirectX(
		m_pModelView->GetSafeHwnd(), 300, 300);

	m_pModelView->Init();

	m_pModelView->ShowWindow(SW_SHOW);

	m_FileList.InsertColumn(0, L"DATA");
	m_FileList.SetColumnWidth(0, 300);
	m_FileList.InsertItem(0, L"test1");
	m_FileList.InsertItem(1, L"test2");
	m_FileList.InsertItem(2, L"test3");
	m_FileList.InsertItem(3, L"test4");


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CViewer2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CViewer2Dlg::OnPaint()
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

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CViewer2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CViewer2Dlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void CViewer2Dlg::OnBnClickedCancel()
{
	m_loop = false;
	CDialogEx::OnCancel();
}


void CViewer2Dlg::MainLoop()
{
	MSG msg;
	while (m_loop)
	{
		if (PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ))
		{
			GetMessage(&msg, NULL, 0, 0);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//render
		if (m_pModelView)
			m_pModelView->Render();		

		Sleep(0);
	}
}


void CViewer2Dlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult)
{

}

void CViewer2Dlg::OnKeydownFileList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLVKEYDOWN pLVKeyDow = reinterpret_cast<LPNMLVKEYDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}
