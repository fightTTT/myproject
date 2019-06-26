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
using AnimVector = std::vector<std::pair<int, int>>;


class Obj
{
public:
	Obj();
	virtual ~Obj();
	virtual void Draw(void);
	void Draw(int id);
	virtual UNIT GetUnit(void) = 0;
protected:
	bool SetAnim(const ANIM key, AnimVector &data);	// �A�j���[�V���������Z�b�g����
	Vector2 _pos;
	ANIM _animKey;
	int _animFram;
	int _animCnt;

private:
	int cnt;
	std::map<ANIM, const AnimVector> _animMap;		// �A�j���[�V���������i�[���Ă���map
};

