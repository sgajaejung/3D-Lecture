// ModelView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Viewer2.h"
#include "ModelView.h"



// CModelView

CModelView::CModelView() : 
	m_model(NULL)
{
	m_LButtonDown = false;
	m_RButtonDown = false;
	
}

CModelView::~CModelView()
{
	SAFE_DELETE(m_model);
}

BEGIN_MESSAGE_MAP(CModelView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


// CModelView 그리기입니다.

void CModelView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.
}


// CModelView 진단입니다.

#ifdef _DEBUG
void CModelView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CModelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CModelView 메시지 처리기입니다.

void CModelView::Init()
{
	//DragAcceptFiles(TRUE);

	m_filePath = "../media/data.dat";
	m_model = new graphic::cModel();
	m_model->Create( m_filePath );

	m_camPos = Vector3(100,100,-500);
	m_lookAtPos = Vector3(0,0,0);
	UpdateCamera();

	const int WINSIZE_X = 1024;		//초기 윈도우 가로 크기
	const int WINSIZE_Y = 768;	//초기 윈도우 세로 크기
	Matrix44 proj;
	proj.SetProjection(D3DX_PI / 4.f, (float)WINSIZE_X / (float) WINSIZE_Y, 1.f, 10000.0f) ;
	graphic::GetDevice()->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&proj) ;

	graphic::GetDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	graphic::GetDevice()->LightEnable (
		0, // 활성화/ 비활성화 하려는 광원 리스트 내의 요소
		true); // true = 활성화 ， false = 비활성화
}


void CModelView::Update(const float elapseT)
{
	m_model->Move(elapseT);
}


void CModelView::Render()
{
	//화면 청소
	if (SUCCEEDED(graphic::GetDevice()->Clear( 
		0,			//청소할 영역의 D3DRECT 배열 갯수		( 전체 클리어 0 )
		NULL,		//청소할 영역의 D3DRECT 배열 포인터		( 전체 클리어 NULL )
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,	//청소될 버퍼 플레그 ( D3DCLEAR_TARGET 컬러버퍼, D3DCLEAR_ZBUFFER 깊이버퍼, D3DCLEAR_STENCIL 스텐실버퍼
		D3DCOLOR_XRGB(150, 150, 150),			//컬러버퍼를 청소하고 채워질 색상( 0xAARRGGBB )
		1.0f,				//깊이버퍼를 청소할값 ( 0 ~ 1 0 이 카메라에서 제일가까운 1 이 카메라에서 제일 먼 )
		0					//스텐실 버퍼를 채울값
		)))
	{
		//화면 청소가 성공적으로 이루어 졌다면... 랜더링 시작
		graphic::GetDevice()->BeginScene();

		graphic::GetRenderer()->RenderFPS();
		graphic::GetRenderer()->RenderGrid();
		graphic::GetRenderer()->RenderAxis();

		m_model->SetTM(m_rotateTm);
		m_model->Render();

		//랜더링 끝
		graphic::GetDevice()->EndScene();
		//랜더링이 끝났으면 랜더링된 내용 화면으로 전송
		graphic::GetDevice()->Present( NULL, NULL, NULL, NULL );
	}
}


void CModelView::UpdateCamera()
{
	Matrix44 V;
	Vector3 dir = m_lookAtPos - m_camPos;
	dir.Normalize();
	V.SetView(m_camPos, dir, Vector3(0,1,0));
	graphic::GetDevice()->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&V);
}


void CModelView::OnLButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	m_LButtonDown = true;
	m_curPos = point;
	CView::OnLButtonDown(nFlags, point);
}


void CModelView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_LButtonDown = false;
	CView::OnLButtonUp(nFlags, point);
}


void CModelView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_LButtonDown)
	{
		CPoint pos = point  - m_curPos;
		m_curPos = point;

		Matrix44 mat1;
		mat1.SetRotationY( -pos.x * 0.01f );
		Matrix44 mat2;
		mat2.SetRotationX( -pos.y * 0.01f );

		m_rotateTm *= (mat1 * mat2);
	}	
	else if (m_RButtonDown)
	{
		CPoint pos = point  - m_curPos;
		m_curPos = point;

		{ // rotate Y-Axis
			Quaternion q(Vector3(0,1,0), pos.x * 0.005f); 
			Matrix44 m = q.GetMatrix();
			m_camPos *= m;
		}

		{ // rotate X-Axis
			Quaternion q(Vector3(1,0,0), pos.y * 0.005f); 
			Matrix44 m = q.GetMatrix();
			m_camPos *= m;
		}

		UpdateCamera();
	}
	CView::OnMouseMove(nFlags, point);
}


BOOL CModelView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	dbg::Print( "%d %d", nFlags, zDelta);

	Vector3 dir = m_lookAtPos - m_camPos;
	dir.Normalize();

	float zoomLen = 50;
	if (nFlags & 0x4)
		zoomLen = 1;

	m_camPos += (zDelta<0)? dir*-zoomLen : dir*zoomLen;
	UpdateCamera();

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void CModelView::OnRButtonDown(UINT nFlags, CPoint point)
{
	SetFocus();
	m_RButtonDown = true;
	m_curPos = point;
	CView::OnRButtonDown(nFlags, point);
}


void CModelView::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_RButtonDown = false;
	CView::OnRButtonUp(nFlags, point);
}


bool CModelView::LoadModel(const string &fileName)
{
	m_rotateTm.SetIdentity();
	m_filePath = fileName;
	return m_model->Create(fileName);
}
