#pragma once
#include <memory>
#include "Obj.h"
#include "../Input/InputState.h"


class Player :
	public Obj
{
public:
	Player();
	Player(const Vector2Dbl& pos, const Vector2Dbl& size);
	~Player();
	void Draw(void) override;
	UNIT GetUnit(void) override;
	void SetMove(void);
	std::vector<Shared_Obj> GetShotData();
private:
	bool Init(void);
	bool Shooting(void);
	std::unique_ptr<InputState> inputState;		// “ü—Íó‘Ôæ“¾
	std::vector<Shared_Obj> _shotObj;
};

