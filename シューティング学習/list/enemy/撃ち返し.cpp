#include <stdlib.h>

bool Destroyed();
void AimingBullet(float ex, float ey, float tx, float ty);
void Delete();

void Revenge(
	float rate,          // �����Ԃ��̊m��
	float ex, float ey,  // �G�̍��W
	float tx, float ty   // �ڕW�i���@�j�̍��W
) {
	// �G���j�󂳂ꂽ���ǂ����̔���F
	// ��̓I�ȏ�����Detroyed�֐��ōs���Ƃ���B
	if (Destroyed()) {
	
		// �����Ԃ��F
		// �������g���Ĉ��m���Ō����Ԃ��B
		// �����Ԃ��e�́u�_�������e�v�Ɠ����B
		// ���˂̋�̓I�ȏ�����AimingBullet�֐��ōs���Ƃ���B
		if (rand()<=rate*RAND_MAX) {
			AimingBullet(ex, ey, tx, ty);
		}
		
		// �G�������F
		// ��̓I�ȏ�����Delete�֐��ōs���Ƃ���B
		Delete();
	}
}

