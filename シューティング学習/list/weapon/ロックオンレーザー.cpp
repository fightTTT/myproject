// �G��\���\����
typedef struct {
	bool Locked;  // ���b�N����Ă��邩�ǂ���
	float X, Y;   // ���W
} ENEMY_TYPE;
#define MAX_ENEMIES 100
static ENEMY_TYPE Enemy[MAX_ENEMIES];

bool Hit(float x, float y, ENEMY_TYPE& enemy);
void ShootLockOnLaser(ENEMY_TYPE& enemy);

// ���b�N�I���̎g�p�\��
static int AvailLocks=8;

// ���b�N�I�����[�U�[�̔���
void LockOnLaser(
	float sx, float sy,  // �Ə��̍��W
	bool button          // �{�^���̏�ԁi�����ꂽ�Ƃ�true�j
) {
	// ���b�N�I���̎g�p�\����1�ȏ�̂Ƃ��F
	// �S�Ă̓G�ƏƏ��Ƃ̓����蔻�菈�����s���C
	// �Ə��Əd�Ȃ����G�ɂ̓��b�N�}�[�N��t����B
	// �����蔻��̋�̓I�ȏ�����Hit�֐��ōs���Ƃ���B
	for (int i=0; AvailLocks>0 && i<MAX_ENEMIES; i++) {
		if (!Enemy[i].Locked && Hit(sx, sy, Enemy[i])) {
			Enemy[i].Locked=true;

			// ���b�N�I���̎g�p�\�������炷�F
			// �G�Ƀ��[�U�[������������C�g�p�\���𑝂₷�B
			AvailLocks--;
		}
	}

	// �{�^���������ꂽ�ꍇ�F
	// ���b�N�}�[�N���t�����S�Ă̓G�Ɍ����ă��[�U�[�𔭎˂���B
	// ���˂̋�̓I�ȏ�����ShootLockOnLaser�֐��ōs���Ƃ���B
	if (button) {
		for (int i=0; i<MAX_ENEMIES; i++) {
			if (Enemy[i].Locked) ShootLockOnLaser(Enemy[i]);
		}
	}
}

