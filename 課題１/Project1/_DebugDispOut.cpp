#ifdef _DEBUG
#include "_DebugDispOut.h"
#include "SceneMng.h"
#include <tuple>

std::unique_ptr<_DebugDispOut, _DebugDispOut::_DebugDispOutDeletor> _DebugDispOut::s_Instance(new _DebugDispOut);

_DebugDispOut::_DebugDispOut()
{
	_dbgScreen = -1;
}


_DebugDispOut::~_DebugDispOut()
{
}

bool _DebugDispOut::StartDrawDbug()
{
	SetScreen();
	ClsDrawScreen();
	RevScreen();

	return true;
}

bool _DebugDispOut::AddDrawDbug()
{
	if (CheckHitKey(KEY_INPUT_G))
	{
		dbugFlag = true;
	}
	if (CheckHitKey(KEY_INPUT_T))
	{
		dbugFlag = false;
	}

	if (dbugFlag)
	{
		lpSceneMng.AddDrawQue({ _dbgScreen,0,0 });
	}

	return true;
}

bool _DebugDispOut::SetAlpha(int alpha)
{
	if (alpha < 0)
	{
		return false;
	}
	this->alpha = alpha;

	return true;
}

bool _DebugDispOut::SetUp(int alpha)
{
	if (_dbgScreen < 0)
	{
		_dbgScreen = MakeScreen(lpSceneMng.screenSize.x, lpSceneMng.screenSize.y, true);
	}
	dbugFlag = false;
	SetAlpha(alpha);

	return true;
}

void _DebugDispOut::SetScreen()
{
	ghBefor = GetDrawScreen();
	SetDrawScreen(_dbgScreen);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
}

void _DebugDispOut::RevScreen()
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawScreen(ghBefor);
}

int _DebugDispOut::DrawGraph(int x, int y, int GrHandle, int TransFlag)
{
	int retFlag;
	SetScreen();
	retFlag = DxLib::DrawGraph(x + lpSceneMng.gameScreenPos.x, y + lpSceneMng.gameScreenPos.y, GrHandle, TransFlag);
	RevScreen();

	return retFlag;
}

int _DebugDispOut::DrawBox(int x1, int y1, int x2, int y2,unsigned int Color, int FillFlag)
{
	int retFlag = 0;
	SetScreen();
	retFlag = DxLib::DrawBox(x1 + lpSceneMng.gameScreenPos.x, y1 + lpSceneMng.gameScreenPos.y, 
							 x2 + lpSceneMng.gameScreenPos.x, y2 + lpSceneMng.gameScreenPos.y, Color, FillFlag);
	RevScreen();

	return retFlag;
}

int _DebugDispOut::DrawCircle(int x, int y, int r, unsigned int Color, int FillFlag)
{
	int retFlag = 0;
	SetScreen();
	retFlag = DxLib::DrawCircle(x + lpSceneMng.gameScreenPos.x, y + lpSceneMng.gameScreenPos.y, r, Color, FillFlag);
	RevScreen();

	return retFlag;
}

int _DebugDispOut::DrawPixel(int x, int y, unsigned int Color)
{
	int retFlag = 0;
	SetScreen();
	retFlag = DxLib::DrawPixel(x + lpSceneMng.gameScreenPos.x, y + lpSceneMng.gameScreenPos.y, Color);
	RevScreen();

	return retFlag;
}

int _DebugDispOut::DrawLine(int x1, int y1, int x2, int y2, unsigned int Color)
{
	int retFlag = 0;
	SetScreen();
	retFlag = DxLib::DrawLine(x1 + lpSceneMng.gameScreenPos.x, y1 + lpSceneMng.gameScreenPos.y,
							  x2 + lpSceneMng.gameScreenPos.x,y2 + lpSceneMng.gameScreenPos.y,Color);
	RevScreen();

	return retFlag;
}

int _DebugDispOut::DrawString(int x, int y, const char * String, unsigned int Color)
{
	int retFlag = 0;
	SetScreen();
	retFlag = DxLib::DrawString(x + lpSceneMng.gameScreenPos.x, y + lpSceneMng.gameScreenPos.y,String,Color);
	RevScreen();

	return retFlag;
}

#endif // _DEBUG