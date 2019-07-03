#pragma once
#ifdef _DEBUG
#include <memory>

#define _DBG (...)

class _DebugDispOut
{
public:
	static _DebugDispOut &GetInstance()
	{
		return *s_Instance;
	}

private:
	_DebugDispOut();
	~_DebugDispOut();

	struct _DebugDispOutDeletor
	{
		void operator()(_DebugDispOut *_debugDispOut) const
		{
			delete _debugDispOut;
		}
	};

	static std::unique_ptr<_DebugDispOut, _DebugDispOutDeletor> s_Instance;
};

#else
#define TRASCE(fmt,...) printf(fmt,_VA_ARGS_)
#endif	// _DEBUG