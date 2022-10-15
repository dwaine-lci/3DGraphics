#pragma once
#include "MathHelper.h"
#include <XEngine.h>

struct Vertex
{
	Vector3 Position;
	X::Color Color;
};

inline Vector3 LerpPosition(Vector3 a, Vector3 b, float t)
{
	Vector3 pos;
	pos.x = MathHelper::Lerp(a.x, b.x, t);
	pos.y = MathHelper::Lerp(a.y, b.y, t);
	pos.z = MathHelper::Lerp(a.z, b.z, t);
	return pos;
}
inline X::Color LerpColor(X::Color a, X::Color b, float t)
{
	X::Color color;
	color.x = MathHelper::Lerp(a.x, b.x, t);
	color.y = MathHelper::Lerp(a.y, b.y, t);
	color.z = MathHelper::Lerp(a.z, b.z, t);
	return color;
}
inline Vertex LerpVertex(Vertex a, Vertex b, float t)
{
	Vertex vertex;
	vertex.Position = LerpPosition(a.Position, b.Position, t);
	vertex.Color = LerpColor(a.Color, b.Color, t);
	return vertex;
}