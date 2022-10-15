#pragma once

#include "Vertex.h"
#include <XEngine.h>

enum class FillMode
{
	Solid,
	Wireframe
};

class Rasterizer
{
public:
	static Rasterizer* Get();

public:
	void SetColor(X::Color color);
	void SetFillMode(FillMode mode);

	void DrawPoint(int x, int y);

	void DrawPoint(const Vertex& v);
	void DrawLine(const Vertex& v1, const Vertex& v2);
	void DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3);

private:

	X::Color mColor = X::Colors::White;
	FillMode mFillMode = FillMode::Solid;
};