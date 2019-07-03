#pragma once
#include <map>
#include <vector>

#define lpImageMng ImageMng::GetInstance()
using IntVec = std::vector<int>;

#define IMAGE_ID(KEY) (ImageMng::GetInstance().GetID(KEY))
#define SET_IMAGE_ID(KEY,F_NAME) (ImageMng::GetInstance().GetID(KEY,F_NAME))

class Vector2;

class ImageMng
{
public:
	static ImageMng &GetInstance()
	{
		//static ImageMng s_Instance;
		if (s_Instance == nullptr)
		{
			s_Instance = new ImageMng();
		}
		return *s_Instance;
	}

	const IntVec& GetID(const std::string& key);
	const IntVec& GetID(const std::string& key,const std::string& fileName);
	const IntVec& GetID(const std::string& key,const Vector2& num, const Vector2& size);
	const IntVec& GetID(const std::string& key,const std::string& fileName, const Vector2& num, const Vector2& size);


	~ImageMng();
private:
	ImageMng();

	std::map<std::string, IntVec> imgMap;

	static ImageMng *s_Instance;
};

