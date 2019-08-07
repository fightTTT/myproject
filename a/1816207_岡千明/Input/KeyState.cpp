#include <DxLib.h>
#include "KeyState.h"
#include <_Debug/_DebugConOut.h>

struct DataHeader {
	int size;				// ���̐�
};

#define _FILE_ID

KeyState::KeyState()
{
	// �e�ʂ̊m��
	_keyCon.reserve(static_cast<size_t>(end(INPUT_ID())));

	// �v�f�̒ǉ�
	//_keyCon.emplace_back(KEY_INPUT_LEFT);
	//_keyCon.emplace_back(KEY_INPUT_RIGHT);
	//_keyCon.emplace_back(KEY_INPUT_UP);
	//_keyCon.emplace_back(KEY_INPUT_DOWN);
	//_keyCon.emplace_back(KEY_INPUT_Z);
	//_keyCon.emplace_back(KEY_INPUT_X);
	//_keyCon.emplace_back(KEY_INPUT_A);
	//_keyCon.emplace_back(KEY_INPUT_S);

	// ���ðĸ׽���ضް�����̏�����
	for (auto data : _oldBuf)
	{
		_oldBuf[data] = 0;
	}

	// ������
	DefKey();

	// ����̨�ޗp�ϐ��̏����l
	confID = begin(INPUT_ID());

	// �֐��߲��������l
	func = &KeyState::RefKeyData;
}

KeyState::~KeyState()
{
}

void KeyState::UpDate(void)
{
	// �����X�V
	SetOld();

	// �ضް�����p
	for (int i = 0; i < sizeof(_buf) / sizeof(_buf[0]); i++)
	{
		_oldBuf[i] = _buf[i];
	}

	// �����擾
	GetHitKeyStateAll(_buf);

	// �ðĈێ�
	(this->*func)();

}

void KeyState::RefKeyData(void)
{
	// ��󷰓o�^
	for (auto id : INPUT_ID())
	{
		state(id, _buf[_keyCon[static_cast<int>(id)]]);
	}

	// �ðĐ؂�ւ�
	if (_buf[KEY_INPUT_F1])
	{
		// 
		confID = begin(INPUT_ID());

		// ����̨��
		func = &KeyState::SetKeyConfig;

		// ���ޯ�۸�
		TRASE("����̨�ފJ�n\n");
	}

	if (_buf[KEY_INPUT_F2] && !_oldBuf[KEY_INPUT_F2])
	{
		// �ۑ������ް��ǂݍ���
		KyeLoad();
	}

	if (_buf[KEY_INPUT_DELETE] && !_oldBuf[KEY_INPUT_DELETE])
	{
		// ��������
		DefKey();
	}
}

void KeyState::SetKeyConfig(void)
{
	// ��U0�ɂ���
	for (auto id : INPUT_ID())
	{
		state(id, 0);
	}

	// �S�̗̂e�ʂ���1�̗e�ʂ������đS�̂̑������o��
	for (int id = 0; id < sizeof(_buf) / sizeof(_buf[0]); id++)
	{
		// �����͂����褑O�̷��Əd�����Ȃ��A
		if (_buf[id] && lastKeyID != id && id != KEY_INPUT_F1 && id != KEY_INPUT_DELETE)
		{
			// ���o�^
			_keyCon[static_cast<size_t>(confID)] = id;

			// �Ō�̷��o�^
			lastKeyID = id;

			// �i�߂�
			++confID;

			// ���ޯ�����޳
			TRASE("%d\n", confID);

			if (confID >= (end(INPUT_ID())))
			{
				// ����̨�ޗp�ϐ��������l�ɂ���
				confID = begin(INPUT_ID());

				// �ް��ۑ�
				KeySave();

				// �ðĐ؂�ւ�
				func = &KeyState::RefKeyData;

				// ���ޯ�����޳
				TRASE("����̨�ޏI��\n");
			}

			break;
		}
	}

	// �ύX������
	if (_buf[KEY_INPUT_DELETE])
	{
		// ������
		confID = begin(INPUT_ID());

		// ���̏�����
		DefKey();

		// �ðĐ؂�ւ�
		func = &KeyState::RefKeyData;

		// ���ޯ�۸�
		TRASE("����̨�ގ�����\n");
	}
}

void KeyState::DefKey(void)
{
	// ��̫�Ă̷��o�^
	_keyCon = {
		KEY_INPUT_LEFT,
		KEY_INPUT_RIGHT,
		KEY_INPUT_UP,
		KEY_INPUT_DOWN,
		KEY_INPUT_Z,
		KEY_INPUT_X,
		KEY_INPUT_A,
		KEY_INPUT_S
	};

	// ���ޯ�۸�
	TRASE("������̫�Ăł�\n");
}

bool KeyState::KeySave(void)
{
	// ̧�ٗp�߲���
	FILE *file = nullptr;

	// ̧�يJ��(��������Ӱ��)
	fopen_s(&file, "data/keydata.dat", "wb");

	// ̧�ق��Ȃ�������false��Ԃ�
	if (&file == nullptr)
	{
		TRASE("���޴�-\n");

		return false;
	}
	else
	{
		// �擪�A���ށA�������݉񐔁A̧�ق������
		fwrite(_keyCon.data(), _keyCon.size() * sizeof(_keyCon[0]), 1, file);

		TRASE("���ނ��܂���\n");
	}

	// ̧�ق����
	fclose(file);

	return true;
}

bool KeyState::KyeLoad(void)
{
	// ̧�ٗp�߲���
	FILE *file = nullptr;

	// ̧�يJ��(�ǂݎ��Ӱ��)
	fopen_s(&file, "data/keydata.dat", "rb");

	// ̧�ق��Ȃ�������false��Ԃ�
	if (&file == nullptr)
	{
		TRASE("۰�޴�-\n");

		return false;
	}
	else
	{
		// �����œǂݍ���
		fread(_keyCon.data(), _keyCon.size() * sizeof(_keyCon[0]), 1, file);

		TRASE("۰�ނ��܂���\n");
	}

	// ̧�ٕ���
	fclose(file);

	return true;
}
