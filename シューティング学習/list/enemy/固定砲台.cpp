void MoveFixedBattery(
	int num_enemy,           // �G�i�Œ�C��j�̐�
	float ex[], float ey[],  // �G�i�Œ�C��j�̍��W
	float svx, float svy     // �w�i�̈ړ����x�i�X�N���[�����x�j
) {
	// �S�Ă̌Œ�C���w�i�Ɠ������x�œ�����
	for (int i=0; i<num_enemy; i++) {
		ex[i]+=svx;
		ey[i]+=svy;
	}
}

