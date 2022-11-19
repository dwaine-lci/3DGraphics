#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "MatrixStack.h"
#include "Camera.h"

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

void PrimitivesManager::SetCullMode(CullMode mode)
{
	mCullMode = mode;
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
		Matrix4 ndcSpace = matWorld * matView * matProj;
		Matrix4 matFinal = ndcSpace * matScreen;

		for (size_t i = 2; i < mVertexBuffer.size(); i += 3)
		{
			std::vector<Vertex> triangle = { mVertexBuffer[i - 2], mVertexBuffer[i - 1], mVertexBuffer[i] };

			if (mApplyTransform)
			{
				if (mCullMode != CullMode::None)
				{
					for (auto& v : triangle)
					{
						auto posNdc = MathHelper::TransformCoord(v.Position, ndcSpace);
						v.Position = posNdc;
					}

					Vector3 faceNorm = MathHelper::Cross((triangle[1].Position - triangle[0].Position), 
														(triangle[2].Position - triangle[0].Position));
					if (mCullMode == CullMode::Back && faceNorm.z > 0.0f)
					{
						continue;
					}
					else if (mCullMode == CullMode::Front && faceNorm.z < 0.0f)
					{
						continue;
					}
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