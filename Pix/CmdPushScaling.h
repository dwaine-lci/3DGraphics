#pragma once

#include "Command.h"

class CmdPushScaling : public Command
{
public:
	const char* GetName() override
	{
		return "PushScaling";
	}

	const char* GetDescription() override
	{
		return
			"Pushes the scaling vector";
	}

	bool Execute(const std::vector<std::string>& params) override;
};
