#include "MathHelper.h"
#include <math.h>

float MathHelper::MagnitudeSquared(const Vector2& v)
{
	return 0.0f;
}

float MathHelper::MagnitudeSquared(const Vector3& v)
{
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

float MathHelper::Magnitude(const Vector2& v)
{
	return 0.0f;
}

float MathHelper::Magnitude(const Vector3& v)
{
	return sqrt(MagnitudeSquared(v));
}

Vector2 MathHelper::Normalize(const Vector2& v)
{
	return Vector2();
}

Vector3 MathHelper::Normalize(const Vector3& v)
{
	float invMag = 1.0f / Magnitude(v);
	return v * invMag;
}

float MathHelper::Dot(const Vector2& a, const Vector2& b)
{
	return a.x * b.x + a.y * b.y;
}

float MathHelper::Dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 MathHelper::Cross(const Vector3& a, const Vector3& b)
{
	return Vector3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}

float MathHelper::Lerp(float a, float b, float t)
{
	return a + ((b - a) * t);
}

float MathHelper::Determinant(const Matrix4& m)
{
	float det = 0.0f;
	det += (m._11 * (m._22 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._32 * m._44 - (m._42 * m._34)) + m._24 * (m._32 * m._43 - (m._42 * m._33))));
	det -= (m._12 * (m._21 * (m._33 * m._44 - (m._43 * m._34)) - m._23 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._43 - (m._41 * m._33))));
	det += (m._13 * (m._21 * (m._32 * m._44 - (m._42 * m._34)) - m._22 * (m._31 * m._44 - (m._41 * m._34)) + m._24 * (m._31 * m._42 - (m._41 * m._32))));
	det -= (m._14 * (m._21 * (m._32 * m._43 - (m._42 * m._33)) - m._22 * (m._31 * m._43 - (m._41 * m._33)) + m._23 * (m._31 * m._42 - (m._41 * m._32))));
	return det;
}

Matrix4 MathHelper::Adjoint(const Matrix4& m)
{
	return Matrix4(
		+(m._22 * ((m._33 * m._44) - (m._43 * m._34)) - m._23 * ((m._32 * m._44) - (m._42 * m._34)) + m._24 * ((m._32 * m._43) - (m._42 * m._33))),
		-(m._12 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._32 * m._44) - (m._42 * m._34)) + m._14 * ((m._32 * m._43) - (m._42 * m._33))),
		+(m._12 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._22 * m._44) - (m._42 * m._24)) + m._14 * ((m._22 * m._43) - (m._42 * m._23))),
		-(m._12 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._22 * m._34) - (m._32 * m._24)) + m._14 * ((m._22 * m._33) - (m._32 * m._23))),

		-(m._21 * ((m._33 * m._44) - (m._43 * m._34)) - m._31 * ((m._23 * m._44) - (m._24 * m._43)) + m._41 * ((m._23 * m._34) - (m._24 * m._33))),
		+(m._11 * ((m._33 * m._44) - (m._43 * m._34)) - m._13 * ((m._31 * m._44) - (m._41 * m._34)) + m._14 * ((m._31 * m._43) - (m._41 * m._33))),
		-(m._11 * ((m._23 * m._44) - (m._43 * m._24)) - m._13 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._43) - (m._41 * m._23))),
		+(m._11 * ((m._23 * m._34) - (m._33 * m._24)) - m._13 * ((m._21 * m._34) - (m._31 * m._24)) + m._14 * ((m._21 * m._33) - (m._31 * m._23))),

		+(m._21 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._22 * m._44) - (m._42 * m._24)) + m._41 * ((m._22 * m._34) - (m._32 * m._24))),
		-(m._11 * ((m._32 * m._44) - (m._42 * m._34)) - m._31 * ((m._12 * m._44) - (m._42 * m._14)) + m._41 * ((m._12 * m._34) - (m._32 * m._14))),
		+(m._11 * ((m._22 * m._44) - (m._42 * m._24)) - m._12 * ((m._21 * m._44) - (m._41 * m._24)) + m._14 * ((m._21 * m._42) - (m._41 * m._22))),
		-(m._11 * ((m._22 * m._34) - (m._32 * m._24)) - m._21 * ((m._12 * m._34) - (m._32 * m._14)) + m._31 * ((m._12 * m._24) - (m._22 * m._14))),

		-(m._21 * ((m._32 * m._43) - (m._42 * m._33)) - m._31 * ((m._22 * m._43) - (m._42 * m._23)) + m._41 * ((m._22 * m._33) - (m._32 * m._23))),
		+(m._11 * ((m._32 * m._43) - (m._42 * m._33)) - m._12 * ((m._31 * m._43) - (m._41 * m._33)) + m._13 * ((m._31 * m._42) - (m._41 * m._32))),
		-(m._11 * ((m._22 * m._43) - (m._42 * m._23)) - m._12 * ((m._21 * m._43) - (m._41 * m._23)) + m._13 * ((m._21 * m._42) - (m._41 * m._22))),
		+(m._11 * ((m._22 * m._33) - (m._32 * m._23)) - m._12 * ((m._21 * m._33) - (m._31 * m._23)) + m._13 * ((m._21 * m._32) - (m._31 * m._22)))
	);
}

