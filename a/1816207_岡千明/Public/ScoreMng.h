#pragma once

// 定義
#define lpScoreMng ScoreMng::GetInstance()

class ScoreMng
{
public:
	static ScoreMng& GetInstance()	// ｱﾄﾞﾚｽが欲しいためﾎﾟｲﾝﾀｰか参照で
	{
		return (*s_Instance);		// *で中身(ｸﾗｽの実体)を返す
	}

	const void AddScore(int score);	// ｽｺｱを加算
	void ScoreReset(void);			// ｽｺｱの初期化(0にする)
	void Draw(void);				// 描画

private:
	// 関数ｵﾌﾞｼﾞｪｸﾄ
	// ﾃﾞｽﾄﾗｸﾀを呼ぶ
	struct ScoreMngDeleter
	{
		void operator()(ScoreMng* sceneMng)const
		{
			delete sceneMng;
		}
	};
	ScoreMng();
	~ScoreMng();

	bool Init(void);	// 初期化用
	int _score;			// ｽｺｱ保存用
	static std::unique_ptr<ScoreMng, ScoreMngDeleter> s_Instance;	// ｲﾝｽﾀﾝｽ用ﾕﾆｰｸﾎﾟｲﾝﾀｰ
};

