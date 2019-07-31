void Draw(int x, int y);

void InitAimingBulletFP(
	int mx, int my,    // ���@�̍��W
	int ex, int ey,    // �G�̍��W
	int& x, int& y,    // �e�̍��W
	int& vx, int& vy,  // �e�̑��x
	int speed          // �e�̑���
) {
	// �e�̍��W��ݒ肷��
	x=ex; y=ey;

	// �ڕW�ɑ΂���X������Y�����̍����̐�Βl(dx,dy)�����߂�
	int dx=mx>=ex?mx-ex:ex-mx;
	int dy=my>=ey?my-ey:ey-my;

	// X������Y�����̍����̂���������������d�Ƃ���
	int d=dx>=dy?dx:dy;

	// ���x(vx,vy)�����߂�
	vx=(mx-ex)*speed/d;
	vy=(my-ey)*speed/d;
}

void MoveAimingBulletFP(
	int& x, int& y,  // �e�̍��W
	int vx, int vy   // �e�̑��x
) {
	// �e�̍��W(x,y)�ɑ��x(vx,vy)��������
	x+=vx;
	y+=vy;

	// �e��`���F
	// ��ʂɒe��`���Ƃ��ɂ͍��W��(x>>8, y>>8)�Ƃ���B
	// �e��`����̓I�ȏ�����Draw�֐��ōs���Ƃ���B
	Draw(x>>8, y>>8);
}

