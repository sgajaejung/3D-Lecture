
#include "stdafx.h"


class cViewer : public framework::cGameMain
{
public:
	cViewer();
	virtual ~cViewer();

	virtual bool OnInit() override;
	virtual void OnUpdate(const float elapseT) override;
	virtual void OnRender(const float elapseT) override;
	virtual void OnShutdown() override;
	virtual void MessageProc( UINT message, WPARAM wParam, LPARAM lParam) override;


protected:
	void UpdateCamera();


private:
	graphic::cLight m_light;

	graphic::cVertexBuffer m_vtxBuff;
	graphic::cIndexBuffer m_idxBuff;
	graphic::cMaterial m_mtrl;
	graphic::cTexture m_texture;

	graphic::cModel m_model;
	

	string m_filePath;

	POINT m_curPos;
	bool m_LButtonDown;
	bool m_RButtonDown;
	Matrix44 m_rotateTm;

	Vector3 m_camPos;
	Vector3 m_lookAtPos;
};

INIT_FRAMEWORK(cViewer);



// 버텍스 구조체
struct Vertex
{
	Vertex() {}
	Vertex(float x0, float y0, float z0) : p(Vector3(x0, y0, z0)), n(Vector3(0,0,0))
		,u(-100), v(-100)
	{}
	Vector3 p;
	Vector3 n;
	float u,v;
	static const DWORD FVF;
};
//버텍스 구조체 포맷.
const DWORD Vertex::FVF  = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;


cViewer::cViewer()
{
	m_windowName = L"Viewer";
	const RECT r = {0, 0, 800, 600};
	m_windowRect = r;
	m_LButtonDown = false;
	m_RButtonDown = false;
}

cViewer::~cViewer()
{
}


bool cViewer::OnInit()
{
	DragAcceptFiles(m_hWnd, TRUE);

	//ReadModelFile("../media/cube.dat", m_vtxBuff, m_idxBuff, m_texture);
	m_filePath = "../media/data.dat";
	m_model.Create( m_filePath );

	m_mtrl.InitWhite();

	Vector4 color(1,1,1,1);
	m_light.Init( graphic::cLight::LIGHT_DIRECTIONAL, color * 0.4f, color, color * 0.6f, Vector3(0,-1,0));
	m_light.Bind(0);


	m_camPos = Vector3(100,100,-500);
	m_lookAtPos = Vector3(0,0,0);
	UpdateCamera();

	const int WINSIZE_X = 1024;		//초기 윈도우 가로 크기
	const int WINSIZE_Y = 768;	//초기 윈도우 세로 크기
	Matrix44 proj;
	proj.SetProjection(D3DX_PI * 0.5f, (float)WINSIZE_X / (float) WINSIZE_Y, 1.f, 1000.0f) ;
	graphic::GetDevice()->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&proj) ;


	graphic::GetDevice()->LightEnable (
		0, // 활성화/ 비활성화 하려는 광원 리스트 내의 요소
		true); // true = 활성화 ， false = 비활성화

	return true;
}


void cViewer::OnUpdate(const float elapseT)
{
	m_model.Move(elapseT);
}


void cViewer::OnRender(const float elapseT)
{
	//화면 청소
	if (SUCCEEDED(graphic::GetDevice()->Clear( 
		0,			//청소할 영역의 D3DRECT 배열 갯수		( 전체 클리어 0 )
		NULL,		//청소할 영역의 D3DRECT 배열 포인터		( 전체 클리어 NULL )
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,	//청소될 버퍼 플레그 ( D3DCLEAR_TARGET 컬러버퍼, D3DCLEAR_ZBUFFER 깊이버퍼, D3DCLEAR_STENCIL 스텐실버퍼
		D3DCOLOR_XRGB(255, 255, 255),			//컬러버퍼를 청소하고 채워질 색상( 0xAARRGGBB )
		1.0f,				//깊이버퍼를 청소할값 ( 0 ~ 1 0 이 카메라에서 제일가까운 1 이 카메라에서 제일 먼 )
		0					//스텐실 버퍼를 채울값
		)))
	{
		//화면 청소가 성공적으로 이루어 졌다면... 랜더링 시작
		graphic::GetDevice()->BeginScene();

		graphic::GetRenderer()->RenderAxis();

		//static float y = 0;
		//y += elapseT * 0.03f;
		//// 각도가 2*PI 에 이르면 0으로 초기화한다.
		//if (y >= 6.28f)
		//	y = 0;

		//Matrix44 rx, ry, r;
		////rx.SetRotationX(MATH_PI/4.f); 	// x축으로 45도 회전시킨다.
		//ry.SetRotationY(y); // y축으로 회전
		//r = rx*ry;

		//Matrix44 tm;
		//tm = m_rotateTm;
		//graphic::GetDevice()->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&tm);

		//m_mtrl.Bind();
		//m_texture.Bind(0);
		//m_idxBuff.Bind();
		//m_vtxBuff.Bind();
		//graphic::GetDevice()->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, 
		//	m_vtxBuff.GetVertexCount(), 0, m_idxBuff.GetFaceCount());

		m_model.SetTM(m_rotateTm);
		m_model.Render();

		//랜더링 끝
		graphic::GetDevice()->EndScene();
		//랜더링이 끝났으면 랜더링된 내용 화면으로 전송
		graphic::GetDevice()->Present( NULL, NULL, NULL, NULL );
	}
}


