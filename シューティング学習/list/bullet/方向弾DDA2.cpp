#include <math.h>

// ���@�̈ʒu���i�[����e�[�u��
int mpos[360][2];

// �e�[�u�������F
// M_PI�͉~�����B
void MakeTable() {
	for (int i=0; i<360; i++) {
		mpos[i][0]=cos(M_PI/180*i)*1000;
		mpos[i][1]=sin(M_PI/180*i)*1000;
	}
}

void InitDirectedBulletDDA2(
	int theta,         // ���ˊp�x
	int ex, int ey,    // �G�̍��W
	int& x, int& y,    // �e�̍��W
	int& vx, int& vy,  // �e�̈ړ�����
	int& dx, int& dy,  // X������Y�����̍���
	int& diff          // �덷
) {
	// ���z�I�Ȏ��@�̈ʒu���e�[�u������ǂݏo��
	int dir=(theta%360+360)%360;
	int mx=mpos[dir][0];
	int my=mpos[dir][1];

	// ���Ƃ�DDA���g���Ď��@�̕����ɒe���΂������Ɠ���

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

