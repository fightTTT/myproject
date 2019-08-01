#include <math.h>

void DirectedShot(float x, float y, float dir);

void TurnMarker(
	float& x, float& y,     // ���@�̍��W
	float speed,            // ���@�̑���
	bool left, bool right,  // �X�e�B�b�N�̏�ԁi���E�����j
	bool up, bool down,     // �X�e�B�b�N�̏�ԁi�㉺�����j
	bool turn_button,       // ����{�^���̏��
	bool shot_button        // �V���b�g�{�^���̏��
) {
	static bool turning;        // ���񒆂Ȃ��true
	static float mx, my;        // �^�[���}�[�J�[�̍��W
	static float rad=M_PI*3/2;  // ����p�x�iM_PI�͉~�����j
	static float d=10;          // ���@�ƃ^�[���}�[�J�[�̋���
	
	// ����̊J�n�F
	// �^�[���}�[�J�[�̍��W���Z�o����B
	if (!turning && turn_button) {
		turning=true;
		mx=x-d*cos(rad);
		my=y-d*sin(rad);
	}
	
	// ����̏I��
	if (!turn_button) turning=false;
	
	// ���@�̈ړ�
	if (up   ) y-=speed;
	if (down ) y+=speed;
	if (left ) x-=speed;
	if (right) x+=speed;
	
	// ���񒆂Ȃ�ΐ���p�x���v�Z����
	if (turning) rad=-atan2(x-mx, y-my);
	
	// �V���b�g�̔��ˁF
	// ���@�������Ă�������ɃV���b�g�����B
	// ���˕�����rad�Ƃ͔��Ε����i180��=�΃��W�A�������j�B
	// ���˂̋�̓I�ȏ�����DirectedShot�֐��ōs���Ƃ���B
	if (shot_button) DirectedShot(x, y, rad+M_PI);
}

