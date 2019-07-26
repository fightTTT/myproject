#pragma once
#include <memory>
#include <vector>
#include <map>
#include "../common/Vector2.h"

enum class ANIM	// �A�j���[�V�����^�C�v
{
	NORMAL,		// �ʏ�
	EX,			// ����
	DEATH,		// ���j
	MAX
};

enum class UNIT
{
	PLAYER,		// �v���C���[���j�b�g
	ENEMY,		// �G
	SHOT,
	MAX
};

class Obj;
using Shared_Obj = std::shared_ptr<Obj>;
using AnimVector = std::vector<std::pair<int, int>>;	// 

class Obj
{
public:
	Obj();
	virtual ~Obj();
	virtual void Draw(void);
	void Draw(int id);
	virtual UNIT GetUnit(void) = 0;
	virtual void SetMove(void);

	// _animkey���擾
	const ANIM AnimKey(void)const;		

	// _animKey�ɃA�j���[�V�����^�C�v���Z�b�g����
	bool AnimKey(const ANIM animkey);	

	// pos���擾
	const Vector2Dbl Pos()const;

	bool IsAnimEnd(void);
	bool DeathProc(void);

	// pos�Z�b�g
	void Pos(const Vector2Dbl &pos);

	// �����m�F
	const bool IsAlive() { return _alive; };
	const bool IsDeath() { return _death; };
protected:

	// �A�j���[�V���������Z�b�g����
	bool SetAnim(const ANIM key, AnimVector &data);	
	Vector2Dbl _pos;		// ���W
	Vector2 _size;		// �L�����̑傫��
	bool _alive;		// �����Ă��邩	true...�����@false...���S
	bool _death;	
	float _angle;
	int _animCnt;		// �A�j���[�V�����J�E���^�[
	
private:
	ANIM _animKey;		// �A�j���[�V�����^�C�v
	int _animFram;		// �A�j���[�V�����̃t���[����

	std::map<ANIM, const AnimVector> _animMap;		// �A�j���[�V���������i�[���Ă���map
};
