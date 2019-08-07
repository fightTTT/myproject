void DestroyEnemy(int id);
void CreateExplosion(float x, float y);

void InducedExplosion(
	float ex0[], float ey0[],  // �G�̍�����W
	float ex1[], float ey1[],  // �G�̉E�����W
	int num_enemy,             // �G�̐�
	float x0[], float y0[],    // �����̍�����W
	float x1[], float y1[],    // �����̉E�����W
	int num_explosion          // �����̐�
) {
	// �G�Ɣ����̓����蔻�菈���F
	// �S�Ă̓G�Ɣ����Ƃ̊Ԃœ����蔻�菈�����s���C
	// �G�������ɓ���������j�󂷂�B
	// �����ēG�Ɠ������W�ɐV���Ȕ����𐶐�����B
	// �j��Ɛ����̋�̓I�ȏ����́C
	// DestroyEnemy�CCreateExplosion�̊e�֐��ōs���Ƃ���B
	for (int i=0; i<num_enemy; i++) {
		for (int j=0; j<num_explosion; j++) {
			if (ex0[i]<x1[j] && x0[j]<ex1[i] && 
				ey0[i]<y1[j] && y0[j]<ey1[i]) {
				DestroyEnemy(i);
				CreateExplosion(ex0[i], ey0[i]);
			}
		}
	}
}
