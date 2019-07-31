void MoveEnemy(int id);
void DeleteEnemy(int id);
void DrawEnemy(float x, float y, float alpha);

// �G�̏�Ԃ�\���萔�F
// �����i�o���O�j�C�o���C�����C����
typedef enum {
	READY, APPEAR, ACT, DISAPPEAR
} STATE_TYPE;

// �o���Ə����ɂ����鎞�ԁC��������
#define TIME 30
#define ACT_TIME 180

// �󒆂Ɍ����G�̏���
void EmergingEnemy(
	int num_enemy,           // �G�̐�
	STATE_TYPE state[],      // �G�̏��
	float ex[], float ey[],  // �G�̍��W
	float alpha[],           // �A���t�@�l
	int timer[]              // �^�C�}�[
) {
	// �S�Ă̓G�Ɋւ��郋�[�v
	for (int i=0; i<num_enemy; i++) {
		
		// ��Ԃɉ����ĕ���
		switch (state[i]) {
			
			// �����i�o���O�j�F
			// �A���t�@�l�ƃ^�C�}�[�����������āC
			// �o����ԂɈڍs����B
			case READY:
				state[i]=APPEAR;
				alpha[i]=0;
				timer[i]=TIME;
				break;
			
			// �o���F
			// �A���t�@�l�����񂾂�傫������B
			// �^�C�}�[��0�ɂȂ����犈����ԂɈڍs����B
			case APPEAR:
				alpha[i]=(float)(TIME-timer[i])/TIME;
				timer[i]--;
				if (timer[i]==0) {
					state[i]=ACT;
					timer[i]=ACT_TIME;
				}
				break;
			
			// �����F
			// �ړ���U�����s���B
			// �^�C�}�[��0�ɂȂ����������ԂɈڍs����B
			// �ړ���U���̋�̓I�ȏ����́C
			// MoveEnemy�֐��ōs���Ƃ���B
			case ACT:
				MoveEnemy(i);
				timer[i]--;
				if (timer[i]==0) {
					state[i]=DISAPPEAR;
					timer[i]=TIME;
				}
				break;
			
			// �����F
			// �A���t�@�l�����񂾂񏬂�������B
			// �^�C�}�[��0�ɂȂ�����G�������B
			// �G��������̓I�ȏ����́C
			// DeleteEnemy�֐��ōs���Ƃ���B
			case DISAPPEAR:
				alpha[i]=(float)timer[i]/TIME;
				timer[i]--;
				if (timer[i]==0) {
					DeleteEnemy(i);
				}
				break;
		}
		
		// �G�̕\���F
		// �A���t�@�l�Ɋ�Â��ăA���t�@�����\�����s���B
		DrawEnemy(ex[i], ey[i], alpha[i]);
	}
}
