#include "CmdSetColor.h"
#include "Rasterizer.h"

bool CmdSetColor::Execute(const std::vector<std::string>& params)
{
	// Need at least 3 params for r, g, b
	if (params.size() < 3)
		return false;

	float r = stof(params[0]);
	float g = stof(params[1]);
	float b = stof(params[2]);

	// Draw the pixel
	Rasterizer::Get()->SetColor(X::Color(r, g, b, 1.0f));
	return true;
}
