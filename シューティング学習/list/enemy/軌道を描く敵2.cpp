void DeleteEnemy(int id);

void DeleteEnemy(int id);

void OrbitalFlight(
	int num_enemy,           // �G�̐�
	float ex[], float ey[],  // �G�̍��W
	int index[],             // �O���f�[�^���w���C���f�b�N�X
	int num_orbit,           // �O���f�[�^�̗v�f��
	float ox[], float oy[]   // �O���f�[�^�i���W�j
) {
	for (int i=0; i<num_enemy; i++) {
		
		// �G���W�̍X�V�F
		// �O���f�[�^��ǂݏo���āC�G�̐V�������W�Ƃ���B
		ex[i]=ox[index[i]];
		ey[i]=oy[index[i]];
		
		// �C���f�b�N�X�i�f�[�^�̓ǂݏo���ʒu�j��i�߂�F
		// �O���f�[�^�̍Ō�ɒB������G�������B
		// �G��������̓I�ȏ�����DeleteEnemy�֐��ōs���Ƃ���B
		// 
		index[i]++;
		if (index[i]==num_orbit) DeleteEnemy(i);
	}
}


