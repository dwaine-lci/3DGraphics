#pragma once

#include "Vertex.h"
#include <XEngine.h>

enum class FillMode
{
	Solid,
	Wireframe
};

enum class ShadeMode
{
	Flat,
	Gouraud,
	Phong
};

class Rasterizer
{
public:
	static Rasterizer* Get();

public:
	void SetColor(X::Color color);
	void SetFillMode(FillMode mode);
	void SetShadeMode(ShadeMode mode);
	ShadeMode GetShadeMode() { return mShadeMode; }

	void DrawPoint(int x, int y);

	void DrawPoint(const Vertex& v);
	void DrawLine(const Vertex& v1, const Vertex& v2);
	void DrawTriangle(Vertex v1, Vertex v2, Vertex v3);

private:
	void DrawTriangleFilled(const Vertex& v1, const Vertex& v2, const Vertex& v3);

	X::Color mColor = X::Colors::White;
	FillMode mFillMode = FillMode::Solid;
	ShadeMode mShadeMode = ShadeMode::Gouraud;
};