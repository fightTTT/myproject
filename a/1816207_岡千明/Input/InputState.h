#pragma once
#include <map>
#include <vector>
#include "InputId.h"

// using�錾
using KeyPair = std::pair<int, int>;			// pair
using KeyMap = std::map<INPUT_ID, KeyPair>;	// map

class InputState
{
public:
	InputState();
	virtual ~InputState();

	virtual void UpDate(void) = 0;						// �����X�V�p

	const KeyMap& state(void)const;						// �����Ȃ��ޯ��
	const KeyPair state(const INPUT_ID id)const;		// ��������ޯ��

	// ����Ȃ�����
	bool state(const INPUT_ID id, const KeyPair pair);	// ����	1�ڑO�̏��

	bool state(const INPUT_ID id, const int data);		// ����	1�ڑO�̏��
	void SetOld(void);

private:
	KeyMap _state;		// [�ǂ̷��������ꂽ��].first(����)	.second(1�ڑO)


};

// pair.first = �V�����@pair.second = 1�ڑO
