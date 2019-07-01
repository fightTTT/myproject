#pragma once
#include <map>
#include "../INPUT_ID.h"


using KeyPair = std::pair<int, int>;	// first...���݂̓��͏��	second...1�t���[���O�̓��͏��
using KeyMap = std::map<INPUT_ID, KeyPair>;

class InputState
{
public:
	InputState();
	virtual ~InputState();

	virtual void Update() = 0;
	const KeyPair state(INPUT_ID key)const;
	const KeyMap& state()const;
	bool state(const INPUT_ID key, const int pair);

	// �g���K�[�����֐�
	void SetOld(void);
private:
	KeyMap _state;		// �L�[�̓��͏�Ԃ��i�[

};
