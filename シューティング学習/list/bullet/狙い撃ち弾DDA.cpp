void InitAimingBulletDDA(
	int mx, int my,    // ���@�̍��W
	int ex, int ey,    // �G�̍��W
	int& x, int& y,    // �e�̍��W
	int& vx, int& vy,  // �e�̈ړ�����
	int& dx, int& dy,  // X������Y�����̍���
	int& diff          // �덷
) {
	// �e�̍��W��ݒ肷��
	x=ex; y=ey;

	// �e�̈ړ�����(vx,vy)�����߂�F�l��1�܂���-1
	vx=mx>ex?1:-1;
	vy=my>ey?1:-1;

	// �ڕW�ɑ΂���X������Y�����̍����̐�Βl(dx,dy)�����߂�
	dx=mx>=ex?mx-ex:ex-mx;
	dy=my>=ey?my-ey:ey-my;

	// �덷diff�Fdx>=dy�̂Ƃ���dx/2�Cdx<dy�̂Ƃ���dy/2�Ƃ���
	diff=dx>=dy?dx/2:dy/2;
}

void MoveAimingBulletDDA(
	int& x, int& y,  // �e�̍��W
	int vx, int vy,  // �e�̈ړ�����
	int dx, int dy,  // X������Y�����̍���
	int& diff,       // �덷
	int speed        // �e�̑���
) {
	// �ړ�������X�����������Ƃ��̏���
	if (dx>=dy) {
		for (int i=0; i<speed; i++) {

			// X�����ɂ͖���ړ�������
			x+=vx;
			
			// Y�����ɂ͌덷���~�ς����Ƃ������ړ�������
			diff+=dy;
			if (diff>=dx) {
				diff-=dx;
				y+=vy;
			}
		}
	} 

	// �ړ�������Y�����������Ƃ��̏���
	else {
		for (int i=0; i<speed; i++) {

			// Y�����ɂ͖���ړ�������
			y+=vy;

			// X�����ɂ͌덷���~�ς����Ƃ������ړ�������
			diff+=dx;
			if (diff>=dy) {
				diff-=dy;
				x+=vx;
			}
		}
	}
}

