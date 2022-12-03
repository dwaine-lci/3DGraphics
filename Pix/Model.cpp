#include "Model.h"


void Model::Load(const std::string& fileName)
{
	mFileName = fileName;

	std::vector<Vector3> positions;
	std::vector<Vector3> normals;
	std::vector<uint32_t> normalsCount;
	std::vector<uint32_t> positionIndicies;

	FILE* file = nullptr;
	fopen_s(&file, fileName.c_str(), "r");
	if (file == nullptr)
	{
		char buffer[128];
		sprintf_s(buffer, "Cannot open model file %s", fileName.c_str());
		MessageBoxA(nullptr, buffer, "Model Error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}

	while (true)
	{
		char buffer[128];
		int result = fscanf_s(file, "%s", buffer, (uint32_t)std::size(buffer));
		if (result == EOF)
		{
			break;
		}

		if (strcmp(buffer, "v") == 0)
		{
			float x, y, z = 0.0f;
			fscanf_s(file, "%f %f %f\n", &x, &y, &z);
			positions.push_back({ x, y, z });
		}
		else if (strcmp(buffer, "f") == 0)
		{
			uint32_t v[3];
			if (fscanf_s(file, "%d//%*d %d//%*d %d//%*d\n", &v[0], &v[1], &v[2]) != 3)
			{
				char buffer[128];
				sprintf_s(buffer, "Unexpected format for %s", fileName.c_str());
				MessageBoxA(nullptr, buffer, "Model Error", MB_OK | MB_ICONEXCLAMATION);
				return;
			}

			positionIndicies.push_back(v[0]);
			positionIndicies.push_back(v[1]);
			positionIndicies.push_back(v[2]);
		}
	}

	// construct the model
	mVerticies.resize(positionIndicies.size());
	normals.resize(positions.size());
	normalsCount.resize(positions.size());
	for (size_t i = 2; i < positionIndicies.size(); i += 3)
	{
		uint32_t index0 = positionIndicies[i - 2] - 1;
		uint32_t index1 = positionIndicies[i - 1] - 1;
		uint32_t index2 = positionIndicies[i] - 1;
		Vector3 pos0 = positions[index0];
		Vector3 pos1 = positions[index1];
		Vector3 pos2 = positions[index2];
		Vector3 faceNorm = MathHelper::Normalize(MathHelper::Cross((pos1 - pos0), (pos2 - pos0)));
		normals[index0] = normals[index0] + faceNorm;
		normals[index1] = normals[index1] + faceNorm;
		normals[index2] = normals[index2] + faceNorm;
		++normalsCount[index0];
		++normalsCount[index1];
		++normalsCount[index2];
	}
	for (size_t i = 0; i < normals.size(); ++i)
	{
		if (normalsCount[i] > 0)
		{
			normals[i] = MathHelper::Normalize((normals[i] / (float)normalsCount[i]));
		}
		else
		{
			normals[i] = Vector3(0, 0, 1);
		}
	}
	for (size_t i = 0; i < positionIndicies.size(); ++i)
	{
		mVerticies[i].Position = positions[positionIndicies[i] - 1];
		mVerticies[i].Normal = normals[positionIndicies[i] - 1];
		mVerticies[i].Color = X::Colors::White;
	}
	fclose(file);
}

const std::string& Model::GetFileName() const
{
	return mFileName;
}
const Vertex& Model::GetVertex(int index) const
{
	return mVerticies[index];
}
int Model::GetVertexCount() const
{
	return static_cast<int>(mVerticies.size());
}