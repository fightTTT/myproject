#ifdef _DEBUG
#include <Windows.h>
#include "_DebugConOut.h"

std::unique_ptr<_DebugConOut, _DebugConOut::_DebugConOutDeleter> _DebugConOut::s_Instance(new _DebugConOut);

_DebugConOut::_DebugConOut()
{
	// これで確実にコンソールよりも手前に表示させる
	HWND hwnd = GetForegroundWindow();
	// これでコンソールを開く
	if (AllocConsole())
	{
		freopen_s(&_debugFp, "CONOUT$", "w", stdout);
		freopen_s(&_debugFp, "CONIN$", "r", stdin);
		SetForegroundWindow(hwnd);
	}
	
}

_DebugConOut::~_DebugConOut()
{
	// これでコンソールを消す
	FreeConsole();
}

#endif // _DEBUG