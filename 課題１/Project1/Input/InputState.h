#pragma once
#include <map>
#include "../INPUT_ID.h"


using KeyPair = std::pair<int, int>;	// first...現在の入力状態	second...1フレーム前の入力状態
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

	// トリガー処理関数
	void SetOld(void);
private:
	KeyMap _state;		// キーの入力状態を格納

};
