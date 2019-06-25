#include <DxLib.h>
#include "ImageMng.h"
#include "vector2.h"

ImageMng* ImageMng::s_Instance = nullptr;

ImageMng::ImageMng()
{
}


ImageMng::~ImageMng()
{
}

const IntVec& ImageMng::GetID(const std::string& key)
{
	GetID(key, key);
	return imgMap[key];
}

const IntVec& ImageMng::GetID(const std::string& key,const std::string& fileName)
{
	if (imgMap.find(key) == imgMap.end())
	{
		imgMap[key].resize(1);
		imgMap[key][0] = LoadGraph(fileName.c_str());
	}
	return imgMap[key];
	
}

const IntVec& ImageMng::GetID(const std::string& key,const Vector2& const num,const Vector2& size)
{
	GetID(key, key, num,size);
	return imgMap[key];
}

const IntVec& ImageMng::GetID(const std::string& key,const std::string& fileName,const Vector2& num,const Vector2& size)
{
	// load‚³‚ê‚Ä‚é‚©Šm”F‚µ‚ÄA‚³‚ê‚Ä‚È‚©‚Á‚½‚çload‚·‚é
	if (imgMap.find(key) == imgMap.end())
	{
		imgMap[key].resize(num.x * num.y);
		LoadDivGraph(fileName.c_str(),(num.x * num.y), num.x, num.y,size.x,size.y, &imgMap[key][0],false);
	}

	return imgMap[key];
}
