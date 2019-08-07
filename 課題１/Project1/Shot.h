#pragma once
#include "unit/Obj.h"

class Shot :
	public Obj
{
public:
	Shot();
	Shot(Vector2Dbl& pos);
	~Shot();
	void SetMove(void);
	UNIT GetUnit(void) override;
	std::vector<Shared_Obj> GetShotData() override;

private:
	void Init(void);

};
