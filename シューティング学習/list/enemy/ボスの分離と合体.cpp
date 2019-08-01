// �{�X��\���\����
#define MAX_PART 32
typedef struct BOSS_STRUCT {
	float X, Y;          // �{�X�̍��W
	struct BOSS_STRUCT* 
		Part[MAX_PART];  // �{�X���\������p�[�c�i�{�X�j
	int NumPart;         // �p�[�c�̐�
	float PX[MAX_PART], 
		PY[MAX_PART];    // �p�[�c�̑��΍��W
} BOSS;

void MoveBoss(BOSS* boss);

// �������̓����F
// �e�p�[�c��Ɨ��ɓ������B
// �ړ��̋�̓I�ȏ�����MoveBoss�֐��ōs���Ƃ���B
void MoveSeparatedBoss(BOSS* boss) {
	for (int i=0; i<boss->NumPart; i++) {
		MoveBoss(boss->Part[i]);
	}
}

// ���̒��̓����F
// �S�p�[�c����̉����ē����悤�ɁC
// ���S�ƂȂ���W�ɑ΂��ČŒ�̈ʒu�Ƀp�[�c��z�u����B
// �ړ��̋�̓I�ȏ�����MoveBoss�֐��ōs���Ƃ���B
void MoveUnitedBoss(BOSS* boss) {
	MoveBoss(boss);
	for (int i=0; i<boss->NumPart; i++) {
		boss->Part[i]->X=boss->X+boss->PX[i];
		boss->Part[i]->Y=boss->Y+boss->PY[i];
	}
}

