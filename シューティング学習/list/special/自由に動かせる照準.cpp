// ��ԁi�ʏ�C�Ə��C�U���j
typedef enum {
	NORMAL, SIGHT, ATTACK
} STATE_TYPE;

// ���@�ƏƏ��𓮂���
void MoveSight1(
	float& x, float& y,     // ���@�̍��W
	float& sx, float& sy,   // �Ə��̍��W
	float speed,            // ���@�̈ړ��̑���
	float sight_speed,      // �Ə��̈ړ��̑���
	bool up, bool down,     // �X�e�B�b�N���́i�㉺�j
	bool left, bool right,  // �X�e�B�b�N���́i���E�j
	bool button             // �Ə��{�^������
) {
	static int state=NORMAL;  // ��ԁi�ʏ킩��J�n�j
	static int time;          // �U������
	
	// ��Ԃɉ����ĕ��򂷂�
	switch (state) {
	
		// �ʏ��ԁF
		// ���@���ړ����C
		// �{�^���������ꂽ��Ə����o���āC�Ə���ԂɈڂ�B
		case NORMAL:
			if (up   ) y-=speed;
			if (down ) y+=speed;
			if (left ) x-=speed;
			if (right) x+=speed;
			if (button) {
				state=SIGHT;
				sx=x; sy=y;
			}
			break;
		
		// �Ə���ԁF
		// �Ə����ړ����C�{�^���������ꂽ��U����ԂɈڂ�B
		case SIGHT:
			if (up   ) sy-=sight_speed;
			if (down ) sy+=sight_speed;
			if (left ) sx-=sight_speed;
			if (right) sx+=sight_speed;
			if (!button) {
				state=ATTACK;
				time=100;
			}
			break;
		
		// �U����ԁF
		// ���@���ړ����C��莞�Ԃ��o������ʏ��Ԃɖ߂�B
		case ATTACK:
			if (up   ) y-=speed;
			if (down ) y+=speed;
			if (left ) x-=speed;
			if (right) x+=speed;
			if (time==0) state=NORMAL;
			time--;
			break;
	}
}

