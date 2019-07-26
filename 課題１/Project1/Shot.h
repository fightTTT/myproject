#pragma once
#include "unit/Obj.h"

class Shot :
	public Obj
{
public:
	Shot();
	Shot(Vector2Dbl pos);
	~Shot();
	void SetMove(void);
	UNIT GetUnit(void);

};
