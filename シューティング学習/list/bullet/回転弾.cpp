#include <math.h>

void MoveLoopingBullet(
	float& x, float& y,    // �e�̍��W
	float& vx, float& vy,  // �e�̑��x
	float cx, float cy,    // ��]���S�̍��W
	float r,               // ���a
	float theta,           // �p�x�i���W�A���j
	float omega            // 1��̈ړ��ŕω�����p�x�i���W�A���j
) {
	// �p�x��ω�������
	theta+=omega;

	// �ʒu���v�Z����
	x=cx+r*cos(theta);
	y=cy+r*sin(theta);

	// �e�̑��x�i�K�v�ȏꍇ�����j
	vx=-r*omega*sin(theta);
	vy= r*omega*cos(theta);
}

void MoveLoopingBullet2(
	float& x, float& y,    // �e�̍��W
	float& vx, float& vy,  // �e�̑��x
	float cx, float cy,    // ��]���S�̍��W
	float& r,              // ���a
	float vr,              // ���a�̕ω�
	float theta,           // �p�x�i���W�A���j
	float omega            // 1��̈ړ��ŕω�����p�x�i���W�A���j
) {
	// �p�x��ω�������
	theta+=omega;
	
	// ���a��ω�������
	r+=vr;

	// �ʒu���v�Z����
	x=cx+r*cos(theta);
	y=cy+r*sin(theta);

	// �e�̑��x�i�K�v�ȏꍇ�����j
	vx=-r*omega*sin(theta);
	vy= r*omega*cos(theta);
}

