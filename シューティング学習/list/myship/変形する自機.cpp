void Walk();
void Fly();

// ���@�̌`�ԁi���s�C��s�j
typedef enum {
	WALKING, FLYING
} MYSHIP_FORM;

// ���@�̕ό`
void Transform(
	bool button  // �ό`�{�^���̓���
) {
	static MYSHIP_FORM formation=WALKING;  // ���@�̌`��
	static bool prev_button=false;         // �O��̃{�^������
	
	// �ό`�F
	// �ό`�{�^���������ꂽ��ό`����B
	if (!prev_button && button) {
		if (formation==WALKING) formation=FLYING;
			else formation=WALKING;
	}
	prev_button=button;
	
	// �`�Ԃɂ���ē�����ς���F
	// ��̓I�ȏ�����Walk�CFly�̊e�֐��ōs���Ƃ���B
	if (formation==WALKING) Walk(); else Fly();
}

