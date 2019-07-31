void MoveEnemy(int id);
void DeleteEnemy(int id);

void Enemy(
	int num_enemy,             // �G�̐�
	float ex0[], float ey0[],  // �G�̓����蔻��̍�����W
	float ex1[], float ey1[],  // �G�̓����蔻��̉E�����W
	float sx0, float sy0,      // �ړ��\�g�i��ʘg�j�̍�����W
	float sx1, float sy1       // �ړ��\�g�i��ʘg�j�̉E�����W
) {
	for (int i=0; i<num_enemy; i++) {
		
		// �G�̈ړ��F
		// �ړ��̋�̓I�ȏ�����DeleteEnemy�֐��ōs���Ƃ���B
		MoveEnemy(i);
		
		// �G�̏����F
		// �G����ʘg����o�����ǂ����𔻒肵�C
		// �o�Ă���������B
		// �����̋�̓I�ȏ�����DeleteEnemy�֐��ōs���Ƃ���B
		if (ex1[i]<=sx0 || sx1<=ex0[i] || 
			ey1[i]<=sy0 || sy1<=ey0[i]) {
			DeleteEnemy(i);
		}
	}
}

