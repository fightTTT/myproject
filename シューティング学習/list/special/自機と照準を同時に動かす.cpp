#include <math.h>

void Shot(float x, float y, float vx, float vy);

void MoveSight2(
	float& x, float& y,       // ���@�̍��W
	float speed,              // ���@�̑���
	bool up1, bool down1,     // ���@�p�X�e�B�b�N����1�i�㉺�j
	bool left1, bool right1,  // ���@�p�X�e�B�b�N����1�i���E�j
	float& sx, float& sy,     // �Ə��̍��W
	float sight_speed,        // �Ə��̑���
	bool up2, bool down2,     // �Ə��p�X�e�B�b�N����2�i�㉺�j
	bool left2, bool right2,  // �Ə��p�X�e�B�b�N����2�i���E�j
	bool button,              // �V���b�g�{�^���̓���
	float shot_speed          // �V���b�g�̑���
) {
	// ���@�𓮂���
	if (up1   ) y-=speed;
	if (down1 ) y+=speed;
	if (left1 ) x-=speed;
	if (right1) x+=speed;

	// �Ə��𓮂���
	if (up2   ) sy-=sight_speed;
	if (down2 ) sy+=sight_speed;
	if (left2 ) sx-=sight_speed;
	if (right2) sx+=sight_speed;

	// �V���b�g�����F
	// �V���b�g�{�^���������ꂽ��C
	// ���@����Ə��Ɍ������ăV���b�g�����B
	// ���˂̋�̓I�ȏ�����Shot�֐��ōs���Ƃ���B
	if (button) {
		float vx=sx-x, vy=sy-y;
		if (vx!=0 || vy!=0) {
			float d=sqrt(vx*vx+vy*vy);
			vx*=shot_speed/d;
			vy*=shot_speed/d;
			Shot(x, y, vx, vy);
		}
	}
}

