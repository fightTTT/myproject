#pragma once
#include "DxLib.h"
#include <map>
#include <vector>

// 定義
#define lpFontMng FontMng::GetInstance()
#define Font_ID(X)(FontMng::GetInstance().GetID(X))

class FontMng
{
public:
	static FontMng &GetInstance(void)
	{
		static FontMng s_Instance;
		return (s_Instance);
	}

	// ﾌｫﾝﾄの読み込み、参照で返す
	const int &GetID(LPCTSTR fontFile, LPCTSTR fontName, std::string useName , int fontSize, int fontThick, bool edgeFlag, bool italic);
	const int &GetFontName(std::string fontName);		// ﾌｫﾝﾄの名前を返す

	int SetFont(std::string useName);					// ﾌｫﾝﾄのｾｯﾄ(つけた名前)非ﾙｰﾌﾟ用

	// 初期化用(ﾌｫﾝﾄﾌｧｲﾙ,ﾌｫﾝﾄの名前, 使いたい名前,ｻｲｽﾞ,太さ(-1~9までﾃﾞﾌｫﾙﾄの太さがいいなら-1),文字の縁(trueで有),斜体(trueで斜め))
	bool FontInit(LPCTSTR fontFile, LPCTSTR fontName, std::string useName, int fontSize, int fontThick , bool edgeFlag,bool italic);

private:
	FontMng();
	~FontMng();
	
	std::map<LPCTSTR, int>		fontMap;		// ﾌｫﾝﾄ登録用map
	std::map<std::string, int> fontNameMap;		// 名前付けmap
};

