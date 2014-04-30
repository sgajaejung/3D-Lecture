// 2014-04-04
// http://joshbeam.com/articles/simple_line_drawing

#include "stdafx.h"
#include "math/Math.h"
#include "DrawTriangle.h"
#include <math.h>


namespace Rasterizer
{
	struct Edge
	{
		Color Color1, Color2;
		Vector3 N1, N2;
		int X1, Y1, X2, Y2;
		Edge(const Color &color1, int x1, int y1, const Vector3 &n1, const Color &color2, int x2, int y2, const Vector3 &n2);
	};

	struct Span
	{
		Color Color1, Color2;
		Vector3 N1, N2;
		int X1, X2;
		Span(const Color &color1, int x1, const Vector3 &n1, const Color &color2, int x2, const Vector3 &n2);
	};


	void DrawSpansBetweenEdges(HDC hdc, const Edge &e1, const Edge &e2);
	void DrawSpan(HDC hdc, const Span &span, int y);


	Vector3 g_LightDir = Vector3(0,-1,0);
	void SetLight( const Vector3 &dir ) { g_LightDir = dir; }
}


using namespace Rasterizer;


Edge::Edge(const Color &color1, int x1, int y1, const Vector3 &n1, const Color &color2, int x2, int y2, const Vector3 &n2)
{
	if(y1 < y2) {
		Color1 = color1;
		X1 = x1;
		Y1 = y1;
		N1 = n1;
		Color2 = color2;
		X2 = x2;
		Y2 = y2;
		N2 = n2;
	} else {
		Color1 = color2;
		X1 = x2;
		Y1 = y2;
		N1 = n2;
		Color2 = color1;
		X2 = x1;
		Y2 = y1;
		N2 = n1;
	}

	//X1 = max(0, X1);
	//X1 = min(X1, 800);
	//X2 = max(0, X2);
	//X2 = min(X2, 800);
	//Y1 = max(0, Y1);
	//Y1 = min(Y1, 600);
	//Y2 = max(0, Y2);
	//Y2 = min(Y2, 600);
}


Span::Span(const Color &color1, int x1, const Vector3 &n1, const Color &color2, int x2, const Vector3 &n2)
{
	if(x1 < x2) {
		Color1 = color1;
		X1 = x1;
		N1 = n1;
		Color2 = color2;
		X2 = x2;
		N2 = n2;
	} else {
		Color1 = color2;
		X1 = x2;
		N1 = n2;
		Color2 = color1;
		X2 = x1;
		N2 = n1;
	}

	//X1 = max(0, X1);
	//X1 = min(X1, 800);
	//X2 = max(0, X2);
	//X2 = min(X2, 800);
}

Color::Color(float r, float g, float b, float a) : R(r), G(g), B(b), A(a)
{
}

Color Color::operator + (const Color &c) const
{
	return Color(R+c.R, G+c.G, B+c.B, A+c.A);
}

Color Color::operator - (const Color &c) const
{
	return Color(R-c.R, G-c.G, B-c.B, A-c.A);
}

Color Color::operator * (float f) const
{
	return Color(R*f, G*f, B*f, A*f);
}


/**
 @brief 
 @date 2014-04-04
*/
void Rasterizer::DrawTriangle(HDC hdc, 
	const Color &color1, float x1, float y1, const Vector3 &norm1,
	const Color &color2, float x2, float y2, const Vector3 &norm2,
	const Color &color3, float x3, float y3, const Vector3 &norm3)
{
	// create edges for the triangle
	Edge edges[3] = {
		Edge(color1, (int)x1, (int)y1, norm1, color2, (int)x2, (int)y2, norm2),
		Edge(color2, (int)x2, (int)y2, norm2, color3, (int)x3, (int)y3, norm3),
		Edge(color3, (int)x3, (int)y3, norm3, color1, (int)x1, (int)y1, norm1)
	};

	int maxLength = 0;
	int longEdge = 0;

	// find edge with the greatest length in the y axis
	for(int i = 0; i < 3; i++) {
		int length = edges[i].Y2 - edges[i].Y1;
		if(length > maxLength) {
			maxLength = length;
			longEdge = i;
		}
	}

	int shortEdge1 = (longEdge + 1) % 3;
	int shortEdge2 = (longEdge + 2) % 3;

	// draw spans between edges; the long edge can be drawn
	// with the shorter edges to draw the full triangle
	DrawSpansBetweenEdges(hdc, edges[longEdge], edges[shortEdge1]);
	DrawSpansBetweenEdges(hdc, edges[longEdge], edges[shortEdge2]);
}


