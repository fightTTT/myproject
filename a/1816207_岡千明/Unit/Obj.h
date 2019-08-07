#pragma once
#include <vector>
#include <list>
#include <map>
#include <memory>
#include <tuple>
#include <Public/ImageMng.h>
#include <common/Vector2.h>

// �׽�錾
class Obj;
class Bullet;
class E_Bullet;

// using�錾
using shared_Obj = std::shared_ptr<Obj>;				// �������߲���
using shared_Blt = std::shared_ptr<Bullet>;				// �������߲���
using shared_E_Blt = std::shared_ptr<E_Bullet>;				// �������߲���
using AnimVector = std::vector<std::pair<int, int>>;	// ��Ұ��ݗp���߱

// ��Ұ��݂̎��
enum class ANIM
{
	NORMAL,	// �ʏ�
	EX,		// ����
	DEATH,	// ���S
	MAX
};

// ��޼ު�Ă̎��
enum class UNIT
{
	PLAYER,	// ��ڲ԰
	P_Blt,	// ��ڲ԰�̒e
	ENEMY,	// �G
	E_Blt,	// �G�̒e
	MAX
};

// ��а�̎��
enum class ENEMY_TYPE
{
	A,	// 
	B,	// 
	C,	//
	MAX
};

// ��а�̈����p
enum class Enemy_State_ID
{
	POS,	// ���W
	TYPE,	// ���
	SIZE,	// �傫��
	AIM,	// �ړI�n
	MAX
};

// ��а�ړ�����
enum class MOVE_TYPE
{
	SIGMOID,	// ���Ӳ��
	SPIRAL,		// ��]
	MOVE_LR,	// ���E�ړ�
	MAX
};

// ��а�̍��E�ړ��p
enum class TYPE_LR
{
	TYPE_L,	// ���ړ�
	TYPE_R,	// �E�ړ�
	MAX
};
// using�錾
// ��а�̖ړI�n��ړ�����
using AIM_VEC = std::vector<std::pair<Vector2Dbl, MOVE_TYPE>>;

// ��а�̲ݽ�ݽ���p�������(Vector2 ���W,�G�̎��,����,�ړI�n)
using Enemy_State = std::tuple<Vector2Dbl, ENEMY_TYPE, Vector2, AIM_VEC,std::list<std::shared_ptr<E_Bullet>>&>;

class Obj
{
public:
	Obj();
	virtual ~Obj();

	virtual void Draw(void);						// �`��֐�
	void Draw(int id);								// �����t���`��֐�(������ImageMng��GetID������)

	virtual void UpDate(void) = 0;					// ��ԍX�V�p�֐�(�������z�֐�)

	virtual UNIT GetUnitType(void) = 0;				// UNIT��ID��Ԃ�

	bool animKey(const ANIM key);					// _animKey�̾���
	const ANIM animKey(void) const;					// _animKey�̹ޯ��

	const Vector2Dbl pos(void) const;				// _pos�̹ޯ��
	const Vector2 size(void) const;					// _size�̹ޯ��
	void hp(const int val);							// _hp�̾���
	const int hp(void)const;						// _hp�̹ޯ��

	bool isAnimEnd(void);							// ��Ұ��݂��ݼ��ėp

	void SetAlive(bool alive);						// ��������p�׸ނ̾���
	bool isAlive(void) { return _alive; };			// ���q�֐�
	bool isDeath(void) { return _death; };			// ���q�֐�(���S�p)

	void CheckHit(std::vector<shared_Obj>& objList);	// �����蔻��(��ڲ԰�ƴ�а�p)
	void CheckHit(std::list<std::shared_ptr<Bullet>>& bulletlist);	// �����蔻��(�e�p)
	void CheckHit(std::list<std::shared_ptr<E_Bullet>>& bulletlist);	// �����蔻��(�e�p)

private:
	std::map<ANIM, AnimVector>_animMap;				// ��Ұ��ݓo�^�pmap
	ANIM _animKey;									// ��Ұ��݂̖��OID
	int _animFrame;									// ��Ұ��݂��ڰѐ�

protected:
	bool SetAnim(const ANIM key, AnimVector& data);	// ��Ұ��ݓo�^�p�֐�
	int LastAnimCnt(void);							// ��Ұ��ݶ��Ă̎擾
	int _animCount;									// ��Ұ��ݗp����

	bool DestroyPlock(void);						// _alive = false���ݼ��ı�Ұ��݂��I�������_death =true�ɂ���
	float _angle;									// ��Ұ��݂̌����p

	bool _alive;									// ��������p�׸ޒʏ�true,false���ݼ��ı�Ұ��݂Ȃǂ��g�p����
	bool _death;									// ���S����p�׸ޒʏ�false,�ݼ��ı�Ұ��݂��I�������true�ɂȂ�

	Vector2Dbl _pos;								// ���W
	Vector2 _size;									// ��޼ު�Ă̑傫��
	Vector2Dbl _speed;								// ���x
	int _hp;										// �̗�
	int _oldHp;										// 1�ڰёO�̗̑�
};

// map
// kye = std::string �ű�Ұ��ݖ�
// data = [�摜ID��ڰѐ�]
// �ϐ�

// map<ANIM(���), vecor<pair<int�摜ID, intFrame��>>>
// _animMap[ANIM::���][�ڰ�].first(IMAGE_ID("���O")[�Z])
// _animMap[ANIM::���][�ڰ�].second(�\�������ڰѐ�)
// _animMap[ANIM::���].size()���v�f��

//std::map   �ikey��Ұ��݂�ID   �idate�摜��ID��\���ڰсj�P�R�}������Ε���������vector���g���j��̃A�j���[�V����
//std::pair<�^1,�^2>���O;�錾�̏ꍇ
// �I�[�1(��