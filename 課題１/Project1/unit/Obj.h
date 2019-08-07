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
	virtual std::vector<Shared_Obj> GetShotData() = 0;
	
	// _animkey���擾
	const ANIM AnimKey(void)const;		

	// _animKey�ɃA�j���[�V�����^�C�v���Z�b�g����
	bool AnimKey(const ANIM animkey);	

	// pos���擾
	const Vector2Dbl Pos()const;
	const Vector2Dbl Size()const;

	bool IsAnimEnd(void);
	bool DeathProc(void);

	// pos�Z�b�g
	void Pos(const Vector2Dbl &pos);

	// �����m�F
	const bool IsAlive() { return _alive; };
	const bool IsDeath() { return _death; };
	const int Life() { return _life; };
	void IsAlive(const bool alive);
	void IsDeath(const bool Death);
	void Life(const int life);

protected:

	// �A�j���[�V���������Z�b�g����
	bool SetAnim(const ANIM key, AnimVector &data);	
	const ANIM GetAnimKey(void) { return _animKey; };
	Vector2Dbl _pos;		// ���W
	Vector2Dbl _size;		// �L�����̑傫��
	double speed;			// �ړ����x
	bool _alive;		// �����Ă��邩	true...�����@false...���S
	bool _death;	
	float _angle;
	int _animCnt;		// �A�j���[�V�����J�E���^�[
	int _life;			// �@�̂̎c�@
	
private:
	ANIM _animKey;		// �A�j���[�V�����^�C�v
	int _animFram;		// �A�j���[�V�����̃t���[����

	std::map<ANIM, const AnimVector> _animMap;		// �A�j���[�V���������i�[���Ă���map
};
