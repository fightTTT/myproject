#pragma once
#include <memory>

class BaseScene;
class GameCtrl;
using unique_Base = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	virtual ~BaseScene();

	virtual unique_Base UpDate(unique_Base own) = 0;		// –ˆÌÚ°Ñˆ—‚·‚é‚à‚Ì‚ğ‚Ü‚Æ‚ß‚½ŠÖ”Astate

private:
	virtual void Init(void) = 0;
};
