#pragma once
#include <vector>
#include <array>
#include <memory>
#include "BaseScene.h"
#include "../unit/Obj.h"
#include "../unit/Enemy.h"
#include "../Input/InputState.h"
#include "../StarScroll.h"


using EnemLine = std::tuple<ENM_TYPE,Vector2Dbl,int,int>;		// �G�̎�ށA�W���ꏊ�̍�����W�AX���@���AY���@��

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

	// shot�̓����蔻��
	bool HitShot(void);		

	std::vector<Shared_Obj> _objList;		// �L�����N�^�[���Ǘ�����List
	int _ghGameScreen;
	std::array<Vector2Dbl, 6> enemAppPos;	// �G�̏o�����W

	std::unique_ptr<StarScroll> star;

	// �f�o�b�O�p
	//--------------------
	char key[256];
	int checkKey = 0;
	int checkKeyOld = 0;
	std::vector<EnemLine> enemLine;
	std::array<std::vector<int>, 3> enemNum;
	//--------------------
};

