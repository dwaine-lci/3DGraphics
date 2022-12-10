#include "CmdSetCorrectUV.h"
#include "PrimitivesManager.h"
#include "VariableCache.h"

bool CmdSetCorrectUV::Execute(const std::vector<std::string>& params)
{
	if (params.empty())
	{
		return false;
	}

	auto vc = VariableCache::Get();
	const bool correctUV = vc->GetBool(params[0]);

	PrimitivesManager::Get()->SetCorrectUV(correctUV);
	return true;
}
