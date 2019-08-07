#pragma once
#include <Unit/Obj.h>
#include <Unit/Bullet.h>
#include <Input/KeyState.h>

// using�錾
using shared_Blt = std::shared_ptr<Bullet>;	// �e�pvector�̌^

class Player :
	public Obj
{
public:
	Player();
	Player(Vector2 pos);
	Player(Vector2 pos, std::list<std::shared_ptr<Bullet>>& bulletlist);

	~Player();

	void Draw(void)override;				// �`��֐�
	void UpDate(void)override;				// ��ԍX�V�p�֐�

	UNIT GetUnitType(void)override;			// Unit��ID��Ԃ�

private:
	bool Init(void);						// �������p�֐�
	std::unique_ptr<InputState> _input;		// ���ް�ނȂǂ̓��͗p�ư��߲���

	std::shared_ptr<Bullet> _bullet_ptr;	// �e�p�������߲���
	std::vector<shared_Blt> _bullet_vec;	// �e�p�Œ蒷�z��

	int invincibleFlag = 0;					// ��Ұ�ނ��������Ƃ��Ɉ�莞�Ԗ��G�ɂ���̶ׂ���
};

// �׽�����̫�Ă���ײ�ް�
//class Player :Obj
//{
//public:
//	Player();
//	~Player();
//};


// �\���̥����̫�Ă�����د�
//struct Player : Obj
//{
//public:
//	Player();
//	~Player();
//};