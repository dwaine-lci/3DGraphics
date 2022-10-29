#include "Clipper.h"
#include "Viewport.h"

const int BIT_INSIDE = 0;	  // 0000
const int BIT_LEFT = 1 << 1; // 0001
const int BIT_RIGHT = 1 << 2; // 0010
const int BIT_BOTTOM = 1 << 3; // 0100
const int BIT_TOP = 1 << 4; // 1000

enum class ClipEdge : int { Left, Bottom, Right, Top, Count };

bool IsInFront(ClipEdge edge, const Vector3& pnt)
{
	float maxX = Viewport::Get()->GetMaxX();
	float maxY = Viewport::Get()->GetMaxY();
	float minX = Viewport::Get()->GetMinX();
	float minY = Viewport::Get()->GetMinY();

	switch (edge)
	{
	case ClipEdge::Left:	return pnt.x > minX;
	case ClipEdge::Bottom:	return pnt.y < maxY;
	case ClipEdge::Right:	return pnt.x < maxX;
	case ClipEdge::Top:		return pnt.y > minY;
	default:
		break;
	}
	return false;
}

Vertex ComputeIntersection(ClipEdge edge, const Vertex& v1, const Vertex& v2)
{
	float maxX = Viewport::Get()->GetMaxX();
	float maxY = Viewport::Get()->GetMaxY();
	float minX = Viewport::Get()->GetMinX();
	float minY = Viewport::Get()->GetMinY();

	float t = 0.0f;
	switch (edge)
	{
	case ClipEdge::Left:
		t = (minX - v1.Position.x) / (v2.Position.x - v1.Position.x);
		break;
	case ClipEdge::Bottom:
		t = (maxY - v1.Position.y) / (v2.Position.y - v1.Position.y);
		break;
	case ClipEdge::Right:
		t = (maxX - v1.Position.x) / (v2.Position.x - v1.Position.x);
		break;
	case ClipEdge::Top:
		t = (minY - v1.Position.y) / (v2.Position.y - v1.Position.y);
		break;
	default:
		break;
	}

	return LerpVertex(v1, v2, t);
}

int GetOutputCode(float x, float y)
{
	int code = BIT_INSIDE;  // initialised as being inside of clip window

	if (x < Viewport::Get()->GetMinX())           // to the left of clip window
		code |= BIT_LEFT;
	else if (x > Viewport::Get()->GetMaxX())      // to the right of clip window
		code |= BIT_RIGHT;
	if (y > Viewport::Get()->GetMaxY())           // below the clip window
		code |= BIT_BOTTOM;
	else if (y < Viewport::Get()->GetMinY())      // above the clip window
		code |= BIT_TOP;

	return code;

}

Clipper::Clipper()
{

}
Clipper::~Clipper()
{

}
Clipper* Clipper::Get()
{
	static Clipper sInstance;
	return &sInstance;
}

