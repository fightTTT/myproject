void MoveAcceleratedBullet(
	float speed,          // �e�̑���
	float accel,          // �����x
	float& vx, float& vy  // ���x��X������Y����
) {
	// ���x���Â������Ŋ���
	if (speed!=0) {
		vx/=speed; vy/=speed;
	}

	// �������X�V����
	speed+=accel;

	// ���x�ɐV�����������|����
	vx*=speed; vy*=speed;
}

