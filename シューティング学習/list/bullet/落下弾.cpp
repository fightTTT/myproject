void MoveDroppingBullet(
	float& x, float& y,   // �e�̍��W
	float accel,          // �����x
	float& vx, float& vy  // ���x��X������Y����
) {
	// ���x���X�V����F
	// X�����͕ω��������CY����������ω�������B
	vy+=accel;

	// ���W���X�V����
	x+=vx; y+=vy;
}
