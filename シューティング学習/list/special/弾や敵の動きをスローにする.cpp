void MoveEnemy();
void MoveBullet();

void Slowing(
	int& gauge,  // �X���[��Ԃɂ��邽�߂ɕK�v�ȃQ�[�W
	bool button  // �X���[�{�^���������Ă��邩�ǂ���
) {
	// �^�C�}�[�F
	// �X���[��Ԃ̂Ƃ��ɍs���񐔂𒲐����邽�߂Ɏg���B
	static int time=1;

	// �G�ƒe�𓮂����F
	// �ʏ��Ԃ̂Ƃ��ɂ͖��񓮂����C
	// �X���[��Ԃ̂Ƃ��ɂ�2���1�񂾂��������B
	// �ړ��̋�̓I�ȏ����́C
	// MoveEnemy�CMoveBullet�̊e�֐��ōs���Ƃ���B
	if (!button || (gauge>0 && time==0)) {
		MoveEnemy();
		MoveBullet();
	}
	
	// �y�i���e�B�F
	// �Q�[�W��0�Ȃ̂ɃX���[�{�^���������Ă�����C
	// �y�i���e�B�Ƃ��Ēe������1�x�������B
	// ���ʂƂ��āC�e�͒ʏ��2�{�̑��x�œ����B
	if (button && gauge==0) {
		MoveBullet();
	}

	// �^�C�}�[�̍X�V
	if (time>0) time--; else time=1;
}

