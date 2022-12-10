#pragma once
#include "MathHelper.h"
#include <XEngine.h>

struct Vertex
{
	Vector3 Position;
	Vector3 WorldPosition;
	Vector3 WorldNormal;
	Vector3 Normal;
	X::Color Color;
};

inline static Vector3 LerpPosition(Vector3 a, Vector3 b, float t)
{
	Vector3 pos;
	pos.x = MathHelper::Lerp(a.x, b.x, t);
	pos.y = MathHelper::Lerp(a.y, b.y, t);
	pos.z = MathHelper::Lerp(a.z, b.z, t);
	return pos;
}

inline static Vector3 LerpNormal(Vector3 a, Vector3 b, float t)
{
	Vector3 norm;
	norm.x = MathHelper::Lerp(a.x, b.x, t);
	norm.y = MathHelper::Lerp(a.y, b.y, t);
	norm.z = MathHelper::Lerp(a.z, b.z, t);
	return MathHelper::Normalize(norm);
}
inline static X::Color LerpColor(X::Color a, X::Color b, float t)
{
	X::Color color;
	color.x = MathHelper::Lerp(a.x, b.x, t);
	color.y = MathHelper::Lerp(a.y, b.y, t);
	color.z = MathHelper::Lerp(a.z, b.z, t);
	color.w = MathHelper::Lerp(a.w, b.w, t);
	color.r = color.x;
	color.g = color.y;
	color.b = color.z;
	color.a = color.w;
	return color;
}
inline static Vertex LerpVertex(Vertex a, Vertex b, float t, bool learpNorm = false)
{
	Vertex vertex;
	vertex.Position = LerpPosition(a.Position, b.Position, t);
	vertex.Normal = LerpPosition(a.Normal, b.Position, t);
	vertex.WorldPosition = LerpPosition(a.WorldPosition, b.WorldPosition, t);
	vertex.WorldNormal = LerpPosition(a.WorldNormal, b.WorldNormal, t);
	vertex.Color = LerpColor(a.Color, b.Color, t);
	if (learpNorm)
	{
		vertex.Normal = LerpNormal(a.Normal, b.Position, t);
		vertex.WorldNormal = LerpPosition(a.WorldNormal, b.WorldNormal, t);
	}
	return vertex;
}
