#pragma once
#include "Vertex.h"

enum class Topology
{
	Point,
	Line,
	Triangle
};

enum class CullMode
{
	None, // No culling
	Front, // Cull primitives that are front facing (clockwise)
	Back // Cull primitives that are back facing (counter-clockwise)
};

class PrimitivesManager
{
public:
	virtual ~PrimitivesManager();
	static PrimitivesManager* Get();

	void SetCullMode(CullMode mode);

	bool BeginDraw(Topology topology, bool applyTransform);
	void AddVertex(Vertex vertex);
	bool EndDraw();

private:
	PrimitivesManager();
	std::vector<Vertex> mVertexBuffer;
	CullMode mCullMode = CullMode::Back;
	Topology mTopology = Topology::Triangle;
	bool mDrawBegin = false;
	bool mApplyTransform = false;
};