#include <DxLib.h>
#include "KeyState.h"


KeyState::KeyState()
{
}

KeyState::~KeyState()
{
}

void KeyState::Update()
{
	GetHitKeyStateAll(_buf);
}

void KeyState::GetState()
{

}