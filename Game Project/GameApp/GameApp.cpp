
#include "stdafx.h"
#include "GameApp.h"
#include <fstream>

INIT_FRAMEWORK(cGameApp);


const int WINSIZE_X = 1024;		//초기 윈도우 가로 크기
const int WINSIZE_Y = 768;	//초기 윈도우 세로 크기
const int WINPOS_X = 0; //초기 윈도우 시작 위치 X
const int WINPOS_Y = 0; //초기 윈도우 시작 위치 Y


template<class T>
class SafeLock
{
public:
	SafeLock(T &t) :m_t(t) { }
	virtual ~SafeLock() { m_t.Unlock(); }
	T &m_t;
};


// 버텍스 구조체
struct Vertex
{
	Vertex() {}
	Vertex(float x0, float y0, float z0) : p(Vector3(x0, y0, z0)), n(Vector3(0,0,0)) {}
	Vector3 p;
	Vector3 n;
	static const DWORD FVF;
};
//버텍스 구조체 포맷.
const DWORD Vertex::FVF  = D3DFVF_XYZ | D3DFVF_NORMAL;


cGameApp::cGameApp() :
	//m_pVB(NULL),
	m_pIB(NULL)
{
	m_windowName = L"GameApp";
	const RECT r = {0, 0, 800, 600};
	m_windowRect = r;
}

cGameApp::~cGameApp()
{
}


bool cGameApp::OnInit()
{
	ReadModelFile("vase.dat", m_vtxBuff, m_VtxSize, m_pIB, m_FaceSize);

	m_mtrl.InitRed();

	D3DXCOLOR color(1,1,1,1);
	ZeroMemory(&m_Light, sizeof(m_Light));
	m_Light.Type = D3DLIGHT_DIRECTIONAL;
	m_Light.Ambient = color * 0.4f;
	m_Light.Diffuse = color;
	m_Light.Specular = color * 0.6f;
	m_Light.Direction = *(D3DXVECTOR3*)&Vector3(1,0,0);	

	Matrix44 V;
	Vector3 dir = Vector3(0,0,0)-Vector3(0,0,-5);
	dir.Normalize();
	V.SetView(Vector3(0,0,-500), dir, Vector3(0,1,0));
	graphic::GetDevice()->SetTransform(D3DTS_VIEW, (D3DXMATRIX*)&V);

	Matrix44 proj;
	proj.SetProjection(D3DX_PI * 0.5f, (float)WINSIZE_X / (float) WINSIZE_Y, 1.f, 1000.0f) ;
	graphic::GetDevice()->SetTransform(D3DTS_PROJECTION, (D3DXMATRIX*)&proj) ;

	graphic::GetDevice()->SetLight(0, &m_Light); // 광원 설정.
	graphic::GetDevice()->LightEnable (
		0, // 활성화/ 비활성화 하려는 광원 리스트 내의 요소
		true); // true = 활성화 ， false = 비활성화

	return true;
}


void cGameApp::OnUpdate(const float elapseT)
{

}


void cGameApp::OnRender(const float elapseT)
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

		static float y = 0;
		y += elapseT;
		// 각도가 2*PI 에 이르면 0으로 초기화한다.
		if (y >= 6.28f)
			y = 0;

		Matrix44 rx, ry, r;
		rx.SetRotationX(MATH_PI/4.f); 	// x축으로 45도 회전시킨다.
		ry.SetRotationY(y); // y축으로 회전
		r = rx*ry;
		graphic::GetDevice()->SetTransform(D3DTS_WORLD, (D3DXMATRIX*)&r);

		m_mtrl.Bind();
		//graphic::GetDevice()->SetStreamSource( 0, m_pVB, 0, sizeof(Vertex) );
		graphic::GetDevice()->SetIndices(m_pIB);
		//graphic::GetDevice()->SetFVF( Vertex::FVF );
		m_vtxBuff.Bind();
		graphic::GetDevice()->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, 0, 0, m_VtxSize, 0, m_FaceSize);


		//랜더링 끝
		graphic::GetDevice()->EndScene();
		//랜더링이 끝났으면 랜더링된 내용 화면으로 전송
		graphic::GetDevice()->Present( NULL, NULL, NULL, NULL );
	}
}


void cGameApp::OnShutdown()
{
	//if (m_pVB)
	//	m_pVB->Release();
	if (m_pIB)
		m_pIB->Release();
}


