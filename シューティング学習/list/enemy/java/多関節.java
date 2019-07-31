import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class ���֐� extends �G�� {
	
	static final float Dist=15, VRad=0.002f, LRad=0.2f;
	float[] Rad;

	// ���C�����[�`��
	public static void main(String[] args) {
		(new Thread(new ���֐�())).start();
	}
	
	// �R���X�g���N�^
	public ���֐�() {
		setTitle("���֐�");
		Rad=new float[NUM_PART];
		for (int i=0; i<NUM_PART; i++) {
			Rad[i]=VRad;
		}
	}
	
	// ���֐߂𓮂���
	void updatePos() {
		int i;
		float c, s;
		
		// ��[���獪���Ɍ������Ċp�x�����߂�
		c=(float)Math.cos(VRad);
		s=(float)Math.sin(VRad);
		for (i=1; i<NUM_PART; i++) {
			float dxt, dyt;
			float dxn, dyn;
			float dxr=0, dyr=0;
			float dxl=0, dyl=0;
			float dpn, dpr, dpl;
			
			// �ڕW����
			dxt=TX-X[i];
			dyt=TY-Y[i];

			// ���̕���
			dxn=X[0]-X[i];
			dyn=Y[0]-Y[i];
			dpn=dxt*dxn+dyt*dyn;
			
			// �E�����̉�]
			if (Rad[i]+VRad<=LRad) {
				dxr=c*dxn-s*dyn;
				dyr=s*dxn+c*dyn;
				dpr=dxt*dxr+dyt*dyr;
			} else dpr=dpn;
			
			// �������̉�]
			if (Rad[i]-VRad>=-LRad) {
				dxl= c*dxn+s*dyn;
				dyl=-s*dxn+c*dyn;
				dpl=dxt*dxl+dyt*dyl;
			} else dpl=dpn;
			
			// �Ȃ�����������߁C�V������[�̈ʒu�����߂�
			if (dpr>dpn && dpr>dpl) {
				Rad[i]+=VRad;
				X[0]=X[i]+dxr;
				Y[0]=Y[i]+dyr;
			}
			if (dpl>dpn && dpl>dpr) {
				Rad[i]-=VRad;
				X[0]=X[i]+dxl;
				Y[0]=Y[i]+dyl;
			}
		}
		
		// ���������[�Ɍ������č��W�����߂�
		float px=Dist, py=0, qx, qy;
		for (i=NUM_PART-2; i>=0; i--) {
			c=(float)Math.cos(Rad[i+1]);
			s=(float)Math.sin(Rad[i+1]);
			qx=c*px-s*py;
			qy=s*px+c*py;
			X[i]=X[i+1]+qx;
			Y[i]=Y[i+1]+qy;
			px=qx;
			py=qy;
		}
	}
}



