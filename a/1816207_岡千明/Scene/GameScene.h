#pragma once
#include <list>
#include <vector>
#include "BaseScene.h"
#include <Unit/Obj.h>

class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();

	shared_Base UpDate(shared_Base own)override;		// ��ԑJ��
	void Draw(void);									// �`��֐�

	SCN_ID GetScnID(void) override;						// ��݂�ID��Ԃ�

private:
	bool Init(void);									// �������֐�

	bool EnemyData(void);								// ��а��ð����ް����쐬
	bool EnemyInit(void);								// ��а�̲ݽ�ݽ�p�ް��쐬
	void EnemyInstance(void);							// ��а�̲ݽ�ݽ���s��

	std::vector<shared_Obj> _objList;					// ��ڲ԰���а������ؽ�(vector)
	std::list<shared_Blt> _bulletList;					// ��ڲ԰�̒e������ؽ�
	std::list<shared_E_Blt> _e_BulletList;				// ��а�̒e������ؽ�

	int _cnt = 0;										// ��а�̲ݽ�ݽ�p����
	std::vector<Vector2Dbl> _enemyPos;					// ��а�ݽ�ݽ���̍��Wð���
	std::vector<Vector2Dbl> _enemyStartPos;				// ��а�̏o��pos������ð���
	std::vector<Vector2> _aimPos;						// ��а�̖ړI�n�pð���
	std::vector<Vector2> _enemySize;					// ��а�̻��ނ�����vector
	std::vector<ENEMY_TYPE> _enemyType;					// ��а�̎�ނ�����vector
	AIM_VEC _enemyAim;									// ��а�̖ړI���W�ƈړ����߂�����pair�^
	std::vector<int> _enemyInsCnt;						// ��а�̲ݽ�ݽ���鎞�Ԃ�����vector

	int _ghGameScreen;									// �`����쐬�p�ϐ�

	bool keyFlagSp = (CheckHitKey(KEY_INPUT_SPACE));	// �ݽ�ݽ�Ŏg�p(���ޯ��p)
	bool keyFlagSpOld = keyFlagSp;

	bool _staretFlag = false;							// �ްъJ�n�p�׸�
	bool _clearFlag = false;							// �ްѸر�p�׸�
	bool _gameOverFlag = false;							// �ްѵ��ް�p�׸�
	int _gameOverCnt = 60 * 3;							// �ްѵ��ް���缰݂��ς��܂ł̶���

	int _gameCnt = 0;									// �ްїp����

	int _stageNum = 1;									// �ð�ޗp���ް
	int _playerLife;									// ��ڲ԰��ײ�
};

