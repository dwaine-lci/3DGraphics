#include "Camera.h"

#include <cmath>

extern float gResolutionX;
extern float gResolutionY;

Camera* Camera::Get()
{
	static Camera sInstance;
	return &sInstance;
}

void Camera::OnNewFrame()
{
	mPosition = { 0.0f, 0.0f, 0.0f };
	mDirection = { 0.0f, 0.0f, 1.0f };
	mNearPlane = 0.01f;
	mFarPlane = 100.0f;
	mFOV = 1.57f;
}

void Camera::SetPosition(Vector3 position)
{
	mPosition = position;
}

void Camera::SetDirection(Vector3 direction)
{
	auto dir = Normalize(direction);
	if (fabs(Dot(dir, { 0.0f, 1.0f, 0.0f })) < 0.995f)
		mDirection = dir;
}

void Camera::SetNearPlane(float nearPlane)
{
	mNearPlane = nearPlane;
}

void Camera::SetFarPlane(float farPlane)
{
	mFarPlane = farPlane;
}

void Camera::SetFOV(float fov)
{
	mFOV = fov;
}

Vector3 Camera::GetPosition() const
{
	return mPosition;
}

Vector3 Camera::GetDirection() const
{
	return mDirection;
}

Matrix4 Camera::GetViewMatrix() const
{
	const Vector3 l = mDirection;
	const Vector3 r = Normalize(Cross({ 0.0f, 1.0f, 0.0f }, l));
	const Vector3 u = Normalize(Cross(l, r));
	const float dx = -Dot(r, mPosition);
	const float dy = -Dot(u, mPosition);
	const float dz = -Dot(l, mPosition);
	return {
		r.x, u.x, l.x, 0.0f,
		r.y, u.y, l.y, 0.0f,
		r.z, u.z, l.z, 0.0f,
		dx,  dy,  dz,  1.0f
	};
}

Matrix4 Camera::GetProjectionMatrix() const
{
	const float aspect = gResolutionX / gResolutionY;
	const float h = 1 / tan(mFOV * 0.5f);
	const float w = h / aspect;
	const float zf = mFarPlane;
	const float zn = mNearPlane;
	const float d = zf / (zf - zn);

	return {
		w,    0.0f, 0.0f,    0.0f,
		0.0f, h,    0.0f,    0.0f,
		0.0f, 0.0f, d,       1.0f,
		0.0f, 0.0f, -zn * d, 0.0f
	};
}