#include "Rasterizer.h"
#include "DepthBuffer.h"
#include "LightManager.h"

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

void Rasterizer::SetShadeMode(ShadeMode mode)
{
	mShadeMode = mode;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, mColor);
}
void Rasterizer::DrawPoint(const Vertex& v)
{
	if (DepthBuffer::Get()->CheckDepthBuffer(v.Position.x, v.Position.y, v.Position.z))
	{
		X::DrawPixel(v.Position.x, v.Position.y, v.Color);
	}
}

void Rasterizer::DrawLine(const Vertex& v1, const Vertex& v2)
{
	//we lerp from v1 to v2
	//draw point
	// y = mx + b
	float dx = v2.Position.x - v1.Position.x;
	float dy = v2.Position.y - v1.Position.y;
	if (std::abs(dx) < 0.01f)
	{
		// y is straight up
		float startY, endY;
		X::Color startColor, endColor;
		if (v1.Position.y < v2.Position.y)
		{
			startY = v1.Position.y;
			endY = v2.Position.y;
		}
		else
		{
			startY = v2.Position.y;
			endY = v1.Position.y;
		}
		for (float y = startY; y <= endY; ++y)
		{
			float t = (y - startY) / (endY - startY);
			Vertex v = LerpVertex(v1, v2, t, mShadeMode == ShadeMode::Phong);
			if (mShadeMode == ShadeMode::Phong)
			{
				Vector3 worldPos = LerpPosition(v1.WorldPosition, v2.WorldPosition, t);
				v.Color *= LightManager::Get()->ComputeLightColor(v.Position, v.WorldNormal);
			}
			DrawPoint(v);
		}
	}
	else
	{
		float m = dy / dx;
		float b = (v2.Position.y - (m * v2.Position.x));
		if (std::abs(dy) < std::abs(dx))
		{
			Vertex startV, endV;
			if (v1.Position.x < v2.Position.x)
			{
				startV = v1;
				endV = v2;
			}
			else
			{
				startV = v2;
				endV = v1;
			}
			for (float x = startV.Position.x; x <= endV.Position.x; ++x)
			{
				float t = (x - startV.Position.x) / (endV.Position.x - startV.Position.x);
				float y = startV.Position.y + (endV.Position.y - startV.Position.y) * t;
				float depth = startV.Position.z + (endV.Position.z - startV.Position.z) * t;
				if (DepthBuffer::Get()->CheckDepthBuffer(x, y, depth))
				{
					Vertex v = LerpVertex(startV, endV, t, mShadeMode == ShadeMode::Phong);
					if (mShadeMode == ShadeMode::Phong)
					{
						Vector3 worldPos = LerpPosition(v1.WorldPosition, v2.WorldPosition, t);
						v.Color *= LightManager::Get()->ComputeLightColor(v.Position, v.WorldNormal);
					}
					DrawPoint(v);
				}
			}
		}
		else
		{
			Vertex startV, endV;
			if (v1.Position.y < v2.Position.y)
			{
				startV = v1;
				endV = v2;
			}
			else
			{
				startV = v2;
				endV = v1;
			}
			for (float y = startV.Position.y; y <= endV.Position.y; ++y)
			{
				float t = (y - startV.Position.y) / (endV.Position.y - startV.Position.y);
				float x = startV.Position.x + (endV.Position.x - startV.Position.x) * t;
				float depth = startV.Position.z + (endV.Position.z - startV.Position.z) * t;
				if (DepthBuffer::Get()->CheckDepthBuffer(x, y, depth))
				{
					Vertex v = LerpVertex(v1, v2, t, mShadeMode == ShadeMode::Phong);
					if (mShadeMode == ShadeMode::Phong)
					{
						Vector3 worldPos = LerpPosition(v1.WorldPosition, v2.WorldPosition, t);
						v.Color *= LightManager::Get()->ComputeLightColor(v.Position, v.WorldNormal);
					}
					DrawPoint(v);
				}
			}
		}
	}
}
void Rasterizer::DrawTriangle(Vertex v1, Vertex v2, Vertex v3)
{
	if (mShadeMode == ShadeMode::Flat)
	{
		v2.Color = v1.Color;
		v3.Color = v1.Color;

		Vector3 faceNorm = MathHelper::Normalize(MathHelper::Cross((v2.Position - v1.Position),
			(v3.Position - v1.Position)));
		v1.Normal = faceNorm;
		v2.Normal = faceNorm;
		v3.Normal = faceNorm;
	}

	switch (mFillMode)
	{
	case FillMode::Wireframe:
		DrawLine(v1, v2);
		DrawLine(v2, v3);
		DrawLine(v3, v1);
		break;
	case FillMode::Solid:
	{
		std::vector<Vertex> sortedVertexes;
		sortedVertexes.push_back(v1);
		sortedVertexes.push_back(v2);
		sortedVertexes.push_back(v3);
		std::sort(sortedVertexes.begin(), sortedVertexes.end(), [](const Vertex& lhs, const Vertex& rhs) { return lhs.Position.y < rhs.Position.y; });
		DrawTriangleFilled(sortedVertexes[0], sortedVertexes[1], sortedVertexes[2]);
		break;
	}
	default:
		break;
	}
}
void Rasterizer::DrawTriangleFilled(const Vertex& v1, const Vertex& v2, const Vertex& v3)
{
	// should be top
	if (MathHelper::CheckEquals(v1.Position.y, v2.Position.y))
	{
		float dy = v1.Position.y - v3.Position.y;
		Vertex topLeft, topRight;
		if (v1.Position.x < v2.Position.x)
		{
			topLeft = v1;
			topRight = v2;
		}
		else
		{
			topLeft = v2;
			topRight = v1;
		}
		for (int y = v1.Position.y; y <= v3.Position.y; ++y)
		{
			float t = (y - v1.Position.y) / (v3.Position.y - v1.Position.y);
			Vertex leftVertex = LerpVertex(topLeft, v3, t);
			Vertex rightVertex = LerpVertex(topRight, v3, t);
			DrawLine(leftVertex, rightVertex);
		}
	}
	// should be bottom
	else if(MathHelper::CheckEquals(v2.Position.y, v3.Position.y))
	{
		float dy = v1.Position.y - v3.Position.y;
		Vertex bottomLeft, bottomRight;
		if (v2.Position.x < v3.Position.x)
		{
			bottomLeft = v2;
			bottomRight = v3;
		}
		else
		{
			bottomLeft = v3;
			bottomRight = v2;
		}
		for (int y = v1.Position.y; y <= v3.Position.y; ++y)
		{
			float t = (y - v1.Position.y) / (v3.Position.y - v1.Position.y);
			Vertex leftVertex = LerpVertex(v1, bottomLeft, t);
			Vertex rightVertex = LerpVertex(v1, bottomRight, t);
			DrawLine(leftVertex, rightVertex);
		}

	}
	else
	{
		float t = (v2.Position.y - v1.Position.y) / (v3.Position.y - v1.Position.y);
		Vertex splitVertex = LerpVertex(v1, v3, t);
		// bottom flat
		DrawTriangleFilled(v1, v2, splitVertex);
		// top flat
		DrawTriangleFilled(v2, splitVertex, v3);
	}
}