#include "CmdSetAddressMode.h"
#include "TextureCache.h"

bool CmdSetAddressMode::Execute(const std::vector<std::string>& params)
{
	if (params.empty())
	{
		return false;
	}

	AddressMode mode;
	if (params[0] == "clamp")
	{
		mode = AddressMode::Clamp;
	}
	else if (params[0] == "wrap")
	{
		mode = AddressMode::Wrap;
	}
	else
	{
		return false;
	}

	TextureCache::Get()->SetAddressMode(mode);
	return true;
}
