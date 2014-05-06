
#include "stdafx.h"
#include "vector3.h"
#include "matrix44.h"


Matrix44::Matrix44()
{
	SetIdentity();
}

void Matrix44::SetIdentity()
{
	_11 = _22 = _33 = _44 = 1;
	_12 = _13 = _14 = _21 = _23 = _24 = _31 = _32 = _34 = _41 = _42 = _43 = 0;
}


void	Matrix44::SetRotationX( const float angle )
{

}


void	Matrix44::SetRotationY( const float angle )
{

}


void	Matrix44::SetRotationZ( const float angle )
{

}


void	Matrix44::Translate( const Vector3& pos )
{

}


void	Matrix44::SetScale( const Vector3& scale)
{

}


Vector3 Matrix44::GetPosition() const
{
	return Vector3(_41, _42, _43);
}


Matrix44 Matrix44::operator * ( const Matrix44& rhs ) const
{
	Matrix44 matrix;
	ZeroMemory( &matrix, sizeof( matrix ) );

	for( int i = 0 ; i < 4 ; ++i )
	{
		for( int j = 0 ; j < 4 ; ++j )
		{			
			for( int k = 0 ; k < 4 ; ++k )
			{
				matrix.m[i][j] += m[i][k] * rhs.m[k][j];
			} //for
		} //for 
	} //for

	return matrix;
}


Matrix44& Matrix44::operator *= ( const Matrix44& rhs )
{
	Matrix44 matrix;
	ZeroMemory( &matrix, sizeof( matrix ) );

	for( int i = 0 ; i < 4 ; ++i )
	{
		for( int j = 0 ; j < 4 ; ++j )
		{			
			for( int k = 0 ; k < 4 ; ++k )
			{
				matrix.m[i][j] += m[i][k] * rhs.m[k][j];
			} //for
		} //for 
	} //for

	*this = matrix;
	return *this;
}
