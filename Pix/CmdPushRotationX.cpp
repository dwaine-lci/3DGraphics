#include "CmdPushRotationX.h"
#include "MatrixStack.h"
#include "VariableCache.h"

bool CmdPushRotationX::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
		return false;
	
	float degree = VariableCache::Get()->GetFloat(params[0]);
	MatrixStack::Get()->PushRotationX(degree * 3.1416f / 180.0f);
	return true;
}
