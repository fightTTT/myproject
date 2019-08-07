void Explode();
void DrawMyShip(float x, float y);
void DrawScope(float x, float y);
void DrawTarget(float x, float y);
void DrawBomb(float x, float y);

void SightedBomb(
	float x, float y,        // ���@�̍��W
	float sx, float sy,      // �Ə��̍��W
	float bvx, float bvy,    // ���e�̑��x
	bool button              // �{�^���̏�ԁi�����ꂽ�Ƃ�true�j
) {
	// ���e�̏��
	static bool bombing=false;  // ���������ǂ���
	static float bx, by;        // ���e�̍��W
	static float tx, ty;        // ���e�_�̍��W

	// �������ł͂Ȃ��Ƃ��F
	// �{�^���������ꂽ�甚������B
	// ���e�̏������W�ƒ��e�_�̍��W��ݒ肷��B
	if (!bombing) {
		if (button) {
			bombing=true;
			bx=x; by=y;
			tx=sx; ty=sy;
		}
	}
	
	// �������̂Ƃ��F
	// ���e���ړ�������B
	// ���e�����e�_�ɓ��B�����甚��������B
	// �����̋�̓I�ȏ�����Explode�֐��ōs���Ƃ���B
	else {
		bx+=bvx; by+=bvy;
		if (bx==tx && by==ty) {
			Explode();
			bombing=false;
		}
	}
	
	// ���@�ƏƏ���`���F
	// ��̓I�ȏ�����DrawMyShip�֐���DrawScope�֐��ōs���Ƃ���B
	// �Ə��ƒn�㕨�Ƃ̓����蔻�菈�����s���΁C
	// �Ə��̒[��_�ł����邱�Ƃ��ł���B
	DrawMyShip(x, y);
	DrawScope(sx, sy);

	// �������̏ꍇ�ɂ͒��e�_�Ɣ��e��`���F
	// ��̓I�ȏ�����DrawTarget�֐���DrawBomb�֐��ōs���Ƃ���B
	if (bombing) {
		DrawTarget(tx, ty);
		DrawBomb(bx, by);
	}
}

