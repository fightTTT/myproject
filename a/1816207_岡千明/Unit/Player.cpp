#include <DxLib.h>
#include "Player.h"
#include <Input/KeyState.h>
#include <Unit/Bullet.h>
#include <Scene/SceneMng.h>
#include <_Debug/_DebugConOut.h>
#include <_Debug/_DebugDispOut.h>
#include <Public/SoundMng.h>

Player::Player()
{
}

Player::Player(Vector2 pos)
{
	// À•W
	_pos.x = pos.x;
	_pos.y = pos.y;

	// ‘å‚«‚³
	_size.x = 30;
	_size.y = 32;

	// ‘¬“x
	_speed = { 5,5 };

	// ÃŞÊŞ¯¸³¨İÄŞ³
	TRASE("%d:%d\n", pos.x, pos.y);

	// ºİÄÛ°×°¸×½§ì
	_input = std::make_unique<KeyState>();

	// ‰Šú‰»ŠÖ”
	Init();
}

Player::Player(Vector2 pos, std::list<std::shared_ptr<Bullet>>& list)
{
	// À•W
	_pos.x = pos.x;
	_pos.y = pos.y;

	// ‘å‚«‚³
	_size.x = 30;
	_size.y = 32;

	// ‘¬“x
	_speed = { 5,5 };

	// ‘Ì—Í
	_hp = 3;
	_oldHp = _hp;

	//// ÃŞÊŞ¯¸³¨İÄŞ³
	//TRASE("%d:%d\n", pos.x, pos.y);

	// ºİÄÛ°×°¸×½¶¬
	_input = std::make_unique<KeyState>();

	// ’e¶¬
	_bullet_vec.reserve(2);
	for (int k = 0; k < 2; k++)
	{
		// 2”­‚Ü‚Åo‚¹‚é‚æ‚¤‚É‚·‚é
		_bullet_vec.emplace_back(std::make_shared<Bullet>(_pos));

		// GameScene‚Ì’e—pØ½Ä‚É‚¢‚ê‚é
		list.emplace_back(_bullet_vec[k]);
	}

	// ‰Šú‰»ŠÖ”
	Init();
}


Player::~Player()
{
}

void Player::Draw(void)
{
	DrawGraph(_pos.x, _pos.y,
		ImageMng::GetInstance().GetID("·¬×")[0],
		true);
}

void Player::UpDate(void)
{
	// €–S‚Íreturn‚Å•Ô‚·
	if (DestroyPlock())
	{
		return;
	}

	// ·°“ü—Í‚Ìó‘ÔXV
	_input->UpDate();

	// ÌßÚ²Ô°‚ÌˆÚ“®(¶‰E‚Ì‚İ)
	int TmpPos = _pos.x;
	// ¶ˆÚ“®
	if (_input->state(INPUT_ID::LEFT).first)
	{
		TmpPos -= _speed.x;
		// ‰æ–ÊŠO‚Éo‚éê‡
		if (_size.x / 2 > TmpPos)
		{
			// •â³
			TmpPos = _size.x / 2;
		}
	}
	// ‰EˆÚ“®
	if (_input->state(INPUT_ID::RIGHT).first)
	{
		TmpPos += _speed.x;
		// ‰æ–ÊŠO‚Éo‚éê‡
		if (TmpPos > lpSceneMng.gameScreenSize.x - (_size.x / 2))
		{
			// •â³
			TmpPos = lpSceneMng.gameScreenSize.x - (_size.x / 2);
		}
	}
	// ‚±‚±‚ÅˆÚ“®
	_pos.x = TmpPos;

	// ’e”­Ë(Z·°)
	if (_input->state(INPUT_ID::BTN_1).first && !(_input->state(INPUT_ID::BTN_1).second))
	{
		for (int k = 0; k < 2; k++)
		{
			// ±¸Ã¨ÌŞ‚Å‚È‚¢’e‚ğ’T‚·
			if (_bullet_vec[k]->actFlg() != true)
			{
				// ’e‚Ìflag‚ğtrue‚É‚µ‚Äo‚·
				_bullet_vec[k]->SetactFlg(_pos);

				// SEÄ¶
				lpSoundMng.SetSound("ÌßÚ²Ô°ÊŞÚ¯Ä");

				break;
			}
		}
	}

	//if ()
	//{

	//}
	// €–S
	else if (_hp <= 0)
	{
		if (_alive)
		{
			// SEÄ¶
			lpSoundMng.SetSound("ÌßÚ²Ô°€–S");
			_alive = false;
		}
		// ”š”­‰æ‘œ‚É·‚µ‘Ö‚¦
		animKey(ANIM::DEATH);
	}
	// ÀŞÒ°¼Ş
	else if (_oldHp > _hp)
	{
		// SE
		lpSoundMng.SetSound("ÀŞÒ°¼Ş");
		_oldHp = _hp;
	}
	// ÃŞÊŞ¯¸—p
	//_DebugDrawBox(_pos.x - _size.x / 2, _pos.y - _size.x / 2, _pos.x + _size.x / 2, _pos.y + _size.x / 2, 0x00fa9a, true);
	//_DebugDrawFormatString(0, 0, 0x00fa9a,"%d:%d", _pos.x, _pos.y);
}

UNIT Player::GetUnitType(void)
{
	return UNIT::PLAYER;
}

bool Player::Init(void)
{
	// ±ÆÒ°¼®İ“o˜^
	AnimVector data;
	data.reserve(2);

	// ·¬×¸À°‰æ‘œ
	data.emplace_back(IMAGE_ID("·¬×")[0], 30);
	data.emplace_back(IMAGE_ID("·¬×")[1], 60);
	// É°ÏÙ‚É“o˜^
	SetAnim(ANIM::NORMAL, data);

	// —Ìˆæ‚ğ•ÏX
	data.reserve(1);
	data.emplace_back(IMAGE_ID("·¬×")[2], 60);
	// EX‚É“o˜^
	SetAnim(ANIM::EX, data);

	// ”š”­—p‚É—Ìˆæ‚ğ•ÏX
	data.reserve(5);
	for (int k = 0; k < 4; k++)
	{
		// ”š”­—p‰æ‘œ“o˜^
		data.emplace_back(IMAGE_ID("PL”š”­")[k], 8 + (k * 8));

		if (k == 3)
		{
			data.emplace_back(-1, 8 + ((k + 1) * 8));
		}
	}
	// ”š”­‚ÍEX‚Éw’è
	SetAnim(ANIM::DEATH, data);

	// SE‚Ì“o˜^
	// ’e
	lpSoundMng.SoundInit("sound/P_Bullet.mp3", "ÌßÚ²Ô°ÊŞÚ¯Ä");
	// ÀŞÒ°¼Ş
	lpSoundMng.SoundInit("sound/Damage.mp3", "ÀŞÒ°¼Ş");
	// €–S
	lpSoundMng.SoundInit("sound/P_Destroy.mp3", "ÌßÚ²Ô°€–S");
	return true;
}
