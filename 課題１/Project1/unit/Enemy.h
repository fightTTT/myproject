#pragma once
#include "Obj.h"
class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(const Vector2& pos);
	~Enemy();
	void Draw(void) override;	// override�Ə������Ƃɂ���ăI�[�o�[���C�h���Y��ɂ��o�O��h�~����
	UNIT GetUnit(void) override;
private:
	void Init(void);
};

