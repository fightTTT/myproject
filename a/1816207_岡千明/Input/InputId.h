#pragma once

// �����͗penum
enum class INPUT_ID
{
	LEFT,	// ��
	RIGHT,	// �E
	UP,		// ��
	DOWN,	// ��
	BTN_1,	// ����1
	BTN_2,	// ����2
	BTN_3,	// ����3
	BTN_4,	// ����4
	MAX
};

// for���p���ڰ���̵��ް۰��
INPUT_ID begin(INPUT_ID);
INPUT_ID end(INPUT_ID);
INPUT_ID operator++(INPUT_ID& key);
INPUT_ID operator* (INPUT_ID& key);

// enum��enumclass�̈Ⴂ
// enum�͈ÖٓI��int
// enumclass�͌^��ς����,int�ȊO�ɂ��ł���