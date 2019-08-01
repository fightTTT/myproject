#include <stdlib.h>

// �G�̊Ԋu
#define INTERVAL 6

// �G�̏��i�\���́j
typedef struct ENEMY_STRUCT {
	float X, Y;                 // ���݂̍��W
	float OldX[INTERVAL];       // �Â�X���W
	float OldY[INTERVAL];       // �Â�Y���W
	int Index;                  // �ł��Â����W���w���C���f�b�N�X
	struct ENEMY_STRUCT* Prec;  // 1�O�̓G
} ENEMY;

void MoveEnemy(int id);
ENEMY* NewEnemyType();

// �ґ���s�̏���
void Formation(
	int num_enemy,  // �G�̐�
	ENEMY* enemy[]  // �G�̏��i�\���̂ւ̃|�C���^�j
) {
	// �G�𓮂���
	int i;
	for (i=0; i<num_enemy; i++) {
		ENEMY* self=enemy[i];
		ENEMY* prec=self->Prec;
		
		// �擪�ȊO�̓G�𓮂����F
		// 1�O�̓G���ۑ����Ă���Â����W�̂����C
		// �����Ƃ��Â����̂������̍��W�ɂ���B
		if (prec) {
			self->X=prec->OldX[prec->Index];
			self->Y=prec->OldY[prec->Index];
		}
		
		// �擪�̓G�𓮂����F
		// ��̓I�ȏ�����MoveEnemy�֐��ōs���Ƃ���B
		else {
			MoveEnemy(i);
		}
	}

	// �Â����W���L�^����F
	// �ł��Â����W��V�������W�ŏ㏑�����C
	// �C���f�b�N�X���X�V����B
	for (i=0; i<num_enemy; i++) {
		ENEMY* self=enemy[i];
		self->OldX[self->Index]=self->X;
		self->OldY[self->Index]=self->Y;
		self->Index=(self->Index+1)%INTERVAL;
	}
}

// �ґ��̐���
void CreateFormation(
	float x, float y,  // �����n�_�̍��W
	int count          // �ґ����\������G�̐�
) {
	ENEMY* enemy;      // �G��\���\���̂ւ̃|�C���^
	ENEMY* prec=NULL;  // 1�O�̓G���w���|�C���^
	
	// �ґ����\������G�����F
	// �G�̍\���̂��m�ۂ��C���W������������B
	// �\���̊m�ۂ̋�̓I�ȏ�����NewEnemyType�֐��ōs���Ƃ���B
	for (int i=0; i<count; i++, prec=enemy) {
		enemy=NewEnemyType();
		enemy->X=x;
		enemy->Y=y;
		for (int j=0; j<INTERVAL; j++) {
			enemy->OldX[j]=x;
			enemy->OldY[j]=y;
		}
		enemy->Index=0;

		// �擪�ȊO�̓G��1�O�̓G���Q�Ƃ��C
		// ��[�̓G��NULL���Q�Ƃ���B
		enemy->Prec=prec;
	}
}

