#include "FontMng.h"

const int & FontMng::GetID(LPCTSTR fontFile, LPCTSTR fontName, std::string useName, int fontSize, int fontThick, bool edgeFlag, bool italic)
{
	if (fontMap.find(fontFile) == fontMap.end())
	{
		// �t�H���g�t�@�C���̒ǉ�
		fontMap[fontFile] = AddFontResourceEx(fontFile, FR_PRIVATE, NULL);
	}

	if (fontNameMap.find(useName) == fontNameMap.end())
	{
		if (edgeFlag)
		{
			// �����ر��������
			fontNameMap[useName] = CreateFontToHandle(fontName, fontSize, fontThick, DX_FONTTYPE_ANTIALIASING_EDGE_8X8 ,/*int CharSet =*/ -1, 2, /*int Italic =*/ italic);
			//CreateFontToHandle(const TCHAR *FontName, int Size, int Thick, int FontType = -1, int CharSet = -1, int EdgeSize = -1, int Italic = FALSE, int Handle = -1);		// �t�H���g�n���h�����쐬����
		}
		else
		{
			// �����ر�����Ȃ�
			fontNameMap[useName] = CreateFontToHandle(fontName, fontSize, fontThick, DX_FONTTYPE_NORMAL, /*int CharSet =*/ -1, -1, /*int Italic =*/ italic);
		}

	}
	return fontMap[fontFile];
}

const int & FontMng::GetFontName(std::string fontName)
{
	return fontNameMap[fontName];
}

int FontMng::SetFont(std::string useName)
{
	return fontNameMap[useName];
}

bool FontMng::FontInit(LPCTSTR fontFile, LPCTSTR fontName, std::string useName, int fontSize, int fontThick, bool edgeFlag, bool italic)
{
	GetID(fontFile, fontName, useName , fontSize, fontThick , edgeFlag, italic);
	return true;
}

FontMng::FontMng()
{
}


FontMng::~FontMng()
{
}
