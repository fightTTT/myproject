#include <math.h>

void DeleteBullet(int id);
void Shot(float x, float y, float vx, float vy);

void ReflectBullet(
	float fx0, float fy0,    // �t�B�[���h�̍�����W
	float fx1, float fy1,    // �t�B�[���h�̉E�����W
	int num_bullet,          // �e�̐�
	float x0[], float y0[],  // �e�̍�����W
	float x1[], float y1[],  // �e�̉E�����W
	float x[], float y[],    // �e�̒��S���W
	float ex[], float ey[],  // �e���������G�̒��S���W
	float speed              // �V���b�g�̑���
) {
	// �S�Ă̒e�Ɋւ��ď������s��
	for (int i=0; i<num_bullet; i++) {
	
		// �e�ƃt�B�[���h�Ƃ̓����蔻�菈���F
		// �e���t�B�[���h�ɐڐG������C
		// �e�������āC�����ʒu����G�Ɍ������ăV���b�g�����B
		if (fx0<x1[i] && x0[i]<fx1 && 
			fy0<y1[i] && y0[i]<fy1) {

			// �e�̏����F
			// ��̓I�ȏ�����DeleteBullet�֐��ōs���Ƃ���B
			DeleteBullet(i);
			
			// �V���b�g�̔��ˁF
			// �G�Ɍ������ăV���b�g�����B
			// ���˂̋�̓I�ȏ�����Shot�֐��ōs���Ƃ���B
			float vx=ex[i]-x[i], vy=ey[i]-y[i];
			if (vx!=0 || vy!=0) {
				float d=sqrt(vx*vx+vy*vy);
				vx*=speed/d;
				vy*=speed/d;
				Shot(x[i], y[i], vx, vy);
			}
		}
	}
}

