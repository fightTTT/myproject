void DamageEnemy(int id);
void DrawPunch();

// �ߐڍU���Ɋւ��鏈��
void Punch(
	bool button,               // �{�^���̏�ԁi�������Ƃ�true�j
	float px0, float py0,      // �ߐڍU���̍�����W
	float px1, float py1,      // �ߐڍU���̉E�����W
	float ex0[], float ey0[],  // �G�̍�����W
	float ex1[], float ey1[],  // �G�̉E�����W
	int num_enemy              // �G�̐�
) {
	static bool punching=false;  // �ߐڍU�������ǂ���
	static int punch_time;       // �ߐڍU�����o���Ă��鎞��
	
	// �ߐڍU���̊J�n�F
	// �ߐڍU�����ł͂Ȃ��C�{�^����������Ă�����C
	// �ߐڍU�����o���B
	if (!punching && button) {
		punching=true;
		punch_time=30;
	}
	
	// �ߐڍU�����̏���
	if (punching) {

		// �G�Ƃ̓����蔻�菈���F
		// �_���[�W��^�����̓I�ȏ����́C
		// DamageEnemy�֐��ōs���Ƃ���B
		for (int i=0; i<num_enemy; i++) {
			if (ex0[i]<px1 && px0<ex1[i] && 
				ey0[i]<py1 && py0<ey1[i]) {
				DamageEnemy(i);
			}
		}

		// �ߐڍU���̕\���F
		// �\���̋�̓I�ȏ�����DrawPunch�֐��ōs���Ƃ���B
		DrawPunch();

		// �ߐڍU���̎����ƏI���F
		// �������Ԃ��߂�����ߐڍU�����������߂�B
		if (punch_time==0) punching=false; else punch_time--;
	}
}

