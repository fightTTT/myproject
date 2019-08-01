void DeleteEnemy(int id);
void DeleteWeapon(int id);

void BreakableEnemy(
	int num_enemy,             // �G�̐�
	float ex0[], float ey0[],  // �G�̓����蔻��̍�����W
	float ex1[], float ey1[],  // �G�̓����蔻��̉E�����W
	float vit[],               // �G�̑ϋv��
	int num_weapon,            // ����̐�
	float wx0[], float wy0[],  // ����̓����蔻��̍�����W
	float wx1[], float wy1[],  // ����̓����蔻��̉E�����W
	float str[]                // ����̍U����
) {
	// �G�ƕ���̓����蔻�菈���F
	// �S�Ă̓G�ƕ���̑g�ݍ��킹�ɂ��āC
	// ���킪�G�ɓ����������ǂ����𔻒肷��
	for (int i=0; i<num_enemy; i++) {
		for (int j=0; j<num_weapon; j++) {
			if (ex0[i]<wx1[j] && wx0[j]<ex1[i] && 
				ey0[i]<wy1[j] && wy0[j]<ey1[i]
			) {
				// ���������ꍇ�F
				// ����̍U���͂œG�̑ϋv�͂����C
				// �ϋv�͂�0�܂��͕��ɂȂ�����G��j�󂷂�B
				// �j��̋�̓I�ȏ����́C
				// DeleteEnemy�֐��ōs���Ƃ���B
				vit[i]-=str[j];
				if (vit[i]<=0) DeleteEnemy(i);
				
				// �G�ɓ�����������͏����F
				// ��̓I�ȏ�����DeleteWeapon�֐��ōs���Ƃ���B
				DeleteWeapon(j);
			}
		}
	}
}

