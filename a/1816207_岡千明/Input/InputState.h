#pragma once
#include <map>
#include <vector>
#include "InputId.h"

// using宣言
using KeyPair = std::pair<int, int>;			// pair
using KeyMap = std::map<INPUT_ID, KeyPair>;	// map

class InputState
{
public:
	InputState();
	virtual ~InputState();

	virtual void UpDate(void) = 0;						// ｷｰ情報更新用

	const KeyMap& state(void)const;						// 引数なしｹﾞｯﾀｰ
	const KeyPair state(const INPUT_ID id)const;		// 引数ありｹﾞｯﾀｰ

	// いらないかも
	bool state(const INPUT_ID id, const KeyPair pair);	// ｾｯﾀｰ	1ﾌﾚ前の情報

	bool state(const INPUT_ID id, const int data);		// ｾｯﾀｰ	1ﾌﾚ前の情報
	void SetOld(void);

private:
	KeyMap _state;		// [どのｷｰが押されたか].first(現在)	.second(1ﾌﾚ前)


};

// pair.first = 新しい　pair.second = 1ﾌﾚ前
