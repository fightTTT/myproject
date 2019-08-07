void DrawOption(float x, float y);

// �I�v�V�����̏�����
void InitOption(
	float x, float y,        // ���@�̍��W�iX�����CY�����j
	float ox[], float oy[],  // ���@�̌Â����W�i�z��j
	int length               // �Â����W�̌��i�z��̒����j
) {
	// �z��̑S�v�f�����@�̍��W�ŏ���������
	for (int i=0; i<length; i++) {
		ox[i]=x; oy[i]=y;
	}
}

// �I�v�V�����̈ړ�
void MoveOption(
	float x, float y,        // ���@�̍��W�iX�����CY�����j
	float ox[], float oy[],  // ���@�̌Â����W�i�z��j
	int length,              // �Â����W�̐��i�z��̒����j
	int& index,              // ���W�̕ۑ��ʒu�i�z���̈ʒu�j
	int opt_count,           // �I�v�V�����̌�
	int opt_interval         // �I�v�V�����̊Ԋu�i�z���̊Ԋu�j
) {
	// �I�v�V������`���F
	// DrawOption�̓I�v�V������`���֐��Ƃ���
	for (int c=0, i=index; c<opt_count; c++) {
		i=(i-opt_interval+length)%length;
		DrawOption(ox[i], oy[i]);
	}
	
	// ���@�̍��W��ۑ����C���W�̕ۑ��ʒu���X�V����
	ox[index]=x;
	oy[index]=y;
	index=(index+1)%length;
}

