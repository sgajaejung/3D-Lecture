/**
 @filename Vector4.h
 
 
*/
#pragma once

struct Vector3;
struct Matrix44;

struct Vector4
{
	Vector4() {}
	Vector4(const Vector3 &v);
	Vector4(float x0, float y0, float z0, float w0) : x(x0), y(y0), z(z0), w(w0) {}
	Vector4 operator * ( const Matrix44& m );
	Vector4 operator = (const Vector3 &v) { x=v.x, y=v.y, z=v.z, w=1; }
	Vector4 operator += (const Vector4 &v);

	float x,y,z,w;
};
