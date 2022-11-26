#include "CmdSetCullMode.h"
#include "PrimitivesManager.h"

bool CmdSetCullMode::Execute(const std::vector<std::string>& params)
{
	// Need just fill mode name
	if (params.size() < 1)
		return false;

	CullMode cullMode = CullMode::Back;
	if (params[0] == "none")
	{
		cullMode = CullMode::None;
	}
	else if (params[0] == "front")
	{
		cullMode = CullMode::Front;
	}
	else if (params[0] == "back")
	{
		cullMode = CullMode::Back;
	}
	PrimitivesManager::Get()->SetCullMode(cullMode);
	return true;
}
