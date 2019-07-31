#include <math.h>

void MoveAtConstantSpeed(
	float& x, float& y,    // ���@�̍��W�iX�����CY�����j
	float speed,           // ���@�̑���
	bool up, bool down,    // �㉺�����ւ̃X�e�B�b�N����
	bool left, bool right  // ���E�����ւ̃X�e�B�b�N����
) {
	// �΂߂Ɉړ�����Ƃ��̃X�s�[�h�F
	// �㉺���E�̖�0.7�{�ɂ���
	float s=speed/sqrt(2);

	// �΂߈ړ�
	if (up   && left ) x-=s, y-=s; else
	if (up   && right) x+=s, y-=s; else
	if (down && left ) x-=s, y+=s; else
	if (down && right) x+=s, y+=s; else
	
	// �㉺���E�ړ�
	if (up    && !down ) y-=speed; else
	if (down  && !up   ) y+=speed; else
	if (left  && !right) x-=speed; else
	if (right && !left ) x+=speed;
}

