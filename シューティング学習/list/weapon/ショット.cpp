void Shot();

void BasicShot(
	bool button  // ����̃{�^���̏�ԁi�����ꂽ�Ƃ�true�j
) {
	// �O��̃{�^���̏�ԁi�����ꂽ�Ƃ�true�j
	static bool prev_button=false;
	
	// �V���b�g�̔��ˁF
	// �O��{�^����������Ă��炸�C���񉟂���Ă���Ƃ������C
	// �V���b�g�𔭎˂���B
	// ���˂̏ڍׂȏ�����Shot�֐��ōs�����̂Ƃ���B
	if (!prev_button && button) Shot();
	
	// ����̃{�^���̏�Ԃ�ۑ�����
	prev_button=button;
}

