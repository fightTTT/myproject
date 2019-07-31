void MoveByAnalog(
	float& x, float& y,    // ���@�̍��W�iX�����CY�����j
	float speed,           // ���@�̍ō����x
	int jx, int jy,        // �X�e�B�b�N�̓��͒l�iX�����CY�����j
	int range, int margin  // ���͒l�͈̔́i�ő�l�j�C�}�[�W��
) {
	// X�����Ɋւ���ړ�
	if (jx<=-range+margin) x-=speed; else
	if (+range-margin<=jx) x+=speed; else
	if (jx<-margin) x+=speed*(jx+margin)/(range-margin*2); else
	if (+margin<jx) x+=speed*(jx-margin)/(range-margin*2);
	
	// Y�����Ɋւ���ړ�
	if (jy<=-range+margin) y-=speed; else
	if (+range-margin<=jy) y+=speed; else
	if (jy<-margin) y+=speed*(jy+margin)/(range-margin*2); else
	if (+margin<jy) y+=speed*(jy-margin)/(range-margin*2);
}

