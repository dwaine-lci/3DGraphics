#pragma once

#include "Command.h"

class CmdBeginDraw : public Command
{
public:
	const char* GetName() override
	{
		return "BeginDraw";
	}

	const char* GetDescription() override
	{
		return
			"BeginDraw(topology)\n"
			"\n"
			"- Prepares the primitive manager for storing vertexes.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
