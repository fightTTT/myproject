#pragma once
#include "Obj.h"
class Bullet :
	public Obj
{
public:
	Bullet();
	Bullet(Vector2Dbl pos);
	~Bullet();
	void Draw(void)override;					// 描画関数
	void UpDate(void)override;					// 状態更新用関数(純粋仮想関数)
	UNIT GetUnitType(void)override;				// UNITのIDを返す

	bool actFlg(void){ return _actFlg; };		// 現在の状態を返す
	void SetactFlg(Vector2Dbl pos);				// ｾｯﾀｰ｡再発射の時に使用､発射したいposを入力､_actFlgはtrueになる
	void SetactFlg(void);						// 弾を非ｱｸﾃｨﾌﾞにするときに使用
private:
	void Init(void);

	bool _actFlg;								// 生存用ﾌﾗｸﾞ
};

