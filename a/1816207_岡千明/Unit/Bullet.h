#pragma once
#include "Obj.h"
class Bullet :
	public Obj
{
public:
	Bullet();
	Bullet(Vector2Dbl pos);
	~Bullet();
	void Draw(void)override;					// �`��֐�
	void UpDate(void)override;					// ��ԍX�V�p�֐�(�������z�֐�)
	UNIT GetUnitType(void)override;				// UNIT��ID��Ԃ�

	bool actFlg(void){ return _actFlg; };		// ���݂̏�Ԃ�Ԃ�
	void SetactFlg(Vector2Dbl pos);				// ������Ĕ��˂̎��Ɏg�p����˂�����pos����ͤ_actFlg��true�ɂȂ�
	void SetactFlg(void);						// �e���è�ނɂ���Ƃ��Ɏg�p
private:
	void Init(void);

	bool _actFlg;								// �����p�׸�
};

