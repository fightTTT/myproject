#pragma once
#include "Obj.h"

class E_Bullet :
	public Obj
{
public:
	E_Bullet();
	E_Bullet(Vector2Dbl pos);
	~E_Bullet();

	void Draw(void)override;					// �`��֐�
	void UpDate(void)override;					// ��ԍX�V�p�֐�(�������z�֐�)
	UNIT GetUnitType(void)override;				// UNIT��ID��Ԃ�

	bool actFlg(void) { return _actFlg; };		// ���݂̏�Ԃ�Ԃ�
	void SetactFlg(Vector2Dbl pos);				// ������Ĕ��˂̎��Ɏg�p����˂�����pos����ͤ_actFlg��true�ɂȂ�
	void SetactFlg(void);						// �e���è�ނɂ���Ƃ��Ɏg�p
private:
	void Init(void);

	bool _actFlg = false;						// �����p�׸�
};

