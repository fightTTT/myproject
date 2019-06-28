#pragma once
#include <map>

enum class INPUT_ID
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	BTN_1,
	BTN_2,
	BTN_3,
	BTN_4,
	MAX
};

using KeyPair = std::pair<int, int>;
using KeyMap = std::map<INPUT_ID, KeyPair>;

class InputState
{
public:
	InputState();
	virtual ~InputState();

	virtual void Update() = 0;
	const KeyPair state(INPUT_ID key)const;
	const KeyMap& state()const;
	bool state(const INPUT_ID key, const KeyPair pair);
private:
	KeyMap _state;		// ƒL[‚Ì“ü—Íó‘Ô‚ğŠi”[

};
