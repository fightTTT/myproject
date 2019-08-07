void BigShot(int power);
void MaxShot();

void PowerShot(
	bool button,    // �{�^���̏�ԁi�����ꂽ�Ƃ�true�j
	int min_power,  // �e���o��ŏ��̃p���[
	int max_power   // �ő�̃p���[
) {
	// ���߃p���[
	static int power=0;

	// �{�^���������Ă���ꍇ�F
	// ���߃p���[�𑝂₷�B
	if (button && power<max_power) power++;
	
	// �{�^���𗣂��Ă���ꍇ�F
	// ���߃p���[>0�Ȃ�Βe�������C���߃p���[��0�ɖ߂��B
	if (!button && power>0) {
		
		// �ő�p���[�̂Ƃ��F
		// ���ʂȒe�����B
		// ��̓I�ȏ�����MaxShot�֐��ōs���Ƃ���B
		if (power==max_power) MaxShot(); else
		
		// �ŏ��p���[�ȏ�C�ő�p���[�����̂Ƃ��F
		// ���߃p���[�ɉ����������̗��ߌ����e�����B
		// ��̓I�ȏ�����BigShot�֐��ōs���Ƃ���B
		if (min_power<=power) BigShot(power);
		
		// ���߃p���[��0�ɖ߂�
		power=0;

	}
}

void PowerShotReleased(
	bool button,    // �{�^���̏�ԁi�����ꂽ�Ƃ�true�j
	int min_power,  // �e���o��ŏ��̃p���[
	int max_power   // �ő�̃p���[
) {
	// ���߃p���[
	static int power=0;

	// �{�^���𗣂��Ă���ꍇ�F
	// ���߃p���[�𑝂₷�B
	if (!button && power<max_power) power++;
	
	// �{�^���������Ă���ꍇ�F
	// ���߃p���[>0�Ȃ�Βe�������C���߃p���[��0�ɖ߂��B
	if (button && power>0) {
		
		// �ő�p���[�̂Ƃ��F
		// ���ʂȒe�����B
		// ��̓I�ȏ�����MaxShot�֐��ōs���Ƃ���B
		if (power==max_power) MaxShot(); else
		
		// �ŏ��p���[�ȏ�C�ő�p���[�����̂Ƃ��F
		// ���߃p���[�ɉ����������̗��ߌ����e�����B
		// ��̓I�ȏ�����BigShot�֐��ōs���Ƃ���B
		if (min_power<=power) BigShot(power);
		
		// ���߃p���[��0�ɖ߂�
		power=0;
	}
}

