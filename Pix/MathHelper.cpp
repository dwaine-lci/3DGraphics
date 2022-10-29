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
	return 0.0f;
}

Vector3 MathHelper::Cross(const Vector3& a, const Vector3& b)
{
	return Vector3();
}

float MathHelper::Lerp(float a, float b, float t)
{
	return a + ((b - a) * t);
}