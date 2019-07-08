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

	// �f�o�b�N�p�̃X�N���[����clsDrawScreen����
	bool StartDrawDbug();

	// G�L�[����������f�o�b�N�p�̃X�N���[����drawList�ɒǉ����A�\������B�@
	// T�L�[�ŕ\�����Ȃ��B
	bool AddDrawDbug();			

	// alpha�l��ݒ�
	bool SetAlpha(int alpha);	

	// _DebugDispOut�̏����������AMakeScreen����
	bool SetUp(int alpha);		

	// �ʏ�̃L�����N�^�[���̕`����ʂ��擾���ăf�o�b�O�p�̃X�N���[�����Z�b�g����
	void SetScreen();
	// �ʏ�̃L�����N�^�[���̕`����ʂ��Z�b�g������
	void RevScreen();

	// �摜�`��
	int DrawGraph(int x, int y, int GrHandle, int TransFlag);		

	// �l�p�`�`��
	int DrawBox(int x1, int y1, int x2, int y2,unsigned int Color, int FillFlag);	

	// �~�`��
	int DrawCircle(int x, int y, int r, unsigned int Color, int FillFlag);	
	
	// �s�N�Z���`��
	int DrawPixel(int x, int y, unsigned int Color);		

	// �����`��
	int DrawLine(int x1, int y1, int x2, int y2, unsigned int Color);		

	// �����`��
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

	int alpha;			// �f�o�b�N�摜�̓��ߗ�
	int _dbgScreen;		// �f�o�b�N�p�̃X�N���[��
	int ghBefor;		
	bool dbugFlag;		// �f�o�b�N���邩���Ȃ���

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