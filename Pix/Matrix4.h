#pragma once

#include "Vertex.h"

struct Matrix4
{
	float	_11, _12, _13, _14,
			_21, _22, _23, _24,
			_31, _32, _33, _34,
			_41, _42, _43, _44;

	explicit Matrix4(float a11, float a12, float a13, float a14,
		float a21, float a22, float a23, float a24,
		float a31, float a32, float a33, float a34,
		float a41, float a42, float a43, float a44)
		: _11(a11), _12(a12), _13(a13), _14(a14),
		_21(a21), _22(a22), _23(a23), _24(a24),
		_31(a31), _32(a32), _33(a33), _34(a34),
		_41(a41), _42(a42), _43(a43), _44(a44)
	{

	}

	Matrix4 operator+(Matrix4 rhs) const
	{
		return Matrix4(_11 + rhs._11, _12 + rhs._12, _13 + rhs._13, _14 + rhs._14,
			_21 + rhs._21, _22 + rhs._22, _23 + rhs._23, _24 + rhs._24,
			_31 + rhs._31, _32 + rhs._32, _33 + rhs._33, _34 + rhs._34,
			_41 + rhs._41, _42 + rhs._42, _43 + rhs._43, _44 + rhs._44);
	}
	Matrix4 operator*(float s) const
	{
		return Matrix4(_11 * s, _12 * s, _13 * s, _14 * s,
			_21 * s, _22 * s, _23 * s, _24 * s,
			_31 * s, _32 * s, _33 * s, _34 * s,
			_41 * s, _42 * s, _43 * s, _44 * s);
	}
	Matrix4 operator*(Matrix4 rhs) const;

	static Matrix4 Identity()
	{
		return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}
	static Matrix4 RotationX(float rad);
	static Matrix4 RotationY(float rad);
	static Matrix4 RotationZ(float rad);
	static Matrix4 Scaling(float s);
	static Matrix4 Scaling(Vector3 s);
	static Matrix4 Scaling(float sx, float sy, float sz);
	static Matrix4 Translation(Vector3 d);
	static Matrix4 Translation(float dx, float dy, float dz);
};