void MoveMyShip(
	float& x, float& y,    // ���@�̍��W�iX�����CY�����j
	float speed,           // ���@�̑���
	bool up, bool down,    // �㉺�����ւ̃X�e�B�b�N����
	bool left, bool right  // ���E�����ւ̃X�e�B�b�N����
) {
	if (up   ) y-=speed;
	if (down ) y+=speed;
	if (left ) x-=speed;
	if (right) x+=speed;
}

