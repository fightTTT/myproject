// �G��\���\����
typedef struct {
	float X, Y;  // �G�̍��W
} ENEMY;

// �{�X�i���G�ȍ\���̓G�j��\���\����
#define MAX_PART 32
typedef struct {
	float X, Y;             // �{�X�̍��W
	ENEMY* Part[MAX_PART];  // �{�X���\������p�[�c�i�G�j
	int NumPart;            // �p�[�c�i�G�j�̐�
	bool Fatal[MAX_PART];   // �v���I�ȃp�[�c���ǂ���
} COMPLEX_ENEMY;

void MoveEnemy(ENEMY* enemy);
void DrawEnemy(ENEMY* enemy, float x, float y);
bool Destroyed(ENEMY* enemy);
void DeleteEnemy(ENEMY* enemy);
void DeleteEnemy(COMPLEX_ENEMY* enemy);

// �{�X�̓����F
// �{�X���\������S�Ă̓G�ɂ��ď��ɏ������s���B
void MoveComplexEnemy(COMPLEX_ENEMY* ce) {
	for (int i=0; i<ce->NumPart; i++) {

		// �G�̍s���F
		// ��̓I�ȏ�����MoveEnemy�֐��ōs���Ƃ���B
		MoveEnemy(ce->Part[i]);

		// �G�̕`��F
		// �S�Ẵp�[�c����̉������ē��������߂ɁC
		// �p�[�c�̍��W���{�X���W����̑��Έʒu�Ƃ��Ďg���B
		// �{�X�S�̂𓮂����ɂ�ce->X��ce->Y��ύX����B
		// ��̓I�ȏ�����DrawEnemy�֐��ōs���Ƃ���B
		DrawEnemy(ce->Part[i],
			ce->Part[i]->X+ce->X, ce->Part[i]->Y+ce->Y);

		// �G�̔j��F
		// ����Ɣj��̋�̓I�ȏ����́C
		// Destroyed�CDeleteEnemy�̊e�֐��ōs���Ƃ���B
		if (Destroyed(ce->Part[i])) {
			DeleteEnemy(ce->Part[i]);

			// �{�X�S�̂̔j��F
			// �j�󂳂ꂽ�p�[�c���v���I�������Ƃ��ɂ́C
			// �{�X�S�̂�j�󂷂�B
			if (ce->Fatal[i]) DeleteEnemy(ce);
		}
	}
}

