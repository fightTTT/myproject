#include <DxLib.h>
#include <Scene/SceneMng.h>
#include <Scene/GameScene.h>
#include <Public/ImageMng.h>
#include <_Debug/_DebugConOut.h>
#include <_Debug/_DebugDispOut.h>

// ²İ½Àİ½‚µ±ÄŞÚ½‚ğ“n‚·¤ÃŞØ°Äæ‚à“o˜^
std::unique_ptr<SceneMng, SceneMng::SceneMngDeleter> SceneMng::s_Instance(new SceneMng);

SceneMng::SceneMng() :screenSize{ 800,600 }, gameScreenSize{ 500, 390 }, gameScreenPos{ (screenSize.x - gameScreenSize.x) / 2, (screenSize.y - gameScreenSize.y) / 2 }
{
}

SceneMng::~SceneMng()
{
}

bool SceneMng::SysInit(void)
{
	// ¼½ÃÑˆ—
	SetGraphMode(screenSize.x, screenSize.y, 16);		// 65536FÓ°ÄŞ‚Éİ’è
	ChangeWindowMode(true);								// true:window@false:ÌÙ½¸Ø°İ

	SetWindowText("GALAGA");							// ³¨İÄŞ³À²ÄÙ
	if (DxLib_Init() == -1) return false;				// DX×²ÌŞ×Ø‰Šú‰»ˆ—	

	// ÃŞÊŞ¯¸—p(o—Í‚Ícin¤cout‚ÅOK)
	TRASE("DXLIB‰Šú‰»Š®—¹\n");

	// ‰æ‘œ“o˜^
	SET_IMAGE_ID("˜g", "image/frame.png");

	// ÃŞÊŞ¯¸—p‚Ì½¸Ø°İì¬(ƒ¿’l200)
	_DebugSetup(200);

	return true;
}

void SceneMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);						// ‚Ğ‚Æ‚Ü‚¸ÊŞ¯¸ÊŞ¯Ì§‚É•`‰æ

	ClsDrawScreen();	// ‰æ–ÊÁ‹

	for (auto _dque : _drawList)
	{
		// ‰æ‘œ‚Ì•`‰æ
		DrawGraph(
			std::get<static_cast<int>(DRAW_QUE::X)>(_dque),	// XÀ•W
			std::get<static_cast<int>(DRAW_QUE::Y)>(_dque),	// YÀ•W
			std::get<static_cast<int>(DRAW_QUE::IMAGE)>(_dque),	// ¸Ş×Ì¨¯¸ÊİÄŞÙ
			true);
	}

	ScreenFlip();		// ¹Ş°ÑÙ°Ìß‚ÌÅŒã‚É•K‚¸•K—v
}

void SceneMng::Run(void)
{
	// ¼½ÃÑ‚Ì‰Šú‰»
	SysInit();

	// ²Ò°¼ŞÏÈ°¼Ş¬°‚Ì²İ½Àİ½
	ImageMng::GetInstance().GetID("·¬×", "image/char.png", Vector2(30, 32), Vector2(10, 10));
	ImageMng::GetInstance().GetID("PL”š”­", "image/pl_blast.png", Vector2(64, 64), Vector2(4, 1));
	ImageMng::GetInstance().GetID("“G”š”­", "image/en_blast.png", Vector2(64, 64), Vector2(5, 1));
	ImageMng::GetInstance().GetID("’e", "image/shot.png", Vector2(3, 4), Vector2(2, 1));

	// ÕÆ°¸Îß²İÀ°‚Ìì¬¤ÃŞÌ«ÙÄºİ½Ä×¸À‚ÅŒÄ‚Ô‚Ì‚Å()‚ğ•t‚¯‚é
	_activeScene = std::make_unique<GameScene>();

	// ---------- ¹Ş°ÑÙ°Ìß
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// ÃŞÊŞ¯¸—p‚Ì•`‰æ
		_DebugStartDraw

			// ‰æ‘œ‚Ì·­°íœ
			_drawList.clear();

		// move‚Å©•ª©g‚ÌuniqueÎß²İÀ°‚ÌŠ—LŒ ‚ğ“n‚·
		_activeScene = _activeScene->UpDate(std::move(_activeScene));

		// ‰æ‘œ‚Ì·­°’Ç‰Á
		addDrawQue({ IMAGE_ID("˜g")[0],0,0 });

		// ÃŞÊŞ¯¸‚ÌµİµÌØ‚è‘Ö‚¦(Œ»İ‚ÍQ,W·°)
		_DebugAddDraw

			// •`‰æ
			Draw();

		// ¶³İÄ‚ği‚ß‚é
		_cnt++;
	}

}

bool SceneMng::addDrawQue(DrawQueT dQue)
{
	// ÊİÄŞÙ‚ªæ“¾‚Å‚«‚È‚¯‚ê‚Îfalse‚ğ•Ô‚·
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) == -1)
	{
		return false;
	}

	// —v‘f’Ç‰Á
	_drawList.emplace_back(dQue);

	return true;
}

const int SceneMng::cnt(void)
{
	return _cnt;
}
