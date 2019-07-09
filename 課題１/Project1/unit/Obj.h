#pragma once
#include <memory>
#include <vector>
#include <map>
#include "../common/Vector2.h"

enum class ANIM	// �A�j���[�V�����^�C�v
{
	NORMAL,		// �ʏ�
	EX,			// ����
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
using AnimVector = std::vector<std::pair<int, int>>;	// first...���݂̓��͏��  second...1�t���[���O�̓��͏��


class Obj
{
public:
	Obj();
	virtual ~Obj();
	virtual void Draw(void);
	void Draw(int id);
	virtual UNIT GetUnit(void) = 0;
	virtual void SetMove();

	// _animkey���擾
	const ANIM AnimKey()const;		

	// _animKey�ɃA�j���[�V�����^�C�v���Z�b�g����
	bool AnimKey(const ANIM animkey);	

	// pos���擾
	const Vector2 Pos()const;

	// pos�Z�b�g
	void Pos(const Vector2 &pos);

	// �����m�F
	const bool IsAlive() { return _active; };
protected:

	// �A�j���[�V���������Z�b�g����
	bool SetAnim(const ANIM key, AnimVector &data);	
	Vector2 _pos;		// ���W
	Vector2 _size;		// �L�����̑傫��
	bool _active;
private:
	ANIM _animKey;		// �A�j���[�V�����^�C�v
	int _animFram;		// �A�j���[�V�����̃t���[����
	int _animCnt;		// �A�j���[�V�����J�E���^�[
	

	std::map<ANIM, const AnimVector> _animMap;		// �A�j���[�V���������i�[���Ă���map
};

