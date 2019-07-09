#include <DxLib.h>
#include <stdio.h>
#include "KeyState.h"
#include "../_DebugConOut.h"

KeyState::KeyState()
{

	// size_t...sizeof���Z�q�ɂ���ĕԂ���镄���Ȃ������^
	_keyCondef.reserve(static_cast<size_t>(end(INPUT_ID())));
	
	_keyCondef.emplace_back(KEY_INPUT_LEFT);
	_keyCondef.emplace_back(KEY_INPUT_RIGHT);
	_keyCondef.emplace_back(KEY_INPUT_UP);
	_keyCondef.emplace_back(KEY_INPUT_DOWN);
	_keyCondef.emplace_back(KEY_INPUT_Z);
	_keyCondef.emplace_back(KEY_INPUT_X);
	_keyCondef.emplace_back(KEY_INPUT_A);
	_keyCondef.emplace_back(KEY_INPUT_S);


	ConfLoad();

	// RefKeyData�̃|�C���^��n�������O��Ԃ��w�肷��K�v������
	func = &KeyState::RefkeyData;

	//begin(INPUT_ID());
	//INPUT_ID num;
	//// �O���Z�̃I�[�o�[���[�h
	//++num;
}

KeyState::~KeyState()
{
}

void KeyState::Update()
{
	SetOld();
	GetHitKeyStateAll(_buf);

	// this->*func��()�����闝�R�Ƃ��ẮA���Ȃ������ꍇ�A�R���p�C������ۂ�this->*func�@()�ł͂Ȃ��A
	// this-> (*func())�Ƃ��Ă݂��邩��
	(this->*func)();		
}

void KeyState::RefkeyData(void)
{
	if (_buf[KEY_INPUT_F1])
	{
		//_keyCon.clear();
		func = &KeyState::SetKeyConfig;
		TRASCE("�L�[�R���t�B�O�J�n\n");
		confID = begin(INPUT_ID());
		//TRASCE("�ݒ�L�[:%d\n",confID);
		return;
	}

	for (auto key : INPUT_ID())
	{
		state(key, _buf[_keyCon[static_cast<int>(key)]]);
	}
}

void KeyState::confSave(void)
{
	FILE *file;
	fopen_s(&file, "data/key.dat", "wb");
	if (file != nullptr)
	{
		// fwrite(�n���f�[�^�̐擪�߲���A���޲Đ��A�������މ񐔁A�������ނׂ�̧�ق̏ꏊ)
		fwrite(_keyCon.data(), _keyCon.size() * sizeof(_keyCon[0]), 1, file);			
		fclose(file);
	}
}

void KeyState::ConfLoad(void)
{
	_keyCon.resize(static_cast<size_t>(end(INPUT_ID())));

	FILE *file;
	fopen_s(&file, "data/key.dat", "rb");
	if (file == nullptr)
	{	
		_keyCon = _keyCondef;
	}
	else
	{
		fread(_keyCon.data(), _keyCon.size() * sizeof(_keyCon[0]), 1, file);
		fclose(file);
	}
}

void KeyState::SetKeyConfig(void)
{
	/*if (CheckHitKeyAll() == 0)
	{
		_keyCon.emplace_back(WaitKey());
	}*/

	for (auto id : INPUT_ID())
	{
		state(id, 0);
	}

	for (int id = 0; id < sizeof(_buf)/ sizeof(_buf[0]); id++)
	{
		if (_buf[id]&& lastKeyID != id 
			&& id != KEY_INPUT_F1 && id != KEY_INPUT_DELETE)
		{
			_keyCon[static_cast<int>(confID)] = id;
			lastKeyID = id;
			++confID;	
			break;
		}
	}

	if (_buf[KEY_INPUT_F3])
	{
		_keyCon = _keyCondef;
		TRASCE("�L�[�R���t�B�O�I��\n");
		func = &KeyState::RefkeyData;
	}

	if (_buf[KEY_INPUT_DELETE])
	{
		ConfLoad();
		TRASCE("�L�[�R���t�B�O�I��\n");
		func = &KeyState::RefkeyData;
	}


	if (confID >= end(INPUT_ID()))
	{
		confSave();
		TRASCE("�L�[�R���t�B�O�I��\n");
		func = &KeyState::RefkeyData;
	}
}
