#include <asset_loader.h>
#include <fstream>
#include <iostream>

#ifndef _WIN32
#include <game-activity/native_app_glue/android_native_app_glue.h>
extern android_app* g_AppCtx;
#endif

using namespace assets;
bool assets::save_binaryfile(const  char* path, const AssetFile& file)
{
	std::ofstream outfile;
	outfile.open(path, std::ios::binary | std::ios::out);
	if (!outfile.is_open())
	{
		std::cout << "Error when trying to write file: " << path << std::endl;
	}
	outfile.write(file.type, 4);
	uint32_t version = file.version;
	//version
	outfile.write((const char*)&version, sizeof(uint32_t));

	//json lenght
	uint32_t lenght = static_cast<uint32_t>(file.json.size());
	outfile.write((const char*)&lenght, sizeof(uint32_t));

	//blob lenght
	uint32_t bloblenght = static_cast<uint32_t>(file.binaryBlob.size());
	outfile.write((const char*)&bloblenght, sizeof(uint32_t));

	//json stream
	outfile.write(file.json.data(), lenght);
	//pixel data
	outfile.write(file.binaryBlob.data(), file.binaryBlob.size());

	outfile.close();

	return true;
}

#ifdef _WIN32
bool assets::load_binaryfile(const  char* path, AssetFile& outputFile)
{
	std::ifstream infile;
	infile.open(path, std::ios::binary);

	if (!infile.is_open()) return false;

	infile.seekg(0);


	infile.read(outputFile.type, 4);
	
	infile.read((char*)&outputFile.version, sizeof(uint32_t));

	uint32_t jsonlen = 0;
	infile.read((char*)&jsonlen, sizeof(uint32_t));

	uint32_t bloblen = 0;
	infile.read((char*)&bloblen, sizeof(uint32_t));

	outputFile.json.resize(jsonlen);

	infile.read(&outputFile.json[0], jsonlen);

	outputFile.binaryBlob.resize(bloblen);
	infile.read(outputFile.binaryBlob.data(), bloblen);

	return true;
}
#else
bool assets::load_binaryfile(const  char* path, AssetFile& outputFile)
{
    AAsset* infile = AAssetManager_open(g_AppCtx->activity->assetManager, path, AASSET_MODE_BUFFER);
	if (!infile) return false;

	AAsset_read(infile, outputFile.type, 4);
	AAsset_read(infile, (char*)&outputFile.version, sizeof(uint32_t));

    uint32_t jsonlen = 0;
	AAsset_read(infile, (char*)&jsonlen, sizeof(uint32_t));

    uint32_t bloblen = 0;
	AAsset_read(infile, (char*)&bloblen, sizeof(uint32_t));

    outputFile.json.resize(jsonlen);

	AAsset_read(infile, &outputFile.json[0], jsonlen);

    outputFile.binaryBlob.resize(bloblen);
	AAsset_read(infile, outputFile.binaryBlob.data(), bloblen);
	AAsset_close(infile);

    return true;
}
#endif

assets::CompressionMode assets::parse_compression(const char* f)
{
	if (strcmp(f, "LZ4") == 0)
	{
		return assets::CompressionMode::LZ4;
	}
	else {
		return assets::CompressionMode::None;
	}
}

