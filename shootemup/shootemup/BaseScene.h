#pragma once
#include <memory>

class BaseScene;
class GameCtrl;
using unique_Base = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	virtual ~BaseScene();

	virtual unique_Base UpDate(unique_Base own) = 0;		// 毎ﾌﾚｰﾑ処理するものをまとめた関数、state

private:
	virtual void Init(void) = 0;
};
