#include <DxLib.h>
#include <time.h>
#include <cmath>
#include "Enemy.h"
#include "../_DebugDispOut.h"
#include "../_DebugConOut.h"
#include "../common/ImageMng.h"
#include "../SceneMng.h"
#include "../EnemyMove.h"

int Enemy::animCnt = 0;
//bool Enemy::enemGather = false;

Enemy::Enemy()
{
	Init();	
}

Enemy::Enemy(EnemyData& data)
{
	_pos = std::get<static_cast<int>(ENM_DATA::POS)>(data);
	_size = std::get<static_cast<int>(ENM_DATA::SIZE)>(data);
	_type = std::get<static_cast<int>(ENM_DATA::TYPE)>(data);
	_targetPos = std::get<static_cast<int>(ENM_DATA::TARGTPOS)>(data);
	_enemCnt = std::get<static_cast<int>(ENM_DATA::ENEMCNT)>(data);
	enemNum = std::get<static_cast<int>(ENM_DATA::ENEMNUM)>(data);
	Init();

	InstancePos = _pos;

	enemMoveData = std::make_unique<EnemyMove>(data);
}

Enemy::~Enemy()
{
}

bool Enemy::Init(void)
{
	enemyAnimFrame = 60;

	_animCnt = lpSceneMng.GetFrame() % enemyAnimFrame;


	AnimVector data;

	//data.push_back(std::make_pair(IMAGE_ID("キャラ")[0],30));

	// 上記のpush_backと同じ処理
	/*data.emplace_back(IMAGE_ID("キャラ")[10], 30);
	data.emplace_back(IMAGE_ID("キャラ")[11], 60);*/

	data.reserve(2);
	switch (_type)
	{
	case ENM_TYPE::A:
		data.emplace_back(IMAGE_ID("キャラ")[30], 30);
		data.emplace_back(IMAGE_ID("キャラ")[31], enemyAnimFrame);
		_life = 3;
		break;
	case ENM_TYPE::B:
		data.emplace_back(IMAGE_ID("キャラ")[20], 30);
		data.emplace_back(IMAGE_ID("キャラ")[21], enemyAnimFrame);
		_life = 1;
		break;
	case ENM_TYPE::C:
		
		data.emplace_back(IMAGE_ID("キャラ")[10], 30);
		data.emplace_back(IMAGE_ID("キャラ")[11], enemyAnimFrame);
		_life = 1;
		break;
	default:
		break;
	}

	SetAnim(ANIM::NORMAL, data);

	data.reserve(2);
	data.emplace_back(IMAGE_ID("キャラ")[34], 30);
	data.emplace_back(IMAGE_ID("キャラ")[35], enemyAnimFrame);

	SetAnim(ANIM::EX, data);

	data.reserve(5);
	data.emplace_back(IMAGE_ID("爆破")[0], 5);
	data.emplace_back(IMAGE_ID("爆破")[1], 15);
	data.emplace_back(IMAGE_ID("爆破")[2], 25);
	data.emplace_back(IMAGE_ID("爆破")[3], 35);
	data.emplace_back(IMAGE_ID("爆破")[4], 45);
	data.emplace_back(-1, 50);

	SetAnim(ANIM::DEATH, data);

	speed = 0.1;
	X = -10;
	
	step = 0.1;
	_alive = true;
	firstFlag = true;
	waitCnt = 0;
	

	return true;
}

void Enemy::Draw(void)
{
}

UNIT Enemy::GetUnit(void)
{
	return UNIT::ENEMY;
}

void Enemy::SetMove()
{
	//死んだらtrueになる関数
	if (DeathProc())
	{
		return;
	}

	EnemDamage();


	_posOld = _pos;


	int color = 0x00ff00;
	if (firstFlag == false)
	{
		color = 0xff0000;
	}

	
	_DbgDrawBox(static_cast<int>(_pos.x), static_cast<int>(_pos.y), static_cast<int>(_pos.x) + 32, static_cast<int>(_pos.y) + 32, color, true);


	enemMoveData->SetMove();

	_pos = enemMoveData->GetPos();
	_angle = enemMoveData->GetAngle();
	animCnt++;
}

std::vector<Shared_Obj> Enemy::GetShotData()
{
	return std::vector<Shared_Obj>();
}


void Enemy::EnemDamage(void)
{
	if (_life <= 0)
	{
		_alive = false;
	
	}

	if (!_alive)
	{
		AnimKey(ANIM::DEATH);
		return;
	}


	if (_type == ENM_TYPE::A && GetAnimKey() == ANIM::NORMAL)
	{
		if (_life <= 1)
		{
			AnimKey(ANIM::EX);
			_animCnt = lpSceneMng.GetFrame() % enemyAnimFrame;
		}
	}

}