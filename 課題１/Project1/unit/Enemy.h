#pragma once
#include "Obj.h"
class Enemy :
	public Obj
{
public:
	Enemy();
	Enemy(const Vector2& pos, const Vector2& size);
	~Enemy();

	// override�Ə������Ƃɂ���ăI�[�o�[���C�h���Y��ɂ��o�O��h�~����
	void Draw(void) override;	
	UNIT GetUnit(void) override;
	void SetMove();
private:
	bool Init(void);
};

