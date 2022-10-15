#pragma once
#include "Vertex.h"

enum class Topology
{
	Point,
	Line,
	Triangle
};

class PrimitivesManager
{
public:
	virtual ~PrimitivesManager();
	static PrimitivesManager* Get();

	bool BeginDraw(Topology topology);
	void AddVertex(Vertex vertex);
	bool EndDraw();

private:
	PrimitivesManager();
	std::vector<Vertex> mVertexBuffer;
	Topology mTopology = Topology::Triangle;
	bool mDrawBegin = false;
};