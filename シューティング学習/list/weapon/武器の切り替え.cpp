void DrawIcon(int id);
void FocusIcon(int id);

// ����̐�
#define MAX_WEAPONS 5

// �����؂�ւ��鏈��
void SelectWeapon(
	bool button  // �{�^���̏�ԁi�������Ƃ�true�j
) {
	static int weapon_id=0;         // ���ݑI�𒆂̕���̔ԍ�
	static bool prev_button=false;  // �O��̃{�^���̏��
	
	// �����؂�ւ���F
	// �O��{�^���������Ă��炸�C���񉟂��Ă�����C
	// ����̐؂�ւ����s���B
	if (!prev_button && button) {
		weapon_id=(weapon_id+1)%MAX_WEAPONS;
	}
	
	// ����̃A�C�R����\������F
	// �S�A�C�R����\�����C�I�𒆂̃A�C�R���͖ڗ�������B
	// �\���̋�̓I�ȏ�����DrawIcon�֐���FocusIcon�֐���
	// �s���Ƃ���B
	for (int i=0; i<MAX_WEAPONS; i++) DrawIcon(i);
	FocusIcon(weapon_id);

	// ����̃{�^���̏�Ԃ�ۑ�����
	prev_button=button;
}


