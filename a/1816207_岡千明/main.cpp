#include <Dxlib.h>	// Dxlibײ���؂��g�p����
#include "main.h"
#include <_Debug/_DebugConOut.h>
#include <Scene/SceneMng.h>

// WinMain�֐�-------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
#ifdef DEBUG
	// ���ޯ�����޳�ݽ�ݽ
	_DebugConOut::GetInstance();
#endif // DEBUG

	// ����Ȱ�ެ��ݽ�ݽ
	lpSceneMng.Run();

	DxLib_End();
	return 0;
};


// $(SolutionDir)