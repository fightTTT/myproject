void Warp(
	float& x, float& y,    // ���@�̍��W
	float speed,           // ���@�̈ړ����x
	float warp_dist,       // ���[�v�̈ړ�����
	bool up, bool down,    // �X�e�B�b�N���́i�㉺�j
	bool left, bool right  // �X�e�B�b�N���́i���E�j
) {
	static bool 
		up0=false, down0=false,     // �O��̃X�e�B�b�N����
		left0=false, right0=false,  // �i�㉺�C���E�j
		released=true;              // �����͏�Ԃɂ������ǂ���
	static int time=0;              // ���͂̐�������

	// �X�e�B�b�N�����͂��ꂽ�Ƃ�
	if (up || down || left || right) {
		
		// ���[�v����ꍇ�F
		// �����͂��͂���ŁC���������ԓ��ɁC
		// �O��Ɠ������������͂��ꂽ�Ƃ��B
		if (released && time>0 &&
			up==up0 && down==down0 &&
			left==left0 && right==right0
		) {
			if (up   ) y-=warp_dist;
			if (down ) y+=warp_dist;
			if (left ) x-=warp_dist;
			if (right) x+=warp_dist;
		}
		
		// ���[�v���Ȃ��ꍇ�F
		// �����͂��͂���ł��Ȃ����C�������Ԑ؂ꂩ�C
		// �O��ƈقȂ���������͂��ꂽ�Ƃ��B
		// �������L�^���C�������Ԃ�ݒ肷��B
		else {
			up0=up; down0=down;
			left0=left; right0=right;
			time=10;
			
			// ���ʂɈړ�����
			if (up   ) y-=speed;
			if (down ) y+=speed;
			if (left ) x-=speed;
			if (right) x+=speed;
		}

		released=false;
	}
	
	// �X�e�B�b�N�������͏�Ԃ̂Ƃ�
	else released=true;
	
	// ���Ԃ����炷
	if (time>0) time--;
}

