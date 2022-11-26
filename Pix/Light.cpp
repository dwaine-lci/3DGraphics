#include "Light.h"

void Light::SetAmbient(const X::Color& ambient)
{
	mAmbient = ambient;
}
void Light::SetDiffuse(const X::Color& diffuse)
{
	mDiffuse = diffuse;
}
void Light::SetSpecular(const X::Color& specular)
{
	mSpecular = specular;
}