void MoveMyShip2(
	float& x, float& y,    // ���@�̍��W�iX�����CY�����j
	float speed,           // ���@�̑���
	float x0, float y0,    // ���@�̍�����W
	float x1, float y1,    // ���@�̉E�����W
	float sx0, float sy0,  // �ړ��\�g�̍�����W
	float sx1, float sy1,  // �ړ��\�g�̉E�����W
	bool up, bool down,    // �㉺�����ւ̃X�e�B�b�N����
	bool left, bool right  // ���E�����ւ̃X�e�B�b�N����
) {
	if (up    && sy0<=y0) y-=speed;
	if (down  && y1<=sy1) y+=speed;
	if (left  && sx0<=x0) x-=speed;
	if (right && x1<=sx1) x+=speed;
}

