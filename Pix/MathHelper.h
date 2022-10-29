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

	constexpr Vector3() : x(0.0f), y(0.0f), z(0.0f) {}
	constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

	Vector3 operator-() const { return { -x, -y, -z }; }

	Vector3 operator+(Vector3 b) const { return { x + b.x, y + b.y, z + b.z }; }
	Vector3 operator-(Vector3 b) const { return { x - b.x, y - b.y, z - b.z }; }
	Vector3 operator*(float s) const { return { x * s, y * s, z * s }; }
	Vector3 operator/(float s) const { return { x / s, y / s, z / s }; }

	Vector3& operator/=(float s) { x /= s; y /= s, z /= s; return *this; }
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

	Vector3 TransformCoord(Vector3 v, Matrix4 m); // assume w = 1
	Vector3 TransformNormal(Vector3 v, Matrix4 m); // assume w = 0
	float Determinant(Matrix4 m);
	Matrix4 Adjoint(Matrix4 m);
	Matrix4 Transpose(Matrix4 m);
	Matrix4 Inverse(Matrix4 m);

};