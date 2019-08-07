void DeleteEnemy(int id);
void CreateExplosion(float x, float y);

// �A�[���̏�ԁF
// �ҋ@�C�L�тĂ���r���C�L�т������C�k��ł���r���B
typedef enum {
	READY, EXTENDING, EXTENDED, SHRINKING
} STATE_TYPE;

// �A�[���̓���
void MoveArm(
	bool button  // �A�[����L�΂��{�^���̏��
) {
	static STATE_TYPE state=READY;  // �A�[���̏��
	static int length;              // �A�[���̒���
	static int max_length=20;       // �A�[���̍ő咷
	static int time;                // ���ԑ҂��p
	
	// �A�[���̏�Ԃɂ���ď�����ς���
	switch (state) {
		
		// �ҋ@�F
		// �{�^���������ꂽ��A�[����L�΂��B
		case READY:
			if (button) {
				state=EXTENDING;
				length=0;
			}
			break;
		
		// �L�тĂ���r���F
		// �A�[����L�΂��C
		// �ő咷�ɒB������L�т�������ԂɈڂ�B
		case EXTENDING:
			if (length<max_length) {
				length++;
			} else {
				state=EXTENDED;
				time=10;
			}
			break;
		
		// �L�т������F
		// ��莞�Ԃ��o�߂�����k�܂���B
		case EXTENDED:
			if (time>0) {
				time--;
			} else {
				state=SHRINKING;
			}
			break;
		
		// �k��ł���r���F
		// ������0�ɂȂ�����ҋ@��Ԃɖ߂�B
		case SHRINKING:
			if (length>0) {
				length--;
			} else {
				state=READY;
			}
			break;
	}
}

void MoveThrownEnemy(
	float& x0, float& y0,      // ��������ꂽ�G�̍�����W
	float& x1, float& y1,      // ��������ꂽ�G�̉E�����W
	float vx, float vy,        // ��������ꂽ�G�̑��x
	float ex0[], float ey0[],  // ���̓G�̍�����W
	float ex1[], float ey1[],  // ���̓G�̉E�����W
	int num_enemy              // ���̓G�̐�
) {
	// �G�Ƃ̓����蔻�菈���F
	// ��������ꂽ�G�ƁC���̑S�Ă̓G�Ƃ̊Ԃ�
	// �����蔻�菈�����s���B
	// �Փ˂�����C��������ꂽ�G�������C
	// ����ɔ������o���B
	// ���łƏo���̋�̓I�ȏ����́C
	// DeleteEnemy�CCreateExplosion�̊e�֐��ōs���Ƃ���B
	int i;
	for (i=0; i<num_enemy; i++) {
		if (ex0[i]<x1 && x0<ex1[i] && 
			ey0[i]<y1 && y0<ey1[i]) {
			DeleteEnemy(i);
			CreateExplosion(x0, y0);
		}
	}
	
	// �ǂ̓G�ɂ��Ԃ���Ȃ������ꍇ�F
	// ��������ꂽ�G�𓮂����B
	if (i==num_enemy) {
		x0+=vx; y0+=vy;
		x1+=vx; y1+=vy;
	}
}


