#pragma once
#include <memory>

class BaseScene;
class GameCtrl;

using unique_Base = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	virtual ~BaseScene();		// ���z�f�X�g���N�^

	virtual unique_Base UpDate(GameCtrl &controller) = 0;

private:
	virtual void Init() = 0;
};

