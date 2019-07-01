#pragma once
#include "BaseScene.h"
#include "../unit/Obj.h"
#include <list>
class GameScene :
	public BaseScene
{
public:
	GameScene();
	~GameScene();
	Unique_Base UpDate(Unique_Base own) override;
	SCN_ID GetScnID(void) override;		// ©g‚ÌƒV[ƒ“‚Ìí—Ş‚ğ•Ô‚·
protected:
	void Init(void)override;
private:
	std::list<Shared_Obj> _objList;
};

