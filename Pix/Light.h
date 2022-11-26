#pragma once

#include "MathHelper.h"
#include <XEngine.h>

class Light
{
public:
	virtual ~Light() = default;

	virtual X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) const = 0;

	void SetAmbient(const X::Color& ambient);	// color without lighting
	void SetDiffuse(const X::Color& diffuse);	// main color with lighting
	void SetSpecular(const X::Color& specular);	// enhanced color at lighting focal point

protected:
	X::Color mAmbient = X::Colors::White;
	X::Color mDiffuse = X::Colors::White;
	X::Color mSpecular = X::Colors::White;
};