void Shot(bool color);
bool HitBullet(int id);
void DeleteBullet(int id);
void Miss();

void SwitchColors(
	bool color_button,   // �F�؂�ւ��{�^���̏��
	bool shot_button,    // �V���b�g�{�^���̏��
	int num_bullet,      // �e�̐�
	bool bullet_color[]  // �e�̐F
) {
	static bool prev_col_button=false;  // �O��̃{�^���̏��
	static bool color=true;             // ���@�̐F
	static int energy=0;                // �G�l���M�[
	
	// �F��؂�ւ���
	if (!prev_col_button && color_button) color=~color;
	prev_col_button=color_button;
	
	// �V���b�g�����F
	// ���@�Ɠ����F�̃V���b�g�����B
	// �V���b�g�̋�̓I�ȏ�����Shot�֐��ōs���Ƃ���B
	if (shot_button) Shot(color);
	
	// �e�Ƃ̓����蔻�菈���F
	// ����̋�̓I�ȏ�����HitBullet�֐��ōs���Ƃ���B
	for (int i=0; i<num_bullet; i++) {
		if (HitBullet(i)) {
			
			// �����F�Ȃ�΋z���F
			// �e�������C�G�l���M�[�𑝂₷�B
			// �����̋�̓I�ȏ�����DeleteBullet�֐��ōs���Ƃ���B
			if (color==bullet_color[i]) {
				DeleteBullet(i);
				energy++;
			}
			
			// �قȂ�F�Ȃ�΃~�X�F
			// �~�X�̋�̓I�ȏ�����Miss�֐��ōs���Ƃ���B
			else {
				Miss();
			}
		}
	}
}

