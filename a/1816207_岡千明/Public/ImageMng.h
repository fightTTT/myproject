#pragma once
#include <DxLib.h>
#include <map>
#include <vector>
#include <common/Vector2.h>

// using宣言
using VecInt = std::vector<int>;

// 定義^
#define IMAGE_ID(KEY) (ImageMng::GetInstance().GetID(KEY))						// 画像登録､引数は(image/〇〇)
#define SET_IMAGE_ID(KEY,F_NAME) (ImageMng::GetInstance().GetID(KEY,F_NAME))	// 画像登録､引数は(付けたい名前,image/〇〇)

class ImageMng
{
public:
	static ImageMng& GetInstance()		// ｱﾄﾞﾚｽが欲しいためﾎﾟｲﾝﾀｰか参照で
	{
		// nullptrでなければｲﾝｽﾀﾝｽする ｼﾝｸﾞﾙﾄﾝ
		if (s_Instance == nullptr)
		{
			s_Instance = new ImageMng();
		}
		return (*s_Instance);
	}

	~ImageMng();

	const VecInt& GetID(const std::string& key);												// 画像IDを登録し渡す関数LoadGraph用("image/〇〇")
	const VecInt& GetID(const std::string& key, const std::string& fileName);					// 画像IDを登録し渡す関数LoadGraph用("つけたい名前","image/〇〇")

	const VecInt& GetID(const std::string& key, const Vector2& divSize, const Vector2& divCnt);	// 画像IDを登録し渡す関数LoadDivGraph用("image/〇〇",分割1枚あたりのｻｲｽﾞ,総分割数)
	const VecInt& GetID(const std::string& key, const std::string& fileName,
		const Vector2& divSize, const Vector2& divCnt);												// 画像IDを登録し渡す関数LoadDivGraph用("つけたい名前","image/〇〇",分割1枚あたりのｻｲｽﾞ,総分割数)

private:
	ImageMng();

	std::map<std::string, VecInt> _imgMap;	// 画像ﾌｧｲﾙ登録用map

	static ImageMng *s_Instance;			// ｲﾝｽﾀﾝｽ用
};

// ImageMngは動的なｼﾝｸﾞﾙﾄﾝ
// const
