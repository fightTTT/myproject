import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class 多関節 extends 触手 {
	
	static final float Dist=15, VRad=0.002f, LRad=0.2f;
	float[] Rad;

	// メインルーチン
	public static void main(String[] args) {
		(new Thread(new 多関節())).start();
	}
	
	// コンストラクタ
	public 多関節() {
		setTitle("多関節");
		Rad=new float[NUM_PART];
		for (int i=0; i<NUM_PART; i++) {
			Rad[i]=VRad;
		}
	}
	
	// 多関節を動かす
	void updatePos() {
		int i;
		float c, s;
		
		// 先端から根元に向かって角度を決める
		c=(float)Math.cos(VRad);
		s=(float)Math.sin(VRad);
		for (i=1; i<NUM_PART; i++) {
			float dxt, dyt;
			float dxn, dyn;
			float dxr=0, dyr=0;
			float dxl=0, dyl=0;
			float dpn, dpr, dpl;
			
			// 目標方向
			dxt=TX-X[i];
			dyt=TY-Y[i];

			// 元の方向
			dxn=X[0]-X[i];
			dyn=Y[0]-Y[i];
			dpn=dxt*dxn+dyt*dyn;
			
			// 右方向の回転
			if (Rad[i]+VRad<=LRad) {
				dxr=c*dxn-s*dyn;
				dyr=s*dxn+c*dyn;
				dpr=dxt*dxr+dyt*dyr;
			} else dpr=dpn;
			
			// 左方向の回転
			if (Rad[i]-VRad>=-LRad) {
				dxl= c*dxn+s*dyn;
				dyl=-s*dxn+c*dyn;
				dpl=dxt*dxl+dyt*dyl;
			} else dpl=dpn;
			
			// 曲がる方向を決め，新しい先端の位置を求める
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
		
		// 根元から先端に向かって座標を求める
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



