#include<DxLib.h>
#include<cmath>
#include"Geometry.h"



enum SHOTPT
{
	SHOTPT_3WAY,
	SHOTPT_BARAM,
	SHOTPT_HOUSYA,
	SHOTPT_JUZI,
	SHOTPT_TUIJU,
	SHOTPT_MAX
};
///�����蔻��֐�
///@param posA A�̍��W
///@param radiusA A�̔��a
///@param posB B�̍��W
///@param radiusB B�̔��a
bool IsHit(const Position2& posA, float radiusA, const Position2& posB,  float radiusB) {
	//�����蔻����������Ă�������
	return hypot(posA.x - posB.x, posA.y - posB.y) < radiusA + radiusB;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(true);
	SetMainWindowText("1816019_�� ���q");
	if (DxLib_Init() != 0) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	//�w�i�p
	int bgH[4];
	LoadDivGraph("img/bganim.png", 4, 4, 1, 256, 192, bgH);

	int skyH = LoadGraph("img/sky.png");
	int sky2H = LoadGraph("img/sky2.png");

	auto bulletH=LoadGraph("img/bullet1.png");
	int playerH[10];
	LoadDivGraph("img/player.png", 10, 5, 2, 16, 24,playerH );

	int enemyH[2];
	LoadDivGraph("img/enemy.png", 2, 2, 1, 32, 32, enemyH);

	struct Bullet {
		Position2 pos;//���W
		Vector2 vel;//���x
		int speed;
		int tuijuCnt;
		float angle;
		bool isActive = false;//�����Ă邩�`�H
		bool flag = false;
	};

	

	//�e�̔��a
	float bulletRadius = 5.0f;

	//���@�̔��a
	float playerRadius = 10.0f;

	//�K����256���炢����Ƃ�
	Bullet bullets[256];

	SHOTPT shotPT;

	Position2 enemypos(320,50);//�G���W
	Position2 playerpos(320, 400);//���@���W

	unsigned int frame = 0;//�t���[���Ǘ��p
	int frameCnt;

	char keystate[256];
	bool isDebugMode = false;
	int skyy = 0;
	int skyy2 = 0;
	int bgidx = 0;
	int juzicnt = 0;
	int tuijuCnt = 0;
	bool stopFlag = false;

	for (auto& b : bullets)
	{
		b.speed = 2;
		b.tuijuCnt = 0;
	}

	while (ProcessMessage() == 0&&CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();

		GetHitKeyStateAll(keystate);

		frameCnt = frame / 60;
		frameCnt %= 60;
		if (frameCnt < 10)
		{
			shotPT = SHOTPT_JUZI;
		}
		else if (frameCnt < 13)
		{
			shotPT = SHOTPT_MAX;
		}
		else if(frameCnt < 20)
		{
			shotPT = SHOTPT_TUIJU;
		}
		else if (frameCnt < 40)
		{
			shotPT = SHOTPT_3WAY;
		}
		else if(frameCnt < 50)
		{
			shotPT = SHOTPT_BARAM;
		}
		else
		{
			shotPT = SHOTPT_HOUSYA;
			juzicnt = 0;
			stopFlag = false;

			for (auto& b : bullets)
			{
				b.flag = false;
			}
		}

		isDebugMode = keystate[KEY_INPUT_P];

		//�w�i
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


		//�v���C���[
		if (keystate[KEY_INPUT_RIGHT]) {
			playerpos.x = min(640,playerpos.x+4);
		}
		else if (keystate[KEY_INPUT_LEFT]) {
			playerpos.x = max(0,playerpos.x-4);
		}
		if (keystate[KEY_INPUT_UP]) {
			playerpos.y = max(0,playerpos.y-4);
		}else if (keystate[KEY_INPUT_DOWN]) {
			playerpos.y = min(480,playerpos.y+4);
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
			//stopFlag = true;
		}

		int pidx = (frame/4 % 2)*5+3;
		DrawRotaGraph(playerpos.x, playerpos.y, 2.0f, 0.0f, playerH[pidx], true);
		if (isDebugMode) {
			//���@�̖{��(�����蔻��)
			DrawCircle(playerpos.x, playerpos.y, playerRadius, 0xffaaaa, false, 3);
		}

		if (shotPT == SHOTPT_3WAY && !stop)
		{
			for (auto& b : bullets)
			{
				if (b.isActive)
				{
					if (!b.flag)
					{
						if (b.tuijuCnt >= 20)
						{
							float angle = atan2f(playerpos.y - b.pos.y, playerpos.x - b.pos.x);
							b.vel.x = cos(angle) * 4;
							b.vel.y = sin(angle) * 4;
							b.flag = true;
						}
					}
						
				}
			}

			//�e����
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
		else if (shotPT == SHOTPT_HOUSYA && !stop)
		{
			for (int i = 0; i < 360 / 15; i++)
			{
				if (frame % 30 == 0)
				{
					for (auto& b : bullets)
					{
						if (!b.isActive)
						{
							/*b.pos = enemypos;
							float angle = atan2f(playerpos.y - b.pos.y, playerpos.x - b.pos.x);
							b.vel = { 0,0 };
							b.vel.x = cos(angle + ((GetRand(120)-60) * DX_PI / 180)) * 2;
							b.vel.y = sin(angle + ((GetRand(120)-60) * DX_PI / 180)) * 2;
							b.isActive = true;
							break;*/

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
		else if (shotPT == SHOTPT_BARAM &&!stop)
		{
			if (frame % 60 == 0)
			{
				for (int i = 0; i < 10; i++)
				{
					for (auto& b : bullets)
					{
						if (!b.isActive)
						{

							
							b.pos = enemypos;
							float angle = atan2f(playerpos.y - b.pos.y, playerpos.x - b.pos.x);
							b.vel = { 0,0 };
							b.vel.x = cos(angle + ((GetRand(120) - 60) * DX_PI / 180)) * 2;
							b.vel.y = sin(angle + ((GetRand(120) - 60) * DX_PI / 180)) * 2;
							b.isActive = true;
							break;

						}
					}
				}
			}
		}
		else if (shotPT == SHOTPT_JUZI && !stop)
		{
			for (int i = 0; i < 360 / 90; i++)
			{
				if (frame % 7 == 0)
				{
					for (auto& b : bullets)
					{

						if (!b.isActive)
						{

							b.pos = enemypos;

							b.vel = { 0,0 };
							b.vel.x = cos(((90 * i * DX_PI + (5 * juzicnt)) / 180)) * 2;
							b.vel.y = sin(((90 * i * DX_PI + (5 * juzicnt)) / 180)) * 2;
							/*if (frameCnt >= 5)
							{
								juzicnt++;
								b.vel.x = cos((90 * i * DX_PI + (5*juzicnt) / 180)) * 5;
								b.vel.y = sin((90 * i * DX_PI + (5 * juzicnt) / 180)) * 5;

							}*/
							juzicnt++;
							b.isActive = true;
							b.angle = ((90 * i * DX_PI) / 180);
							break;
						}
					}
					for (auto& b : bullets)
					{

						if (!b.isActive)
						{

							b.pos = enemypos;

							b.vel = { 0,0 };
							b.vel.x = cos(((90 * i * DX_PI + (-5 * juzicnt)) / 180)) * 2;
							b.vel.y = sin(((90 * i * DX_PI + (-5 * juzicnt)) / 180)) * 2;
							/*if (frameCnt >= 5)
							{
								juzicnt++;
								b.vel.x = cos((90 * i * DX_PI + (5*juzicnt) / 180)) * 5;
								b.vel.y = sin((90 * i * DX_PI + (5 * juzicnt) / 180)) * 5;

							}*/
							juzicnt++;
							b.isActive = true;
							b.angle = ((90 * i * DX_PI) / 180);
							break;
						}
					}
				}
			}
		}
		else if(shotPT == SHOTPT_TUIJU && !stop)
		{ 
			if (frame % 90 == 0)
			{
				for (int i = 0; i < 360 / 15; i++)
				{
					for (auto& b : bullets)
					{
						if (!b.isActive)
						{
							b.pos = enemypos;
							float angle = atan2f(playerpos.y - b.pos.y, playerpos.x - b.pos.x);
							b.vel = { 0,0 };
							b.tuijuCnt = 0;
							b.vel.x = cos(angle + (15 * i * DX_PI / 180)) * 1.5f;
							b.vel.y = sin(angle + (15 * i * DX_PI / 180)) * 1.5f;
							b.isActive = true;
							break;
						}

					}
				}
			}

			for (auto& b : bullets)
			{
				if (b.isActive)
				{
					if (b.tuijuCnt < 20)
					{
					}
					else if (b.tuijuCnt < 90)
					{
						float angle = atan2f(playerpos.y - b.pos.y, playerpos.x - b.pos.x);
						b.vel.x = cos(angle) * 1;
						b.vel.y = sin(angle) * 1;
					}
					else if (b.tuijuCnt < 100)
					{
						float angle = atan2f(playerpos.y - b.pos.y, playerpos.x - b.pos.x);
						b.vel.x = cos(angle) * 3;
						b.vel.y = sin(angle) * 3;
					}
					b.tuijuCnt++;
				}
				
			}
		}

		

		//�e�̍X�V����ѕ\��
		for (auto& b : bullets) {
			if (!b.isActive) {
				continue;
			}

			
			//�e�̌��ݍ��W�ɒe�̌��ݑ��x�����Z���Ă�������
			if (!stop)
			{
				b.pos += b.vel;
			}
			float angle = atan2f(playerpos.y - b.pos.y,playerpos.x - b.pos.x);
			//�e�̊p�x��atan2�Ōv�Z���Ă��������Bangle�ɒl������񂾂�I�D
			
			DrawRotaGraph(b.pos.x, b.pos.y,0.2f, angle, bulletH, true);
			
			if (isDebugMode) {
				//�e�̖{��(�����蔻��)
				DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
			}
			//�e���E��
			if (b.pos.x + 16 < 0 || b.pos.x - 16 > 640 ||
				b.pos.y + 24 < 0 || b.pos.y - 24 > 480) {
				b.isActive = false;
			}

			//������I
			//����IsHit�͎����������Ă܂���B�����ŏ����Ă��������B
			if (IsHit(b.pos, bulletRadius, playerpos, playerRadius)) {
				//�������������������Ă��������B
				b.isActive = false;
			}
			if (!stop)
			{
				b.pos = b.pos + b.vel;
			}
			
		}

		//�G�̕\��
		enemypos.x = abs((int)((frame + 320) % 1280) - 640);
		int eidx = (frame / 4 % 2);
		DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx],true);

		if (isDebugMode) {
			//�G�̖{��(�����蔻��)
			DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
		}
		++frame;
		ScreenFlip();
	}

	DxLib_End();

	return 0;
}