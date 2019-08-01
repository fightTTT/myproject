void DeleteEnemy(int id);
void DeleteWeapon(int id);

// �G�̃^�C�v��\���萔�F
// �j��ł���C�j��ł��Ȃ��C���킪������Ȃ�
typedef enum {
	BREAKABLE, UNBREAKABLE, TRANSPARENT
} ENEMY_TYPE;

// �j��ł��Ȃ����̂��܂߂��G�̏���
void BreakableEnemy2(
	int num_enemy,             // �G�̐�
	ENEMY_TYPE type[],         // �G�̃^�C�v
	float ex0[], float ey0[],  // �G�̓����蔻��̍�����W
	float ex1[], float ey1[],  // �G�̓����蔻��̉E�����W
	float vit[],               // �G�̑ϋv��
	int num_weapon,            // ����̐�
	float wx0[], float wy0[],  // ����̓����蔻��̍�����W
	float wx1[], float wy1[],  // ����̓����蔻��̉E�����W
	float str[]                // ����̍U����
) {
	// �S�Ă̓G�Ɋւ��郋�[�v
	for (int i=0; i<num_enemy; i++) {
		
		// ����ɓ�����Ȃ��G�̏ꍇ�F
		// �����蔻�菈���͍s�킸�C
		// ���̓G�̏����Ɉڂ�B
		if (type[i]==TRANSPARENT) continue;
		
		// �G�ƕ���Ƃ̓����蔻�菈��
		for (int j=0; j<num_weapon; j++) {
			if (ex0[i]<wx1[j] && wx0[j]<ex1[i] && 
				ey0[i]<wy1[j] && wy0[j]<ey1[i]
			) {
				// �j��ł���G�ɓ��������ꍇ�F
				// ����̍U���͂œG�̑ϋv�͂����C
				// �ϋv�͂�0�܂��͕��ɂȂ�����G��j�󂷂�B
				// �j��̋�̓I�ȏ����́C
				// DeleteEnemy�֐��ōs���Ƃ���B
				if (type[i]==BREAKABLE) {
					vit[i]-=str[j];
					if (vit[i]<=0) DeleteEnemy(i);
				}
				
				// �G�ɓ�����������͏����F
				// ��̓I�ȏ�����DeleteWeapon�֐��ōs���Ƃ���B
				DeleteWeapon(j);
			}
		}
	}
}


