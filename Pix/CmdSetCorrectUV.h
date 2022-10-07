#pragma once

#include "Command.h"

class CmdSetCorrectUV : public Command
{
public:
	const char* GetName() override
	{
		return "SetCorrectUV";
	}

	const char* GetDescription() override
	{
		return
			"SetCorrectUV(0 or 1)\n"
			"\n"
			"- Enable/disable perspective correct texturing.\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
