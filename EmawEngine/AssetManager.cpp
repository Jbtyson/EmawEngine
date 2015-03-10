#include "stdafx.h"
#include "AssetManager.h"
#include <hash_map>
#include <fstream>

bool AssetManager::instanceFlag = false;
AssetManager* AssetManager::instance = NULL;
GraphicsDeviceInterface* AssetManager::graphicsDevice = NULL;

AssetManager::AssetManager(GraphicsDeviceInterface *device)
{
	rootAssetFolder = "C:\\Users";
	graphicsDevice = device;
}


AssetManager::~AssetManager()
{
}

// Returns the instance of our AssetManager
AssetManager* AssetManager::getInstance() {
	if (!instanceFlag)
	{
		instance = new AssetManager();
		instanceFlag = true;
	}
	return instance;
}

// Sets the root folder for the assets
void AssetManager::setRootFolder(std::string path) {
	rootAssetFolder = path;
}

// Checks for an asset (loads if not found) and then returns a pointer to it
Asset* AssetManager::load(std::string name) {

	if (assets[name] != nullptr) {
		return assets[name];
	}
	else {
		Asset *asset = NULL;
		assets[name] = loadFromFile(name);
		return asset;
	}
}

// Checks for and then loads a file
Asset* AssetManager::loadFromFile(std::string name) {
	Asset* asset = NULL;
	name = rootAssetFolder + "\\" + name;
	// Check if the file exists
	if (std::ifstream(name).good()) {
		// Get the extension and call the appropraite method
		std::string ext = name.substr(name.size() - 3);

		if (ext == "pmg" || ext == "jpeg")
			loadTexture(name);
		else if (ext == "wav" || ext == "mp3")
			loadMusic(name);
		else
			OutputDebugString(L"File type not supported.");
	}
	else {
		OutputDebugString(L"File not found.\n");
	}

	return asset;
}

// Textures ====================================
Asset* AssetManager::loadTexture(std::string name) {
	Asset* asset = NULL;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadTexture(std::string name) {
	//TODO: Unload asset
}

// Shaders ====================================
Asset* AssetManager::loadShader(std::string name) {
	// Shaders require a reference to the graphics device
	ShaderAsset shader(graphicsDevice);
	shader.load(name.c_str);
	return &shader;
}
void AssetManager::unloadShader(std::string name) {
	ShaderAsset* shader = assets[name.c_str];
	shader->unload();
}

// Music ====================================
Asset* AssetManager::loadMusic(std::string name) {
	Asset* asset = NULL;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadMusic(std::string name) {
	//TODO: Unload asset
}

// SoundFX ====================================
Asset* AssetManager::loadSoundFX(std::string name) {
	Asset* asset = NULL;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadSoundFX(std::string name) {
	//TODO: Unload asset
}

// VoxelMap ====================================
Asset* AssetManager::loadVoxelMap(std::string name) {
	Asset* asset = NULL;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadVoxelMap(std::string name) {
	//TODO: Unload asset
}

// BSPMap ====================================
Asset* AssetManager::loadBSPMap(std::string name) {
	Asset* asset = NULL;
	//TODO: Load asset
	return asset;
}
void AssetManager::unloadBSPMap(std::string name) {
	//TODO: Unload asset
}