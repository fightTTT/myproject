#pragma once
#include <memory>

enum class SCN_ID
{
	GAME,
	MAX
};

class BaseScene;
using Unique_Base = std::unique_ptr<BaseScene>;
class BaseScene
{
public:
	BaseScene() {};
	virtual ~BaseScene() {};
	virtual Unique_Base UpDate(Unique_Base own) = 0;
	virtual SCN_ID GetScnID(void) = 0;
protected:
	virtual void Init() = 0;
};

