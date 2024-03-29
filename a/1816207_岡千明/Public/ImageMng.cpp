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
	// ｷｰ名がなければ新しく作る
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
	// ｷｰ名がなければ新しく作る
	if (_imgMap.find(key) == _imgMap.end())
	{
		_imgMap[key].resize(divCnt.x * divCnt.y);

		LoadDivGraph(fileName.c_str(),
			divCnt.x * divCnt.y,	// 全体の数
			divCnt.x,				// 横の数
			divCnt.y,				// 縦の数
			divSize.x,				// ｻｲｽﾞx
			divSize.y,				// ｻｲｽﾞy
			&_imgMap[key][0]);
	}

	return _imgMap[key];
}

