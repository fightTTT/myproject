#include <math.h>

void MoveJoints(
	int num_joint,         // �֐߂̐�
	float x[], float y[],  // �֐߂̍��W
	float rad[],           // �֐߂̉�]�p�x
	float vrad,            // �֐߂���]���鑬��
	float lrad,            // ��]�p�x�̌��E�l
	float dist,            // �֐ߊԂ̋���
	float tx, float ty     // �ڕW�̍��W
) {
	int i;
	float c, s;
	
	// �O���̏����F
	// ��[���獪���Ɍ������Ċ֐߂̊p�x�����߂�B
	c=(float)cos(vrad);
	s=(float)sin(vrad);
	for (i=1; i<num_joint; i++) {
		float dxt, dyt;       // �֐߂���ڕW�ւ̃x�N�g��
		float dxn, dyn;       // �֐߂����[�ւ̃x�N�g��
		float dxr=0, dyr=0;   // �E���̃x�N�g��
		float dxl=0, dyl=0;   // �����̃x�N�g��
		float dpn, dpr, dpl;  // ���ρi���Ȃ��C�E���C�����j
		
		// �֐߂���ڕW�ւ̃x�N�g���̌v�Z
		dxt=tx-x[i];
		dyt=ty-y[i];

		// �֐߂����[�ւ̃x�N�g���Ɠ��ς̌v�Z
		// �i���Ȃ��ꍇ�̃x�N�g���j
		dxn=x[0]-x[i];
		dyn=y[0]-y[i];
		dpn=dxt*dxn+dyt*dyn;
		
		// �E���̃x�N�g���̌v�Z�F
		// ��]�p�x�̌��E�𒴂����Ƃ��ɂ͉񂳂Ȃ�
		if (rad[i]+vrad<=lrad) {
			dxr=c*dxn-s*dyn;
			dyr=s*dxn+c*dyn;
			dpr=dxt*dxr+dyt*dyr;
		} else dpr=dpn;
		
		// �����̃x�N�g���̌v�Z�F
		// ��]�p�x�̌��E�𒴂����Ƃ��ɂ͉񂳂Ȃ�
		if (rad[i]-vrad>=-lrad) {
			dxl= c*dxn+s*dyn;
			dyl=-s*dxn+c*dyn;
			dpl=dxt*dxl+dyt*dyl;
		} else dpl=dpn;
		
		// ��]�����̑I���F
		// ���ς��r���āC��]��3�ʂ�̒�����I�ԁB
		// ��[����]�����āC�V������[�̈ʒu�����߂�B
		if (dpr>dpn && dpr>dpl) {
			rad[i]+=vrad;
			x[0]=x[i]+dxr;
			y[0]=y[i]+dyr;
		}
		if (dpl>dpn && dpl>dpr) {
			rad[i]-=vrad;
			x[0]=x[i]+dxl;
			y[0]=y[i]+dyl;
		}
	}
	
	// �㔼�̏����F
	// ���������[�Ɍ������Ċ֐߂̈ʒu�����߂�B
	float px=dist, py=0, qx, qy;
	for (i=num_joint-2; i>=0; i--) {
		c=(float)cos(rad[i+1]);
		s=(float)sin(rad[i+1]);
		qx=c*px-s*py;
		qy=s*px+c*py;
		x[i]=x[i+1]+qx;
		y[i]=y[i+1]+qy;
		px=qx;
		py=qy;
	}
}
