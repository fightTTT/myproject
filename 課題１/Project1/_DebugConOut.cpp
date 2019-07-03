#ifdef _DEBUG
#include <Windows.h>
#include "_DebugConOut.h"

std::unique_ptr<_DebugConOut, _DebugConOut::_DebugConOutDeleter> _DebugConOut::s_Instance(new _DebugConOut);

_DebugConOut::_DebugConOut()
{
	// ����Ŋm���ɃR���\�[��������O�ɕ\��������
	HWND hwnd = GetForegroundWindow();
	// ����ŃR���\�[�����J��
	if (AllocConsole())
	{
		freopen_s(&_debugFp, "CONOUT$", "w", stdout);
		freopen_s(&_debugFp, "CONIN$", "r", stdin);
		SetForegroundWindow(hwnd);
	}
	
}

_DebugConOut::~_DebugConOut()
{
	// ����ŃR���\�[��������
	FreeConsole();
}

#endif // _DEBUG