void Rasterizer::DrawSpansBetweenEdges(HDC hdc, const Edge &e1, const Edge &e2)
{
	// calculate difference between the y coordinates
	// of the first edge and return if 0
	float e1ydiff = (float)(e1.Y2 - e1.Y1);
	if(e1ydiff == 0.0f)
		return;

	// calculate difference between the y coordinates
	// of the second edge and return if 0
	float e2ydiff = (float)(e2.Y2 - e2.Y1);
	if(e2ydiff == 0.0f)
		return;

	// calculate differences between the x coordinates
	// and colors of the points of the edges
	float e1xdiff = (float)(e1.X2 - e1.X1);
	float e2xdiff = (float)(e2.X2 - e2.X1);
	Color e1colordiff = (e1.Color2 - e1.Color1);
	Color e2colordiff = (e2.Color2 - e2.Color1);

	// calculate factors to use for interpolation
	// with the edges and the step values to increase
	// them by after drawing each span
	float factor1 = (float)(e2.Y1 - e1.Y1) / e1ydiff;
	float factorStep1 = 1.0f / e1ydiff;
	float factor2 = 0.0f;
	float factorStep2 = 1.0f / e2ydiff;

	// loop through the lines between the edges and draw spans
	for(int y = e2.Y1; y < e2.Y2; y++) {
		// create and draw span
		Span span(e1.Color1 + (e1colordiff * factor1),
			e1.X1 + (int)(e1xdiff * factor1),
			e1.N1,
			e2.Color1 + (e2colordiff * factor2),
			e2.X1 + (int)(e2xdiff * factor2),
			e2.N1);
		DrawSpan(hdc, span, y);

		// increase factors
		factor1 += factorStep1;
		factor2 += factorStep2;
	}
}


void Rasterizer::DrawSpan(HDC hdc, const Span &span, int y)
{
	int xdiff = span.X2 - span.X1;
	if(xdiff == 0)
		return;

	Color colordiff = span.Color2 - span.Color1;

	float factor = 0.0f;
	float factorStep = 1.0f / (float)xdiff;

	// draw each pixel in the span
	for (int x = span.X1; x < span.X2; x++) {
		//SetPixel(x, y, span.Color1 + (colordiff * factor));
		Color c = span.Color1 + (colordiff * factor);
		Vector3 c0(c.R, c.G, c.B);
		c0 = c0 * max(0, span.N1.DotProduct(-g_LightDir));

		//COLORREF color = RGB(c.R, c.G, c.B);
		COLORREF color = RGB((int)c0.x, (int)c0.y, (int)c0.z);
		SetPixel(hdc, x, y, color);
		factor += factorStep;
	}
}


void Rasterizer::DrawLine(HDC hdc, const Color &color1, float x1, float y1,
	const Color &color2, float x2, float y2)
{
	float xdiff = (x2 - x1);
	float ydiff = (y2 - y1);

	if(xdiff == 0.0f && ydiff == 0.0f) {
		COLORREF color = RGB(color1.R, color1.G, color1.B);
		SetPixel(hdc, (int)x1, (int)y1, color);
		return;
	}

	if(fabs(xdiff) > fabs(ydiff)) {
		float xmin, xmax;

		// set xmin to the lower x value given
		// and xmax to the higher value
		if(x1 < x2) {
			xmin = x1;
			xmax = x2;
		} else {
			xmin = x2;
			xmax = x1;
		}

		xmin = max(0, xmin);
		xmax = min(xmax, 800);

		// draw line in terms of y slope
		float slope = ydiff / xdiff;
		for(float x = xmin; x <= xmax; x += 1.0f) {
			float y = y1 + ((x - x1) * slope);
			Color color = color1 + ((color2 - color1) * ((x - x1) / xdiff));
			COLORREF c = RGB(color.R, color.G, color.B);
			SetPixel(hdc, (int)x, (int)y, c);
		}

	} else {
		float ymin, ymax;

		// set ymin to the lower y value given
		// and ymax to the higher value
		if(y1 < y2) {
			ymin = y1;
			ymax = y2;
		} else {
			ymin = y2;
			ymax = y1;
		}

		ymin = max(0, ymin);
		ymax = min(ymax, 600);

		// draw line in terms of x slope
		float slope = xdiff / ydiff;
		for(float y = ymin; y <= ymax; y += 1.0f) {
			float x = x1 + ((y - y1) * slope);
			Color color = color1 + ((color2 - color1) * ((y - y1) / ydiff));
			COLORREF c = RGB(color.R, color.G, color.B);
			SetPixel(hdc, (int)x, (int)y, c);
		}
	}
}

