#include <Dxlib.h>	// Dxlibﾗｲﾌﾞﾗﾘを使用する
#include "main.h"
#include <_Debug/_DebugConOut.h>
#include <Scene/SceneMng.h>

// WinMain関数-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#ifdef DEBUG
	// ﾃﾞﾊﾞｯｸｳｨﾝﾄﾞｳｲﾝｽﾀﾝｽ
	_DebugConOut::GetInstance();
#endif // DEBUG

	// ｼｰﾝﾏﾈｰｼﾞｬｰｲﾝｽﾀﾝｽ
	lpSceneMng.Run();

	DxLib_End();
	return 0;
};


// $(SolutionDir)