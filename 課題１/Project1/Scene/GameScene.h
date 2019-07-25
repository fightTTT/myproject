#pragma once
#include <vector>
#include <array>
#include "BaseScene.h"
#include "../unit/Obj.h"
#include "../unit/Enemy.h"
#include "../Input/InputState.h"


class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	Unique_Base UpDate(Unique_Base own) override;

	// ���g�̃V�[���̎�ނ�Ԃ�
	SCN_ID GetScnID(void) override;		

	// Enemy��ǉ�����
	void AddEnemy(EnemyData data);		

	void Draw(void);
protected:
	void Init(void)override;
private:
	std::vector<Shared_Obj> _objList;		// �L�����N�^�[���Ǘ�����List
	int _ghGameScreen;
	std::array<Vector2Dbl, 5> enemAppPos;	// �G�̏o�����W

	// �f�o�b�O�p
	//--------------------
	char key[256];
	int checkKey = 0;
	int checkKeyOld = 0;
	std::vector<char> enemON;
	//--------------------
};

