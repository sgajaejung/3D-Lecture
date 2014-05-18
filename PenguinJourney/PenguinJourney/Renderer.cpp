
#include "math/Math.h"
#include "Renderer.h"
#include "DrawTriangle.h"

extern Vector3 g_cameraLookat;
extern Vector3 g_cameraPos;


void RenderVertices(HDC hdc, const vector<Vector3> &vertices, const Matrix44 &tm)
{
	for (unsigned int i=0; i < vertices.size(); ++i)
	{
		Vector3 p = vertices[ i] * tm;

		if (0 == i)
			MoveToEx(hdc, (int)p.x, (int)p.y, NULL);
		else
			LineTo(hdc, (int)p.x, (int)p.y);
	}
}


void RenderIndices(HDC hdc, const vector<Vector3> &vertices, const vector<int> &indices, 
	const vector<Vector3> &normals, const Matrix44 &tm, const Matrix44 &vpv)
{
	Vector3 camDir = g_cameraLookat - g_cameraPos;
	camDir.Normalize();

	Rasterizer::Color c0(0,0,255,1);
	Rasterizer::Color c1(255,255,255,1);
	Vector3 lightDir(0,-1,0);
	Vector3 H = -(camDir + lightDir);
	H.Normalize();
	Rasterizer::Color ambient(0,20,0,1);

	for (unsigned int i=0; i < indices.size(); i+=3)
	{
		Vector3 p1 = vertices[ indices[ i]];
		Vector3 p2 = vertices[ indices[ i+1]];
		Vector3 p3 = vertices[ indices[ i+2]];

		p1 = p1 * tm;
		p2 = p2 * tm;
		p3 = p3 * tm;

		// culling
		Vector3 n1 = normals[ indices[i]].MultiplyNormal(tm);
		Vector3 n2 = normals[ indices[i+1]].MultiplyNormal(tm);
		Vector3 n3 = normals[ indices[i+2]].MultiplyNormal(tm);
		const float dot1 = n1.DotProduct(camDir);
		const float dot2 = n2.DotProduct(camDir);
		const float dot3 = n3.DotProduct(camDir);
		if ((dot1 > 0) && (dot2 > 0) && (dot3 > 0))
			continue;

		p1 = p1 * vpv;
		p2 = p2 * vpv;
		p3 = p3 * vpv;

		Rasterizer::Color color1, color2, color3;
		{
			Rasterizer::Color diffuse = c0 * max(0, n1.DotProduct(-lightDir));
			Rasterizer::Color specular = 0;//c1*pow(n1.DotProduct(H), 16);
			color1 = ambient + diffuse + specular;
		}
		{
			Rasterizer::Color diffuse = c0 * max(0, n2.DotProduct(-lightDir));
			Rasterizer::Color specular = c1*pow(n2.DotProduct(H), 16);
			color2 = ambient + diffuse + specular;
		}
		{
			Rasterizer::Color diffuse = c0 * max(0, n3.DotProduct(-lightDir));
			Rasterizer::Color specular = c1*pow(n3.DotProduct(H), 16);
			color3 = ambient + diffuse + specular;
		}

		Rasterizer::DrawLine(hdc, color1, p1.x, p1.y, color1, p2.x, p2.y);
		Rasterizer::DrawLine(hdc, color1, p1.x, p1.y, color1, p3.x, p3.y);
		Rasterizer::DrawLine(hdc, color1, p3.x, p3.y, color1, p2.x, p2.y);
		//Rasterizer::DrawTriangle(hdc, 
		//	color1, p1.x, p1.y, n1,
		//	color2, p2.x, p2.y, n2,
		//	color3, p3.x, p3.y, n3);
	}
}


void RenderIndices(HDC hdc, const vector<Vector3> &vertices, const vector<int> &indices, const Matrix44 &tm)
{
	for (unsigned int i=0; i < indices.size(); i+=3)
	{
		Vector3 p1 = vertices[ indices[ i]];
		Vector3 p2 = vertices[ indices[ i+1]];
		Vector3 p3 = vertices[ indices[ i+2]];

		p1 = p1 * tm;
		p2 = p2 * tm;
		p3 = p3 * tm;

		Vector3 n;
		Rasterizer::Color color(0,255,0,1);
		Rasterizer::DrawTriangle(hdc, 
			color, p1.x, p1.y, n,
			color, p2.x, p2.y, n,
			color, p3.x, p3.y, n);
	}
}
