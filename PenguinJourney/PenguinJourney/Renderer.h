#pragma once


void RenderVertices(HDC hdc, const vector<Vector3> &vertices, const Matrix44 &tm);

void RenderIndices(HDC hdc, const vector<Vector3> &vertices, const vector<int> &indices, 
	const vector<Vector3> &normals, const Matrix44 &tm, const Matrix44 &vpv);

void RenderIndices(HDC hdc, const vector<Vector3> &vertices, const vector<int> &indices, const Matrix44 &tm);
