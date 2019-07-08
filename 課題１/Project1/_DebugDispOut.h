#pragma once
#ifdef _DEBUG
#include <memory>
#include <DxLib.h>
#include <chrono>

#define _DbgStartDraw	 _DebugDispOut::GetInstance().StartDrawDbug()
#define _DbgAddDraw		 _DebugDispOut::GetInstance().AddDrawDbug()
#define _DbgSetUp(A)     _DebugDispOut::GetInstance().SetUp(A)
#define _DbgSetAlpha(A)  _DebugDispOut::GetInstance().SetAlpha(A)

#define _DbgDrawGraph(fmt,...)  _DebugDispOut::GetInstance().DrawGraph(fmt,__VA_ARGS__)
#define _DbgDrawBox(fmt,...)    _DebugDispOut::GetInstance().DrawBox(fmt,__VA_ARGS__)
#define _DbgDrawCircle(fmt,...) _DebugDispOut::GetInstance().DrawCircle(fmt,__VA_ARGS__)
#define _DbgDrawPixel(fmt,...)  _DebugDispOut::GetInstance().DrawPixel(fmt,__VA_ARGS__)
#define _DbgDrawLine(fmt,...)   _DebugDispOut::GetInstance().DrawLine(fmt,__VA_ARGS__)
#define _DbgDrawString(fmt,...) _DebugDispOut::GetInstance().DrawString(fmt,__VA_ARGS__)
#define _DbgDrawFormatString(fmt,...)   _DebugDispOut::GetInstance().SetScreen();\
										DxLib::DrawFormatString(fmt,__VA_ARGS__);\
										_DebugDispOut::GetInstance().RevScreen()

using chronoSysTime = std::chrono::system_clock::time_point;

class _DebugDispOut
{
public:
	static _DebugDispOut &GetInstance()
	{
		return *s_Instance;
	}

	// デバック用のスクリーンをclsDrawScreenする
	bool StartDrawDbug();

	// Gキーを押したらデバック用のスクリーンをdrawListに追加し、表示する。　
	// Tキーで表示しない。
	bool AddDrawDbug();			

	// alpha値を設定
	bool SetAlpha(int alpha);	

	// _DebugDispOutの初期化処理、MakeScreenする
	bool SetUp(int alpha);		

	// 通常のキャラクター等の描画先画面を取得してデバッグ用のスクリーンをセットする
	void SetScreen();
	// 通常のキャラクター等の描画先画面をセットし直す
	void RevScreen();

	// 画像描画
	int DrawGraph(int x, int y, int GrHandle, int TransFlag);		

	// 四角形描画
	int DrawBox(int x1, int y1, int x2, int y2,unsigned int Color, int FillFlag);	

	// 円描画
	int DrawCircle(int x, int y, int r, unsigned int Color, int FillFlag);	
	
	// ピクセル描画
	int DrawPixel(int x, int y, unsigned int Color);		

	// 直線描画
	int DrawLine(int x1, int y1, int x2, int y2, unsigned int Color);		

	// 文字描画
	int DrawString(int x, int y, const char *String, unsigned int Color);	

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

	bool SetTime();

	int alpha;			// デバック画像の透過率
	int _dbgScreen;		// デバック用のスクリーン
	int ghBefor;		
	bool dbugFlag;		// デバックするかしないか

	chronoSysTime startTime;
	chronoSysTime endTime;
	double waitTime;

	static std::unique_ptr<_DebugDispOut, _DebugDispOutDeletor> s_Instance;
};

#else
#define _DbgStartDraw	 _DebugDispOut::GetInstance().StartDrawDbug()
#define _DbgAddDraw		 _DebugDispOut::GetInstance().AddDrawDbug()
#define _DbgSetUp(A)	 _DebugDispOut::GetInstance().SetUp(A)
#define _DbgSetAlpha(A)  _DebugDispOut::GetInstance().SetAlpha(A)

#define _DbgDrawGraph(fmt,...) _DebugDispOut::GetInstance().DrawGraph(fmt,__VA_ARGS__)
#define _DbgDrawBox(fmt,...)   _DebugDispOut::GetInstance().DrawBox(fmt,__VA_ARGS__)
#define _DbgDrawCircle(fmt,...) _DebugDispOut::GetInstance().DrawCircle(fmt,__VA_ARGS__)
#define _DbgDrawPixel(fmt,...)  _DebugDispOut::GetInstance().DrawPixel(fmt,__VA_ARGS__)
#define _DbgDrawLine(fmt,...)   _DebugDispOut::GetInstance().DrawLine(fmt,__VA_ARGS__)
#define _DbgDrawString(fmt,...) _DebugDispOut::GetInstance().DrawString(fmt,__VA_ARGS__)
#define _DbgDrawFormatString(fmt,...) {_DebugDispOut::GetInstance().SetScreen();\
										DxLib::DrawFormatString(fmt,__VA_ARGS__);\
										_DebugDispOut::GetInstance().RevScreen();}
#endif	// _DEBUG