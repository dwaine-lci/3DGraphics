#include "Rasterizer.h"
#include "DepthBuffer.h"

Rasterizer* Rasterizer::Get()
{
	static Rasterizer sInstance;
	return &sInstance;
}

void Rasterizer::SetColor(X::Color color)
{
	mColor = color;
}

void Rasterizer::SetFillMode(FillMode mode)
{
	mFillMode = mode;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, mColor);
}
void Rasterizer::DrawPoint(const Vertex& v)
{
	X::DrawPixel(v.Position.x, v.Position.y, v.Color);
}

void Rasterizer::DrawLine(const Vertex& v1, const Vertex& v2)
{
	//we lerp from v1 to v2
	//draw point
}
void Rasterizer::DrawTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	switch (mFillMode)
	{
	case FillMode::Wireframe:
		// use draw line
		break;
	case FillMode::Solid:
		// use the edge walk algorithm
		break;
	default:
		break;
	}
}