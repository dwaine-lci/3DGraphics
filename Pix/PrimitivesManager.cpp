#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "MatrixStack.h"
#include "Camera.h"
#include "LightManager.h"

extern float gResolutionX;
extern float gResolutionY;

namespace
{
	Matrix4 GetScreenTransform()
	{
		float hw = gResolutionX * 0.5f;
		float hh = gResolutionY * 0.5f;
		return Matrix4(
			hw, 0.0f, 0.0f, 0.0f,
			0.0f, -hh, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			hw, hh, 0.0f, 1.0f
		);
	}
}

PrimitivesManager::PrimitivesManager()
{

}
PrimitivesManager::~PrimitivesManager()
{

}
PrimitivesManager* PrimitivesManager::Get()
{
	static PrimitivesManager sInstance;
	return &sInstance;
}

void PrimitivesManager::OnNewFrame()
{
	mCullMode = CullMode::Back;
	mCorrectUV = true;
}

void PrimitivesManager::SetCullMode(CullMode mode)
{
	mCullMode = mode;
}
void PrimitivesManager::SetCorrectUV(bool correctUV)
{
	mCorrectUV = correctUV;
}

bool PrimitivesManager::BeginDraw(Topology topology, bool applyTransform)
{
	mDrawBegin = true;
	mApplyTransform = applyTransform;
	mTopology = topology;
	mVertexBuffer.clear();
	return true;
}
void PrimitivesManager::AddVertex(Vertex vertex)
{
	if (mDrawBegin)
	{
		mVertexBuffer.push_back(vertex);
	}
}
bool PrimitivesManager::EndDraw()
{
	if (!mDrawBegin)
	{
		return false;
	}

	switch (mTopology)
	{
	case Topology::Point:
		for (size_t i = 0; i < mVertexBuffer.size(); ++i)
		{
			if (Clipper::Get()->ClipPoint(mVertexBuffer[i]))
			{
				Rasterizer::Get()->DrawPoint(mVertexBuffer[i]);
			}
		}
		break;
	case Topology::Line:
		for (size_t i = 1; i < mVertexBuffer.size(); i += 2)
		{
			if (Clipper::Get()->ClipLine(mVertexBuffer[i - 1], mVertexBuffer[i]))
			{
				Rasterizer::Get()->DrawLine(mVertexBuffer[i - 1], mVertexBuffer[i]);
			}
		}
		break;
	case Topology::Triangle:

		Matrix4 matWorld = MatrixStack::Get()->GetTransform();
		Matrix4 matView = Camera::Get()->GetViewMatrix();
		Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
		Matrix4 matScreen = GetScreenTransform();
		Matrix4 matFinal = matProj * matScreen;  // matWorld * matView * matProj * matScreen

		for (size_t i = 2; i < mVertexBuffer.size(); i += 3)
		{
			std::vector<Vertex> triangle = { mVertexBuffer[i - 2], mVertexBuffer[i - 1], mVertexBuffer[i] };

			if (mApplyTransform)
			{
				if (MathHelper::MagnitudeSquared(triangle[0].Normal) < 0.5f)
				{
					Vector3 faceNorm = MathHelper::Normalize(MathHelper::Cross((triangle[1].Position - triangle[0].Position),
						(triangle[2].Position - triangle[0].Position)));

					for (auto& v : triangle)
					{
						v.Normal = faceNorm;
					}
				}
				// This transforms all vertecies into world position
				// move all the vertecies to the world
				for (auto& v : triangle)
				{
					v.Position = MathHelper::TransformCoord(v.Position, matWorld);
					v.Normal = MathHelper::TransformNormal(v.Normal, matWorld);

					// cache here so we dont need to do more math
					v.WorldPosition = v.Position;
					v.WorldNormal = v.Normal;
				}

				// color from lighting based on world position of object and light
				if (Rasterizer::Get()->GetShadeMode() != ShadeMode::Phong)
				{
					// apply color
					for (auto& v : triangle)
					{
						v.Color *= LightManager::Get()->ComputeLightColor(v.Position, v.Normal);
					}
				}

				for (auto& v : triangle)
				{
					v.Position = MathHelper::TransformCoord(v.Position, matView);
					v.Normal = MathHelper::TransformNormal(v.Normal, matView);
				}

				if (mCorrectUV && triangle[0].Color.z < 0.0f)
				{
					for (auto& v : triangle)
					{
						v.Color.x /= v.Position.z;
						v.Color.y /= v.Position.z;
						v.Color.w = 1.0f / v.Position.z;
					}
				}

				if (mCullMode != CullMode::None)
				{
					// move from world to NDC
					for (auto& v : triangle)
					{
						v.Position = MathHelper::TransformCoord(v.Position, matProj);
						v.Normal = MathHelper::TransformNormal(v.Normal, matProj);
					}

					// get facing at NDC to determin CULL
					Vector3 faceNorm = MathHelper::Normalize(MathHelper::Cross((triangle[1].Position - triangle[0].Position),
														(triangle[2].Position - triangle[0].Position)));

					if (mCullMode == CullMode::Back && faceNorm.z > 0.0f)
					{
						continue;
					}
					else if (mCullMode == CullMode::Front && faceNorm.z < 0.0f)
					{
						continue;
					}

					// move to screen space
					for (auto& v : triangle)
					{
						auto posScreen = MathHelper::TransformCoord(v.Position, matScreen);
						v.Position = posScreen;
					}
				}
				else
				{
					for (auto& v : triangle)
					{
						auto posScreen = MathHelper::TransformCoord(v.Position, matFinal);
						v.Position = posScreen;
					}
				}
			}
			if (Clipper::Get()->ClipTriangle(triangle))
			{
				for (size_t t = 2; t < triangle.size(); ++t)
				{
					Rasterizer::Get()->DrawTriangle(triangle[0], triangle[t - 1], triangle[t]);
				}
			}
		}
		break;
	default:
		// throw error here
		return false;
		break;
	}

	mDrawBegin = false;

	return true;
}