void cViewer::OnShutdown()
{

}


void cViewer::MessageProc( UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DROPFILES:
		{
			HDROP hdrop = (HDROP)wParam;
			char filePath[ MAX_PATH];
			const UINT size = DragQueryFileA(hdrop, 0, filePath, MAX_PATH);
			if (size == 0) 
				return;// handle error...

			m_filePath = filePath;
			//m_texture.Clear();
			//m_vtxBuff.Clear();
			//m_idxBuff.Clear();
			//ReadModelFile(filePath, m_vtxBuff, m_idxBuff, m_texture);
			m_model.Create(filePath);
		}
		break;

	case WM_MOUSEWHEEL:
		{
			int fwKeys = GET_KEYSTATE_WPARAM(wParam);
			int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			//dbg::Print( "%d %d", fwKeys, zDelta);

			Vector3 dir = m_lookAtPos - m_camPos;
			dir.Normalize();

			m_camPos += (zDelta<0)? dir*-50.f : dir*50.f;
			UpdateCamera();
		}
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_F5: // Refresh
			{
				if (m_filePath.empty())
					return;
				m_model.Create(m_filePath);
			}
			break;
		case VK_BACK:
			// 회전 행렬 초기화.
			m_rotateTm.SetIdentity();
			m_model.SetTM(m_rotateTm);
			break;
		case VK_TAB:
			{
				static bool flag = false;
				graphic::GetDevice()->SetRenderState(D3DRS_CULLMODE, flag);
				graphic::GetDevice()->SetRenderState(D3DRS_FILLMODE, flag? D3DFILL_SOLID : D3DFILL_WIREFRAME);
				flag = !flag;
			}
			break;
		}
		break;

	case WM_LBUTTONDOWN:
		{
			m_LButtonDown = true;
			m_curPos.x = LOWORD(lParam);
			m_curPos.y = HIWORD(lParam);
		}
		break;

	case WM_LBUTTONUP:
		m_LButtonDown = false;
		break;

	case WM_RBUTTONDOWN:
		{
			m_RButtonDown = true;
			m_curPos.x = LOWORD(lParam);
			m_curPos.y = HIWORD(lParam);
		}
		break;

	case WM_RBUTTONUP:
		m_RButtonDown = false;
		break;

	case WM_MOUSEMOVE:
		if (m_LButtonDown)
		{
			POINT pos;
			pos.x = LOWORD(lParam);
			pos.y = HIWORD(lParam);

			const int x = pos.x - m_curPos.x;
			const int y = pos.y - m_curPos.y;

			Matrix44 mat1;
			mat1.SetRotationY( -x * 0.01f );
			Matrix44 mat2;
			mat2.SetRotationX( -y * 0.01f );

			m_curPos = pos;

			m_rotateTm *= (mat1 * mat2);
		}
		else if (m_RButtonDown)
		{
			POINT pos;
			pos.x = LOWORD(lParam);
			pos.y = HIWORD(lParam);

			const int x = pos.x - m_curPos.x;
			const int y = pos.y - m_curPos.y;
			m_curPos = pos;

			{ // rotate Y-Axis
				Quaternion q(Vector3(0,1,0), x * 0.005f); 
				Matrix44 m = q.GetMatrix();
				m_camPos *= m;
			}

			{ // rotate X-Axis
				Quaternion q(Vector3(1,0,0), y * 0.005f); 
				Matrix44 m = q.GetMatrix();
				m_camPos *= m;
			}

			UpdateCamera();
		}
		break;
	}
}


void cViewer::UpdateCamera()
{
	Matrix44 V;
	Vector3 dir = m_lookAtPos - m_camPos;
	dir.Normalize();
	V.SetView(m_camPos, dir, Vector3(0,1,0));
	graphic::GetDevice()->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&V);
}