void cGameApp::MessageProc( UINT message, WPARAM wParam, LPARAM lParam)
{

}


bool cGameApp::ReadModelFile( const string &fileName, graphic::cVertexBuffer &vtxBuff, int &vtxSize,  
	LPDIRECT3DINDEXBUFFER9 &idxBuff, int &faceSize )
{
	using namespace std;
	ifstream fin(fileName.c_str());
	if (!fin.is_open())
		return false;

	string vtx, vtx_eq;
	int numVertices;
	fin >> vtx >> vtx_eq >> numVertices;

	if (numVertices <= 0)
		return  false;

	vtxSize = numVertices;

	if (!vtxBuff.Create(vtxSize, sizeof(Vertex), Vertex::FVF))
		return false;

	// 버텍스 버퍼 생성.
	//if (FAILED(graphic::GetDevice()->CreateVertexBuffer( numVertices * sizeof(Vertex),
	//	D3DUSAGE_WRITEONLY, Vertex::FVF,
	//	D3DPOOL_MANAGED, &vtxBuff, NULL)))
	//{
	//	return false;
	//}

	// 버텍스 버퍼 초기화.
	Vertex* vertices = (Vertex*)vtxBuff.Lock();
	//if (FAILED(vtxBuff->Lock( 0, sizeof(Vertex), (void**)&vertices, 0)))
	//	return false;
	float num1, num2, num3;
	for (int i = 0; i < numVertices; i++)
	{
		fin >> num1 >> num2 >> num3;
		vertices[i] = Vertex(num1, num2, num3);
	}
	//vtxBuff->Unlock();
	vtxBuff.Unlock();


	string idx, idx_eq;
	int numIndices;
	fin >> idx >> idx_eq >> numIndices;

	if (numIndices <= 0)
		return false;

	faceSize = numIndices;

	if (FAILED(graphic::GetDevice()->CreateIndexBuffer(numIndices*3*sizeof(WORD), 
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&idxBuff, NULL)))
	{
		return false;
	}

	WORD *indices = NULL;
	idxBuff->Lock(0, 0, (void**)&indices, 0);
	int num4, num5, num6;
	for (int i = 0; i < numIndices*3; i+=3)
	{
		fin >> num4 >> num5 >> num6;
		indices[ i] = num4;
		indices[ i+1] = num5;
		indices[ i+2] = num6;	
	}
	idxBuff->Unlock();

	ComputeNormals(vtxBuff, vtxSize, idxBuff, faceSize);
	return true;
}


void cGameApp::ComputeNormals(graphic::cVertexBuffer &vtxBuff, int vtxSize,  
	LPDIRECT3DINDEXBUFFER9 idxBuff, int faceSize)
{
	//Vertex* vertices;
	//vtxBuff->Lock( 0, sizeof(Vertex), (void**)&vertices, 0);
	Vertex* vertices = (Vertex*)vtxBuff.Lock();

	WORD *indices = NULL;
	idxBuff->Lock(0, 0, (void**)&indices, 0);

	for (int i=0; i < faceSize*3; i+=3)
	{
		Vector3 p1 = vertices[ indices[ i]].p;
		Vector3 p2 = vertices[ indices[ i+1]].p;
		Vector3 p3 = vertices[ indices[ i+2]].p;

		Vector3 v1 = p2 - p1;
		Vector3 v2 = p3 - p1;
		v1.Normalize();
		v2.Normalize();
		Vector3 n = v1.CrossProduct(v2);
		n.Normalize();

		if (vertices[ indices[ i]].n.IsEmpty())
		{
			vertices[ indices[ i]].n = n;
		}
		else
		{
			vertices[ indices[ i]].n += n;
			vertices[ indices[ i]].n /= 2.f;
		}

		if (vertices[ indices[ i+1]].n.IsEmpty())
		{
			vertices[ indices[ i+1]].n = n;
		}
		else
		{
			vertices[ indices[ i+1]].n += n;
			vertices[ indices[ i+1]].n /= 2.f;
		}

		if (vertices[ indices[ i+2]].n.IsEmpty())
		{
			vertices[ indices[ i+2]].n = n;
		}
		else
		{
			vertices[ indices[ i+2]].n += n;
			vertices[ indices[ i+2]].n /= 2.f;
		}
	}

	//vtxBuff->Unlock();
	vtxBuff.Unlock();
	idxBuff->Unlock();
}
