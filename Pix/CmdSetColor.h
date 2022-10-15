#pragma once

#include "Command.h"

class CmdSetColor : public Command
{
public:
	const char* GetName() override
	{
		return "SetColor";
	}

	const char* GetDescription() override
	{
		return
			"SetColor(r, g, b)\n"
			"\n"
			"- Sets the color for the pixels.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
