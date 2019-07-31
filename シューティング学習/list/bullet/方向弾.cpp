#include <math.h>

void InitDirectedBullet(
	float ex, float ey,    // “G‚ÌÀ•W
	float& x, float& y,    // ’e‚ÌÀ•W
	float& vx, float& vy,  // ’e‚Ì‘¬“x
	float speed,           // ’e‚Ì‘¬‚³
	float theta            // ”­ËŠp“x
) {
	// ’e‚ÌÀ•W‚ğİ’è‚·‚é
	x=ex; y=ey;

	// ‘¬‚³speed‚ÅŠp“xtheta‚Ì•ûŒü‚É”ò‚Ô’e‚Ì‘¬“x(vx,vy)‚ğ‹‚ß‚éF
	// M_PI‚Í‰~ü—¦B
	vx=cos(M_PI/180*theta)*speed;
	vy=sin(M_PI/180*theta)*speed;
}

void MoveDirectedBullet(
	float& x, float& y,  // ’e‚ÌÀ•W
	float vx, float vy   // ’e‚Ì‘¬“x
) {
	// ’e‚ÌÀ•W(x,y)‚É‘¬“x(vx,vy)‚ğ‰Á‚¦‚é
	x+=vx;
	y+=vy;
}

