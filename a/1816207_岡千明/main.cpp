#include <Dxlib.h>	// Dxlib×²ÌŞ×Ø‚ğg—p‚·‚é
#include "main.h"
#include <_Debug/_DebugConOut.h>
#include <Scene/SceneMng.h>

// WinMainŠÖ”-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#ifdef DEBUG
	// ÃŞÊŞ¯¸³¨İÄŞ³²İ½Àİ½
	_DebugConOut::GetInstance();
#endif // DEBUG

	// ¼°İÏÈ°¼Ş¬°²İ½Àİ½
	lpSceneMng.Run();

	DxLib_End();
	return 0;
};


// $(SolutionDir)