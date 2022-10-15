//====================================================================================================
// Filename:	WinMain.h
// Created by:	Peter Chan
//====================================================================================================

#include "PixEditor.h"
#include "MathHelper.h"

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// Start Pix Editor
	PixEditor editor;

	Vector3 value;
	Vector3 normal = MathHelper::Normalize(value);

	X::Start("xconfig.json");
	editor.Initialize();

	X::Run([&](float deltaTime)
	{
		return editor.Run(deltaTime);
	});

	editor.Terminate();
	X::Stop();
	return 0;
}