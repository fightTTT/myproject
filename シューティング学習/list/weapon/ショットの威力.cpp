void ShotPower(
	float& x, float& y,  // �V���b�g�̍��W
	float vx, float vy,  // �V���b�g�̑��x
	float& power,        // �V���b�g�̈З�
	float attenuation    // �З͂���������x����
) {
	// �V���b�g���ړ�������
	x+=vx; y+=vy;
	
	// �ړ����邽�тɃV���b�g�̈З͂���߂�
	power-=attenuation;
}

