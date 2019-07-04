#pragma once
#ifdef _DEBUG
#include <memory>

#define _DbgStartDraw	 _DebugDispOut::GetInstance().StartDrawDbug()
#define _DbgAddDraw		 _DebugDispOut::GetInstance().AddDrawDbug()
#define _DbgSetUp(A) _DebugDispOut::GetInstance().SetUp(A)
#define _DbgSetAlpha(A)  _DebugDispOut::GetInstance().SetAlpha(A)

#define _DbgDrawGraph(fmt,...) _DebugDispOut::GetInstance().DrawGraph(fmt,__VA_ARGS__)
#define _DbgDrawBox(fmt,...)   _DebugDispOut::GetInstance().DrawBox(fmt,__VA_ARGS__)

class _DebugDispOut
{
public:
	static _DebugDispOut &GetInstance()
	{
		return *s_Instance;
	}

	bool StartDrawDbug();
	bool AddDrawDbug();
	bool SetAlpha(int alpha);
	bool SetUp(int alpha);

	int DrawGraph(int x, int y, int GrHandle, int TransFlag);
	int DrawBox(int x1, int y1, int x2, int y2,unsigned int Color, int FillFlag);

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

	int alpha;
	int _dbgScreen;
	bool dbugFlag;

	static std::unique_ptr<_DebugDispOut, _DebugDispOutDeletor> s_Instance;
};

#else
#define _DbgStartDraw	 _DebugDispOut::GetInstance().StartDrawDbug()
#define _DbgAddDraw		 _DebugDispOut::GetInstance().AddDrawDbug()
#define _DbgSetUp(A)	 _DebugDispOut::GetInstance().SetUp(A)
#define _DbgSetAlpha(A)  _DebugDispOut::GetInstance().SetAlpha(A)

#define _DbgDrawGraph(fmt,...) _DebugDispOut::GetInstance().DrawGraph(fmt,__VA_ARGS__)
#define _DbgDrawBox(fmt,...)   _DebugDispOut::GetInstance().DrawBox(fmt,__VA_ARGS__)
#endif	// _DEBUG