void Clipper::OnNewFrame()
{

}
bool Clipper::ClipPoint(const Vertex& v)
{
	if (mClipping)
	{
		float maxX = Viewport::Get()->GetMaxX();
		float maxY = Viewport::Get()->GetMaxY();
		float minX = Viewport::Get()->GetMinX();
		float minY = Viewport::Get()->GetMinY();

		return v.Position.x >= minX && v.Position.x <= maxX
			&& v.Position.y >= minY && v.Position.y <= maxY;
	}
	return true;
}
bool Clipper::ClipLine(Vertex& v1, Vertex& v2)
{
	if (mClipping)
	{
		float maxX = Viewport::Get()->GetMaxX();
		float maxY = Viewport::Get()->GetMaxY();
		float minX = Viewport::Get()->GetMinX();
		float minY = Viewport::Get()->GetMinY();
		int codeV1 = GetOutputCode(v1.Position.x, v1.Position.y);
		int codeV2 = GetOutputCode(v2.Position.x, v2.Position.y);
		bool accept = false;

		while (true)
		{
			if (!(codeV1 | codeV2))
			{
				// bitwise OR is 0: both points inside window; trivially accept and exit loop
				accept = true;
				break;
			}
			else if (codeV1 & codeV2)
			{
				// bitwise AND is not 0: both points share an outside zone (LEFT, RIGHT, TOP,
				// or BOTTOM), so both must be outside window; exit loop (accept is false)
				break;
			}
			else
			{
				// failed both tests, so calculate the line segment to clip
				// from an outside point to an intersection with clip edge
				
				float t = 0.0f;
				// At least one endpoint is outside the clip rectangle; pick it.
				int outcodeOut = codeV2 > codeV1 ? codeV2 : codeV1;

				// Now find the intersection point;
				// use formulas:
				//   slope = (y1 - y0) / (x1 - x0)
				//   x = x0 + (1 / slope) * (ym - y0), where ym is ymin or ymax
				//   y = y0 + slope * (xm - x0), where xm is xmin or xmax
				// No need to worry about divide-by-zero because, in each case, the
				// outcode bit being tested guarantees the denominator is non-zero
				if (outcodeOut & BIT_TOP)
				{
					// point is above the clip window
					t = (minY - v1.Position.y) / (v2.Position.y - v1.Position.y);
				}
				else if (outcodeOut & BIT_BOTTOM)
				{
					// point is below the clip window
					t = (maxY - v1.Position.y) / (v2.Position.y - v1.Position.y);
				}
				else if (outcodeOut & BIT_RIGHT)
				{ 
					// point is to the right of clip window
					t = (maxX - v1.Position.x) / (v2.Position.x - v1.Position.x);
				}
				else if (outcodeOut & BIT_LEFT)
				{
					// point is to the left of clip window
					t = (minX - v1.Position.x) / (v2.Position.x - v1.Position.x);
				}

				// Now we move outside point to intersection point to clip
				// and get ready for next pass.
				if (outcodeOut == codeV1)
				{
					v1 = LerpVertex(v1, v2, t);
					codeV1 = GetOutputCode(v1.Position.x, v1.Position.y);
				}
				else
				{
					v2 = LerpVertex(v1, v2, t);
					codeV2 = GetOutputCode(v2.Position.x, v2.Position.y);
				}
			}
		}
		return accept;
	}
	return true;
}
bool Clipper::ClipTriangle(std::vector<Vertex>& vertices)
{
	if (mClipping)
	{
		std::vector<Vertex> newVertices;
		for (int i = 0; i < (int)ClipEdge::Count; ++i)
		{
			newVertices.clear();
			ClipEdge edge = (ClipEdge)i;
			for (size_t n = 0; n < vertices.size(); ++n)
			{
				size_t np1 = (n + 1) % vertices.size();
				const Vertex& v1 = vertices[n];
				const Vertex& v2 = vertices[np1];
				bool isInFront_V1 = IsInFront(edge, v1.Position);
				bool isInFront_V2 = IsInFront(edge, v2.Position);

				// simplified version
				//if (isInFront_V1 != isInFront_V2)
				//{
				//	newVertices.push_back(ComputeIntersection(edge, v1, v2));
				//}
				//if (isInFront_V2)
				//{
				//	newVertices.push_back(v2);
				//}

				// clarity version
				if (isInFront_V1 && isInFront_V2)
				{
					// save V npt
					newVertices.push_back(v2);
				}
				else if (isInFront_V1 && !isInFront_V2)
				{
					//save intersection
					newVertices.push_back(ComputeIntersection(edge, v1, v2));
				}
				else if (!isInFront_V1 && isInFront_V2)
				{
					// save intersection and np1
					newVertices.push_back(ComputeIntersection(edge, v1, v2));
					newVertices.push_back(v2);
				}
				else // both are behind
				{
					// dont save any
				}
			}
			vertices = newVertices;
		}

	}
	return true;
}