#include <math.h>

void RotateVelocity(
	float theta,           // ��]�p�x
	float vx0, float vy0,  // ���̑��x
	float& vx, float& vy   // ��]��̑��x
) {
	// theta�����W�A���ɕϊ����Ccos��sin�����߂�F
	// M_PI�͉~�����B
	float rad=M_PI/180*theta;
	float c=cos(rad), s=sin(rad);

	// ���x�x�N�g��(vx0,vy0)����]������(vx,vy)�����߂�
	vx=vx0*c-vy0*s;
	vy=vx0*s+vy0*c;
}

void InitNWayBullets(
	float vx0, float vy0,    // ���S�ƂȂ�e�̑��x
	float theta,             // �e�ƒe�̊Ԃ̊p�x
	int n,                   // �e�̐�
	float vx[], float vy[]   // n-way�e�̑��x
) {
	// �e�ƒe�̊Ԃ̊p�x�����W�A���ɕϊ�����
	float rad_step=M_PI/180*theta;
	
	// �[�̒e�ƒ��S�̒e�Ƃ̊Ԃ̊p�x���v�Z����
	float rad=n%2 ? -n/2*rad_step : (-n/2+0.5)*rad_step;

	// n�̒e�̑��x���v�Z����
	for (int i=0; i<n; i++, rad+=rad_step) {
		
		// (vx[i],vy[i])�����߂�F
		// ���x�x�N�g��(vx0,vy0)��rad������]������B
		float c=cos(rad), s=sin(rad);
		vx[i]=vx0*c-vy0*s;
		vy[i]=vx0*s+vy0*c;
	}
}

