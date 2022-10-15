#pragma once

struct Vector2
{
	float x, y;

	Vector2()
		: x(0.0f)
		, y(0.0f)
	{

	}
};
struct Vector3
{
	float x, y, z;

	Vector3()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{

	}
};

class MathHelper
{
public:
	static float MagnitudeSquared(const Vector2& v);
	static float MagnitudeSquared(const Vector3& v);
	static float Magnitude(const Vector2& v);
	static float Magnitude(const Vector3& v);
	static Vector2 Normalize(const Vector2& v);
	static Vector3 Normalize(const Vector3& v);
	static float Dot(const Vector2& a, const Vector2& b);
	static float Dot(const Vector3& a, const Vector3& b);
	static Vector3 Cross(const Vector3& a, const Vector3& b);
	static float Lerp(float a, float b, float t);
};