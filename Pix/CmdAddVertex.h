#pragma once

#include "Command.h"

class CmdAddVertex : public Command
{
public:
	const char* GetName() override
	{
		return "AddVertex";
	}

	const char* GetDescription() override
	{
		return
			"AddVertex(x, y)\n"
			"AddVertex(x, y, z)\n"
			"AddVertex(x, y, r, g, b)\n"
			"AddVertex(x, y, z, r, g, b)\n"
			"\n"
			"- Sends the vertexes to the rasterizer to render.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
