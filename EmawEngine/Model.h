#pragma once
#include "Asset.h"
#include <fbxsdk.h>
#include <vector>

class Model : public Asset
{
public:
	Model();
	~Model();
	void* load(std::string);
	void* getData();
	bool unload();
	std::vector<VERTEX> getVertexBuffer();
private:
	std::vector<VERTEX> vertexBuffer;
};

