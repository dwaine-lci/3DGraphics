#pragma once

#include "Command.h"

class CmdPopMatrix : public Command
{
public:
	const char* GetName() override
	{
		return "PopMatrix";
	}

	const char* GetDescription() override
	{
		return
			"Pops the matrix";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
