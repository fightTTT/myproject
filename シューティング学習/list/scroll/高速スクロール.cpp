void ScrollForce(
	int& x, int& y,   // ���@�̍��W
	int vx, int vy,   // ���@�̑��x
	int svx, int svy  // �X�N���[���̑��x
) {
	x+=vx+svx/2;
	y+=vy+svy/2;
}

