#include <DxLib.h>
#include <Scene/SceneMng.h>
#include <Scene/GameScene.h>
#include <Public/ImageMng.h>
#include <_Debug/_DebugConOut.h>
#include <_Debug/_DebugDispOut.h>

// ｲﾝｽﾀﾝｽしｱﾄﾞﾚｽを渡す､ﾃﾞﾘｰﾄ先も登録
std::unique_ptr<SceneMng, SceneMng::SceneMngDeleter> SceneMng::s_Instance(new SceneMng);

SceneMng::SceneMng() :screenSize{ 800,600 }, gameScreenSize{ 500, 390 }, gameScreenPos{ (screenSize.x - gameScreenSize.x) / 2, (screenSize.y - gameScreenSize.y) / 2 }
{
}

SceneMng::~SceneMng()
{
}

bool SceneMng::SysInit(void)
{
	// ｼｽﾃﾑ処理
	SetGraphMode(screenSize.x, screenSize.y, 16);		// 65536色ﾓｰﾄﾞに設定
	ChangeWindowMode(true);								// true:window　false:ﾌﾙｽｸﾘｰﾝ

	SetWindowText("GALAGA");							// ｳｨﾝﾄﾞｳﾀｲﾄﾙ
	if (DxLib_Init() == -1) return false;				// DXﾗｲﾌﾞﾗﾘ初期化処理	

	// ﾃﾞﾊﾞｯｸ用(出力はcin､coutでOK)
	TRASE("DXLIB初期化完了\n");

	// 画像登録
	SET_IMAGE_ID("枠", "image/frame.png");

	// ﾃﾞﾊﾞｯｸ用のｽｸﾘｰﾝ作成(α値200)
	_DebugSetup(200);

	return true;
}

void SceneMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);						// ひとまずﾊﾞｯｸﾊﾞｯﾌｧに描画

	ClsDrawScreen();	// 画面消去

	for (auto _dque : _drawList)
	{
		// 画像の描画
		DrawGraph(
			std::get<static_cast<int>(DRAW_QUE::X)>(_dque),	// X座標
			std::get<static_cast<int>(DRAW_QUE::Y)>(_dque),	// Y座標
			std::get<static_cast<int>(DRAW_QUE::IMAGE)>(_dque),	// ｸﾞﾗﾌｨｯｸﾊﾝﾄﾞﾙ
			true);
	}

	ScreenFlip();		// ｹﾞｰﾑﾙｰﾌﾟの最後に必ず必要
}

void SceneMng::Run(void)
{
	// ｼｽﾃﾑの初期化
	SysInit();

	// ｲﾒｰｼﾞﾏﾈｰｼﾞｬｰのｲﾝｽﾀﾝｽ
	ImageMng::GetInstance().GetID("ｷｬﾗ", "image/char.png", Vector2(30, 32), Vector2(10, 10));
	ImageMng::GetInstance().GetID("PL爆発", "image/pl_blast.png", Vector2(64, 64), Vector2(4, 1));
	ImageMng::GetInstance().GetID("敵爆発", "image/en_blast.png", Vector2(64, 64), Vector2(5, 1));
	ImageMng::GetInstance().GetID("弾", "image/shot.png", Vector2(3, 4), Vector2(2, 1));

	// ﾕﾆｰｸﾎﾟｲﾝﾀｰの作成､ﾃﾞﾌｫﾙﾄｺﾝｽﾄﾗｸﾀで呼ぶので()を付ける
	_activeScene = std::make_unique<GameScene>();

	// ---------- ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ﾃﾞﾊﾞｯｸ用の描画
		_DebugStartDraw

			// 画像のｷｭｰ削除
			_drawList.clear();

		// moveで自分自身のuniqueﾎﾟｲﾝﾀｰの所有権を渡す
		_activeScene = _activeScene->UpDate(std::move(_activeScene));

		// 画像のｷｭｰ追加
		addDrawQue({ IMAGE_ID("枠")[0],0,0 });

		// ﾃﾞﾊﾞｯｸのｵﾝｵﾌ切り替え(現在はQ,Wｷｰ)
		_DebugAddDraw

			// 描画
			Draw();

		// ｶｳﾝﾄを進める
		_cnt++;
	}

}

bool SceneMng::addDrawQue(DrawQueT dQue)
{
	// ﾊﾝﾄﾞﾙが取得できなければfalseを返す
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) == -1)
	{
		return false;
	}

	// 要素追加
	_drawList.emplace_back(dQue);

	return true;
}

const int SceneMng::cnt(void)
{
	return _cnt;
}