Matrix4 MathHelper::Transpose(const Matrix4& m)
{
	return Matrix4(
		m._11, m._21, m._31, m._41,
		m._12, m._22, m._32, m._42,
		m._13, m._23, m._33, m._43,
		m._14, m._24, m._34, m._44
	);
}

Matrix4 MathHelper::Inverse(const Matrix4& m)
{
	const float determinant = Determinant(m);
	const float invDet = 1.0f / determinant;
	return Adjoint(m) * invDet;
}

Vector3 MathHelper::TransformCoord(const Vector3& v, const Matrix4& m)
{
	const float w = ((v.x * m._14) + (v.y * m._24) + (v.z * m._34) + (1.0f * m._44));
	const float invW = (w == 0.0f) ? 1.0f : 1 / w;
	return {
		((v.x * m._11) + (v.y * m._21) + (v.z * m._31) + (1.0f * m._41)) * invW,
		((v.x * m._12) + (v.y * m._22) + (v.z * m._32) + (1.0f * m._42)) * invW,
		((v.x * m._13) + (v.y * m._23) + (v.z * m._33) + (1.0f * m._43)) * invW
	};
}

Vector3 MathHelper::TransformNormal(const Vector3& v, const Matrix4& m)
{
	return {
		(v.x * m._11) + (v.y * m._21) + (v.z * m._31),
		(v.x * m._12) + (v.y * m._22) + (v.z * m._32),
		(v.x * m._13) + (v.y * m._23) + (v.z * m._33)
	};
}

Matrix4 Matrix4::Translation(Vector3 d)
{
	return Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		d.x,  d.y,  d.z,  1.0f
	);
}

Matrix4 Matrix4::RotationX(float radian)
{
	const float s = sinf(radian);
	const float c = cosf(radian);
	return Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, c,    s,    0.0f,
		0.0f, -s,   c,    0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4 Matrix4::RotationY(float radian)
{
	const float s = sinf(radian);
	const float c = cosf(radian);
	return Matrix4(
		c,    0.0f, -s,   0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		s,    0.0f, c,    0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4 Matrix4::RotationZ(float radian)
{
	const float s = sinf(radian);
	const float c = cosf(radian);
	return Matrix4(
		c,    s,    0.0f, 0.0f,
		-s,   c,    0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4 Matrix4::Scaling(float s)
{
	return Matrix4(
		s,    0.0f, 0.0f, 0.0f,
		0.0f, s,    0.0f, 0.0f,
		0.0f, 0.0f, s,    0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4 Matrix4::Scaling(Vector3 s)
{
	return Matrix4(
		s.x,  0.0f, 0.0f, 0.0f,
		0.0f, s.y,  0.0f, 0.0f,
		0.0f, 0.0f, s.z,  0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}
