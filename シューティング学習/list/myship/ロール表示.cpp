typedef enum {
	LEFT_BIG_ROLL, LEFT_SMALL_ROLL,
	CENTER,
	RIGHT_SMALL_ROLL, RIGHT_BIG_ROLL
} ROLL;

void Draw(ROLL roll);

void RollMyShip(
	int& roll,             // ���[���̊p�x
	bool left, bool right  // ���E�����ւ̃X�e�B�b�N����
) {
	// �X�e�B�b�N�ō�����͂����ꍇ�F
	// -20<roll�Ȃ��roll��-1����B
	if (left && -20<roll) roll--;

	// �X�e�B�b�N�ŉE����͂����ꍇ�F
	// roll<20�Ȃ��roll��+1����B
	if (right && roll<20) roll++;

	// �X�e�B�b�N�ō����E�����͂��Ă��Ȃ��ꍇ�F
	// roll��0�ɋ߂Â��悤�ɂ���B
	if (!left && !right) {
		if (roll<0) roll++; else
		if (0<roll) roll--;
	}

	// roll�̒l�ɉ����ĈقȂ�p�^�[����\������F
	// �p�^�[���\���̋�̓I�ȏ����͊֐�Draw�̒��ōs���Ƃ���B
	if (-20<=roll && roll<-15) Draw(LEFT_BIG_ROLL);    else
	if (-15<=roll && roll< -5) Draw(LEFT_SMALL_ROLL);  else
	if ( -5<=roll && roll<= 5) Draw(CENTER);           else
	if (  5< roll && roll<=15) Draw(RIGHT_SMALL_ROLL); else
	if ( 15< roll && roll<=20) Draw(RIGHT_BIG_ROLL);
}

