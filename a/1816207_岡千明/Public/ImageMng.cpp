#include "imageMng.h"

ImageMng* ImageMng::s_Instance = nullptr;

ImageMng::ImageMng()
{

}


ImageMng::~ImageMng()
{

}

const VecInt& ImageMng::GetID(const std::string& key)
{
	return GetID(key, key);
}

const VecInt & ImageMng::GetID(const std::string& key, const std::string& fileName)
{
	// ·°–¼‚ª‚È‚¯‚ê‚ÎV‚µ‚­ì‚é
	if (_imgMap.find(key) == _imgMap.end())
	{
		_imgMap[key].resize(1);
		_imgMap[key][0] = LoadGraph(fileName.c_str(), true);
	}

	return _imgMap[key];
}

const VecInt & ImageMng::GetID(const std::string& key, const Vector2& divSize, const Vector2& divCnt)
{
	return GetID(key, key, Vector2(divSize), Vector2(divCnt));
}

const VecInt & ImageMng::GetID(const std::string& key, const std::string& fileName, const Vector2& divSize, const Vector2& divCnt)
{
	// ·°–¼‚ª‚È‚¯‚ê‚ÎV‚µ‚­ì‚é
	if (_imgMap.find(key) == _imgMap.end())
	{
		_imgMap[key].resize(divCnt.x * divCnt.y);

		LoadDivGraph(fileName.c_str(),
			divCnt.x * divCnt.y,	// ‘S‘Ì‚Ì”
			divCnt.x,				// ‰¡‚Ì”
			divCnt.y,				// c‚Ì”
			divSize.x,				// »²½Şx
			divSize.y,				// »²½Şy
			&_imgMap[key][0]);
	}

	return _imgMap[key];
}

