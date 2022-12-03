#pragma once

#include "Light.h"

class LightManager
{
public:
	static LightManager* Get();

public:
	void OnNewFrame();

	void AddDirectionalLight(const Vector3& direction);
	void AddPointLight(const Vector3& position, float constant, float linear, float quadratic);

	void SetLightingAmbient(const X::Color& ambient);
	void SetLightingDiffuse(const X::Color& diffuse);
	void SetLightingSpecular(const X::Color& specular);

	X::Color ComputeLightColor(const Vector3& position, const Vector3& normal) const;

private:
	std::vector<std::unique_ptr<Light>> mLights;
	X::Color mAmbient = X::Colors::White;
	X::Color mDiffuse = X::Colors::White;
	X::Color mSpecular = X::Colors::White;
};