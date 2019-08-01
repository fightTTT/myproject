#include <stdio.h>

// ���[�U�[�̊e������\���\����
typedef struct LASER_STRUCT {
	float X, Y;                 // ���W
	float VX, VY;               // ���x
	float OldX, OldY;           // �Â����W
	float Angle;                // ��]�p�x
	float OldAngle;             // �Â���]�p�x
	struct LASER_STRUCT* Prec;  // 1�O�̕����ւ̃|�C���^
	                            // �i�擪�����̏ꍇ�ɂ�NULL�j
} LASER_TYPE;

void MoveHoming(LASER_TYPE* laser);
LASER_TYPE* NewLaserType();

// ���[�U�[�𓮂����֐�
void MoveHomingLaser(
	LASER_TYPE* laser  // ���[�U�[�̐擪�����܂��͔���1����
) {
	// ��[�����̏ꍇ�F
	// �U���e�̓����Ɠ����B
	// �U���̋�̓I�ȏ�����MoveHoming�֐��ōs���Ƃ���B
	if (laser->Prec==NULL) {
		MoveHoming(laser);
	}

	// ��[�����ȊO�̏ꍇ�F
	// 1�O�̕�����ǂ�������B
	// �Â����W�ƌÂ���]�p�x���R�s�[����B
	else {
		laser->X=laser->Prec->OldX;
		laser->Y=laser->Prec->OldY;
		laser->Angle=laser->Prec->OldAngle;
	}
}

// ���[�U�[�̔���
void ShootHomingLaser(
	float x, float y,   // ���˒n�_�̍��W
	int length          // ���[�U�[�̒���
) {
	LASER_TYPE* laser;      // ���[�U�[��\���\���̂ւ̃|�C���^
	LASER_TYPE* prec=NULL;  // 1�O�̕������w���|�C���^
	
	// ���[�U�[�̊e���������F
	// ���[�U�[�̍\���̂��m�ۂ��C���W������������B
	// �\���̊m�ۂ̋�̓I�ȏ�����NewLaserType�֐��ōs���Ƃ���B
	for (int i=0; i<length; i++, prec=laser) {
		laser=NewLaserType();
		laser->X=laser->OldX=x;
		laser->Y=laser->OldY=y;
		laser->Angle=laser->OldAngle=0;

		// ���̕�����1�O�̕������Q�Ƃ���悤�ɂ��C
		// ��[�����ɂ�NULL���Q�Ƃ�����B
		laser->Prec=prec;
	}
}

