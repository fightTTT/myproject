void Draw(int x, int y);

void InitAimingBulletFP(
	int mx, int my,    // Ž©‹@‚ÌÀ•W
	int ex, int ey,    // “G‚ÌÀ•W
	int& x, int& y,    // ’e‚ÌÀ•W
	int& vx, int& vy,  // ’e‚Ì‘¬“x
	int speed          // ’e‚Ì‘¬‚³
) {
	// ’e‚ÌÀ•W‚ðÝ’è‚·‚é
	x=ex; y=ey;

	// –Ú•W‚É‘Î‚·‚éX•ûŒü‚ÆY•ûŒü‚Ì·•ª‚Ìâ‘Î’l(dx,dy)‚ð‹‚ß‚é
	int dx=mx>=ex?mx-ex:ex-mx;
	int dy=my>=ey?my-ey:ey-my;

	// X•ûŒü‚ÆY•ûŒü‚Ì·•ª‚Ì‚¤‚¿’·‚¢•û‚ð‹——£d‚Æ‚·‚é
	int d=dx>=dy?dx:dy;

	// ‘¬“x(vx,vy)‚ð‹‚ß‚é
	vx=(mx-ex)*speed/d;
	vy=(my-ey)*speed/d;
}

void MoveAimingBulletFP(
	int& x, int& y,  // ’e‚ÌÀ•W
	int vx, int vy   // ’e‚Ì‘¬“x
) {
	// ’e‚ÌÀ•W(x,y)‚É‘¬“x(vx,vy)‚ð‰Á‚¦‚é
	x+=vx;
	y+=vy;

	// ’e‚ð•`‚­F
	// ‰æ–Ê‚É’e‚ð•`‚­‚Æ‚«‚É‚ÍÀ•W‚ð(x>>8, y>>8)‚Æ‚·‚éB
	// ’e‚ð•`‚­‹ï‘Ì“I‚Èˆ—‚ÍDrawŠÖ”‚Ås‚¤‚Æ‚·‚éB
	Draw(x>>8, y>>8);
}

