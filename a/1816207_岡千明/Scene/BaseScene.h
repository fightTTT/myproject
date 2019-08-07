#pragma once
#include <memory>

// ¼°İ—pID
// ¸×½–¼‚Å‰½‚©‚í‚©‚é‚æ‚¤‚É‚µ•Ï”–¼‚Í’Z‚ß‚É‚·‚é
enum class SCN_ID
{
	TITLE,	// 
	GAME,	// ¹Ş°Ñ¼°İ
	MAX
};

// ÌßÛÄÀ²ÌßéŒ¾
class BaseScene;

// usingéŒ¾
using shared_Base = std::shared_ptr<BaseScene>;			// ¼ª±°ÄŞÎß²İÀ°

class BaseScene
{
public:
	BaseScene() {};
	virtual ~BaseScene() {};

	virtual shared_Base UpDate(shared_Base own) = 0;	// ó‘Ô‘JˆÚ
	virtual SCN_ID GetScnID(void) = 0;					// ©•ª‚Ì¼°İ‚ÌID‚ğ•Ô‚·(ƒˆ‰¼‘zŠÖ”)
};

