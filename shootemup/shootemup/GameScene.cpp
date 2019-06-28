#include "GameScene.h"
#include <DxLib.h>



GameScene::GameScene()
{
	Init();
}


GameScene::~GameScene()
{
}

unique_Base GameScene::UpDate(unique_Base own)
{
	frameCnt = frame / 60;
	frameCnt %= 60;
	if (frameCnt < 20)
	{
		shotPT = SHOTPT_3WAY;
	}
	else if (frameCnt < 30)
	{
		shotPT = SHOTPT_HOUSYA;
	}
	else if (frameCnt < 40)
	{
		shotPT = SHOTPT_BARAM;
	}
	else
	{
		shotPT = SHOTPT_BARAM;
	}

	isDebugMode = keystate[KEY_INPUT_P];

	//背景
	DrawExtendGraph(0, 0, 640, 480, bgH[bgidx / 8], false);
	bgidx = (bgidx + 1) % 32;

	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	skyy = (skyy + 1) % 480;
	skyy2 = (skyy2 + 2) % 480;
	DrawExtendGraph(0, skyy, 640, skyy + 480, skyH, true);
	DrawExtendGraph(0, skyy - 480, 640, skyy, skyH, true);
	DrawExtendGraph(0, skyy2, 640, skyy2 + 480, sky2H, true);
	DrawExtendGraph(0, skyy2 - 480, 640, skyy2, sky2H, true);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL, 0);


	//プレイヤー
	if (keystate[KEY_INPUT_RIGHT]) {
		playerpos.x = min(640, playerpos.x + 4);
	}
	else if (keystate[KEY_INPUT_LEFT]) {
		playerpos.x = max(0, playerpos.x - 4);
	}
	if (keystate[KEY_INPUT_UP]) {
		playerpos.y = max(0, playerpos.y - 4);
	}
	else if (keystate[KEY_INPUT_DOWN]) {
		playerpos.y = min(480, playerpos.y + 4);
	}

	int pidx = (frame / 4 % 2) * 5 + 3;
	DrawRotaGraph(playerpos.x, playerpos.y, 2.0f, 0.0f, playerH[pidx], true);
	if (isDebugMode) {
		//自機の本体(当たり判定)
		DrawCircle(playerpos.x, playerpos.y, playerRadius, 0xffaaaa, false, 3);
	}

	if (shotPT == SHOTPT_3WAY)
	{
		//弾発射
		if (frame % 15 == 0)
		{
			for (int i = 2; i > -3; i--)
			{
				for (auto& b : bullets)
				{
					if (!b.isActive)
					{
						b.pos = enemypos;
						float angle = atan2f(playerpos.y - b.pos.y, playerpos.x - b.pos.x);
						b.vel = { 0,0 };

						b.vel.x = cos(angle + (15 * i * DX_PI / 180)) * 2;
						b.vel.y = sin(angle + (15 * i * DX_PI / 180)) * 2;
						b.isActive = true;
						break;
					}
				}
			}
		}
	}
	else if (shotPT == SHOTPT_HOUSYA)
	{
		for (int i = 0; i < 360 / 15; i++)
		{
			if (frame % 30 == 0)
			{
				for (auto& b : bullets)
				{
					if (!b.isActive)
					{
						b.pos = enemypos;
						float angle = atan2f(playerpos.y - b.pos.y, playerpos.x - b.pos.x);
						b.vel = { 0,0 };
						b.vel.x = cos(angle + (15 * i * DX_PI / 180)) * 2;
						b.vel.y = sin(angle + (15 * i * DX_PI / 180)) * 2;
						b.isActive = true;
						break;
					}
				}
			}
		}
	}

	bool stop = false;
	if (frameCnt >= 30 && frameCnt <= 34)
	{
		stop = true;
	}

	if (frameCnt >= 34 && stop)
	{
		stop = false;
		int cnt = 0;
		for (auto& b : bullets)
		{
			if (b.isActive)
			{
				float angle = atan2f(playerpos.y - b.pos.y, playerpos.x - b.pos.x);

				b.vel.x = cos(angle) * 1;
				b.vel.y = sin(angle) * 1;

			}
			cnt++;
		}
	}

	//弾の更新および表示
	for (auto& b : bullets) {
		if (!b.isActive) {
			continue;
		}


		//弾の現在座標に弾の現在速度を加算してください
		if (!stop)
		{
			b.pos += b.vel;
		}
		//float angle = atan2f(playerpos.y - b.pos.y,playerpos.x - b.pos.x);
		//弾の角度をatan2で計算してください。angleに値を入れるんだよオゥ

		DrawRotaGraph(b.pos.x, b.pos.y, 1.0f, 0, bulletH, true);

		if (isDebugMode) {
			//弾の本体(当たり判定)
			DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
		}
		//弾を殺す
		if (b.pos.x + 16 < 0 || b.pos.x - 16 > 640 ||
			b.pos.y + 24 < 0 || b.pos.y - 24 > 480) {
			b.isActive = false;
		}

		//あたり！
		//↓のIsHitは実装を書いてません。自分で書いてください。
		if (IsHit(b.pos, bulletRadius, playerpos, playerRadius)) {
			//当たった反応を書いてください。
			b.isActive = false;
		}
		if (!stop)
		{
			b.pos = b.pos + b.vel;
		}

	}

	//敵の表示
	enemypos.x = abs((int)((frame + 320) % 1280) - 640);
	int eidx = (frame / 4 % 2);
	DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx], true);

	if (isDebugMode) {
		//敵の本体(当たり判定)
		DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
	}
	++frame;
	return unique_Base(std::move(own));
}

void GameScene::Init()
{
	//背景用
	LoadDivGraph("img/bganim.png", 4, 4, 1, 256, 192, bgH);

	skyH = LoadGraph("img/sky.png");
	sky2H = LoadGraph("img/sky2.png");

	bulletH = LoadGraph("img/bullet.png");
	LoadDivGraph("img/player.png", 10, 5, 2, 16, 24, playerH);

	LoadDivGraph("img/enemy.png", 2, 2, 1, 32, 32, enemyH);
}

bool GameScene::IsHit(const Position2 & posA, float radiusA, const Position2 & posB, float radiusB)
{
	return hypot(posA.x - posB.x, posA.y - posB.y) < radiusA + radiusB;
}
