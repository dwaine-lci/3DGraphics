#include "CmdSetTexture.h"
#include "TextureCache.h"

bool CmdSetTexture::Execute(const std::vector<std::string>& params)
{
	if (params.empty())
	{
		return false;
	}

	TextureCache::Get()->SetTexture(params[0]);
	return true;
}
