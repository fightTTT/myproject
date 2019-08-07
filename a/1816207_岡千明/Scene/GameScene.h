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

	shared_Base UpDate(shared_Base own)override;		// 状態遷移
	void Draw(void);									// 描画関数

	SCN_ID GetScnID(void) override;						// ｼｰﾝのIDを返す

private:
	bool Init(void);									// 初期化関数

	bool EnemyData(void);								// ｴﾈﾐｰのﾃｰﾌﾞﾙﾃﾞｰﾀを作成
	bool EnemyInit(void);								// ｴﾈﾐｰのｲﾝｽﾀﾝｽ用ﾃﾞｰﾀ作成
	void EnemyInstance(void);							// ｴﾈﾐｰのｲﾝｽﾀﾝｽを行う

	std::vector<shared_Obj> _objList;					// ﾌﾟﾚｲﾔｰやｴﾈﾐｰを入れるﾘｽﾄ(vector)
	std::list<shared_Blt> _bulletList;					// ﾌﾟﾚｲﾔｰの弾を入れるﾘｽﾄ
	std::list<shared_E_Blt> _e_BulletList;				// ｴﾈﾐｰの弾を入れるﾘｽﾄ

	int _cnt = 0;										// ｴﾈﾐｰのｲﾝｽﾀﾝｽ用ｶｳﾝﾄ
	std::vector<Vector2Dbl> _enemyPos;					// ｴﾈﾐｰｲﾝｽﾀﾝｽ時の座標ﾃｰﾌﾞﾙ
	std::vector<Vector2Dbl> _enemyStartPos;				// ｴﾈﾐｰの出現posを入れるﾃｰﾌﾞﾙ
	std::vector<Vector2> _aimPos;						// ｴﾈﾐｰの目的地用ﾃｰﾌﾞﾙ
	std::vector<Vector2> _enemySize;					// ｴﾈﾐｰのｻｲｽﾞを入れるvector
	std::vector<ENEMY_TYPE> _enemyType;					// ｴﾈﾐｰの種類を入れるvector
	AIM_VEC _enemyAim;									// ｴﾈﾐｰの目的座標と移動ﾀｲﾌﾟを入れる｡pair型
	std::vector<int> _enemyInsCnt;						// ｴﾈﾐｰのｲﾝｽﾀﾝｽする時間を入れるvector

	int _ghGameScreen;									// 描画区域作成用変数

	bool keyFlagSp = (CheckHitKey(KEY_INPUT_SPACE));	// ｲﾝｽﾀﾝｽで使用(ﾃﾞﾊﾞｯｸ用)
	bool keyFlagSpOld = keyFlagSp;

	bool _staretFlag = false;							// ｹﾞｰﾑ開始用ﾌﾗｸﾞ
	bool _clearFlag = false;							// ｹﾞｰﾑｸﾘｱ用ﾌﾗｸﾞ
	bool _gameOverFlag = false;							// ｹﾞｰﾑｵｰﾊﾞｰ用ﾌﾗｸﾞ
	int _gameOverCnt = 60 * 3;							// ｹﾞｰﾑｵｰﾊﾞｰからｼｰﾝが変わるまでのｶｳﾝﾄ

	int _gameCnt = 0;									// ｹﾞｰﾑ用ｶｳﾝﾄ

	int _stageNum = 1;									// ｽﾃｰｼﾞ用ﾅﾝﾊﾞｰ
	int _playerLife;									// ﾌﾟﾚｲﾔｰのﾗｲﾌ
};

