#ifdef _DEBUG
#include <DxLib.h>
#include "_DebugDispOut.h"
#include "SceneMng.h"
#include <tuple>

std::unique_ptr<_DebugDispOut, _DebugDispOut::_DebugDispOutDeletor> _DebugDispOut::s_Instance(new _DebugDispOut);

bool _DebugDispOut::StartDrawDbug()
{
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_dbgScreen);
	ClsDrawScreen();
	SetDrawScreen(ghBefor);

	return true;
}

bool _DebugDispOut::AddDrawDbug()
{
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
	dbugFlag = true;
	SetAlpha(alpha);
	return true;
}

int _DebugDispOut::DrawGraph(int x, int y, int GrHandle, int TransFlag)
{
	int retFlag;
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_dbgScreen);
	retFlag = DxLib::DrawGraph(x, y, GrHandle, TransFlag);
	SetDrawScreen(ghBefor);
	return retFlag;
}

int _DebugDispOut::DrawBox(int x1, int y1, int x2, int y2,unsigned int Color, int FillFlag)
{
	int retFlag = 0;
	int ghBefor;
	ghBefor = GetDrawScreen();
	SetDrawScreen(_dbgScreen);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	retFlag = DxLib::DrawBox(x1 + lpSceneMng.gameScreenPos.x, y1 + lpSceneMng.gameScreenPos.y, x2 + lpSceneMng.gameScreenPos.x, y2 + lpSceneMng.gameScreenPos.y, Color, FillFlag);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0);
	SetDrawScreen(ghBefor);
	return retFlag;
}

_DebugDispOut::_DebugDispOut()
{
	_dbgScreen = -1;
}


_DebugDispOut::~_DebugDispOut()
{
}

#endif // _DEBUG