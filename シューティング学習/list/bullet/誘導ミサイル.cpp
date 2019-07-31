#include <stdio.h>

// �~�T�C���̊e������\���\����
typedef struct MISSILE_STRUCT {
	float X, Y;                   // ���W
	float VX, VY;                 // ���x
	float OldX, OldY;             // �Â����W
	float Angle;                  // ��]�p�x
	float OldAngle;               // �Â���]�p�x
	struct MISSILE_STRUCT* Prec;  // 1�O�̕����ւ̃|�C���^
	                              // �i�擪�����̏ꍇ�ɂ�NULL�j
	bool IsMissile;               // �~�T�C�����ǂ���
	                              // �itrue�Ȃ�~�T�C���C
	                              //   false�Ȃ牌�j
} MISSILE_TYPE;

MISSILE_TYPE* NewMissileType();

// �~�T�C���̔���
void ShootMissile(
	float x, float y,   // ���˒n�_�̍��W
	int length          // ���[�U�[�̒���
) {
	MISSILE_TYPE* missile;    // �~�T�C���̍\���̂ւ̃|�C���^
	MISSILE_TYPE* prec=NULL;  // 1�O�̕������w���|�C���^
	
	// �~�T�C���̊e���������F
	// �~�T�C���̍\���̂��m�ۂ��C���W������������B
	// �\���̊m�ۂ̋�̓I�ȏ�����NewMissileType�֐��ōs���Ƃ���B
	for (int i=0; i<length; i++, prec=missile) {
		missile=NewMissileType();
		missile->X=missile->OldX=x;
		missile->Y=missile->OldY=y;
		missile->Angle=missile->OldAngle=0;

		// ���̕�����1�O�̕������Q�Ƃ���悤�ɂ��C
		// ��[�����ɂ�NULL���Q�Ƃ�����B
		missile->Prec=prec;

		// ��[�����̓~�T�C���ɁC���̕����͉��ɂ���B
		missile->IsMissile=(i==0);
	}
}

