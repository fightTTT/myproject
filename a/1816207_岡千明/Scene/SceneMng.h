#pragma once
#include <memory>
#include <vector>
#include <common/VECTOR2.h>
#include <Scene/BaseScene.h>

// 定義
#define lpSceneMng SceneMng::GetInstance()

// using宣言
using DrawQueT = std::tuple<int, int, int>; // ｸﾞﾗﾌｨｯｸﾊﾝﾄﾞﾙ､x座標､y座標

// 画像用tuple変数
enum class DRAW_QUE
{
	IMAGE,	// ｸﾞﾗﾌｨｯｸﾊﾝﾄﾞﾙ
	X,		// 座標X
	Y		// 座標Y
};

class SceneMng
{
public:
	static SceneMng& GetInstance()	// ｱﾄﾞﾚｽが欲しいためﾎﾟｲﾝﾀｰか参照で
	{
		return (*s_Instance);		// *で中身(ｸﾗｽの実体)を返す
	}

	void Run(void);					// ｹﾞｰﾑﾙｰﾌﾟ

	bool addDrawQue(DrawQueT dQue);	// 画像のｷｭｰ追加用関数

	const Vector2 screenSize;		// ｽｸﾘｰﾝのｻｲｽﾞ
	const Vector2 gameScreenSize;	// ｹﾞｰﾑ画面のｻｲｽﾞ
	const Vector2 gameScreenPos;	// ｵﾌｾｯﾄ

	const int cnt(void);			// ｹﾞｯﾀｰ｡ｹﾞｰﾑ内ｶｳﾝﾄの取得

private:
	// 関数ｵﾌﾞｼﾞｪｸﾄ
	// ﾃﾞｽﾄﾗｸﾀを呼ぶ
	struct SceneMngDeleter
	{
		void operator()(SceneMng* sceneMng)const
		{
			delete sceneMng;
		}
	};

	SceneMng();
	~SceneMng();

	bool SysInit(void);				// ｼｽﾃﾑ初期化用関数

	void Draw(void);				// 描画関数

	std::vector<DrawQueT>_drawList;	// 画像保存用vector

	static std::unique_ptr<SceneMng, SceneMngDeleter> s_Instance;	// ｲﾝｽﾀﾝｽ用ﾕﾆｰｸﾎﾟｲﾝﾀｰ
	shared_Base _activeScene;		// 現在のｼｰﾝを入れるﾎﾟｲﾝﾀｰ

	int _cnt = 0;					// ｹﾞｰﾑ内ｶｳﾝﾄ(ｱﾆﾒｰｼｮﾝ統一用)
};

