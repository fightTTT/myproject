#pragma once
#include "DxLib.h"
#include <map>
#include <vector>

// ��`
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

	// ̫�Ă̓ǂݍ��݁A�Q�ƂŕԂ�
	const int &GetID(LPCTSTR fontFile, LPCTSTR fontName, std::string useName , int fontSize, int fontThick, bool edgeFlag, bool italic);
	const int &GetFontName(std::string fontName);		// ̫�Ă̖��O��Ԃ�

	int SetFont(std::string useName);					// ̫�Ă̾��(�������O)��ٰ�ߗp

	// �������p(̫��̧��,̫�Ă̖��O, �g���������O,����,����(-1~9�܂���̫�Ă̑����������Ȃ�-1),�����̉�(true�ŗL),�Α�(true�Ŏ΂�))
	bool FontInit(LPCTSTR fontFile, LPCTSTR fontName, std::string useName, int fontSize, int fontThick , bool edgeFlag,bool italic);

private:
	FontMng();
	~FontMng();
	
	std::map<LPCTSTR, int>		fontMap;		// ̫�ēo�^�pmap
	std::map<std::string, int> fontNameMap;		// ���O�t��map
};

