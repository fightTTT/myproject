#include "Ojisan.h"
#include<DxLib.h>
#include"ScreenShaker.h"
const int GROUND_LINE=428;

Ojisan::Ojisan(const char* filename,int xnum,int ynum,ScreenShaker& shaker) : Character(filename,xnum,ynum),_shaker(shaker),
	_vx(0),_vy(0),_ax(0),_ay(0),_isPushJump(false),_isJumped(false)
{
	_phase=&Ojisan::FallingPhase;
	//ひもの支点を定義する
	_endPoint.x=320;
	_endPoint.y=0;
	_scroll.x=0;
	_scroll.y=0;
	_v=0;
	OnInit(_vx,_vy);
	_explosionSE = LoadSoundMem("sound/explosion.mp3");
	_explosionH = LoadGraph("img/explosion.png");
	_g=0.8f;//重力の定義
	_length=320;//紐の長さの計算
	_handle=LoadGraph("img/ojisan.png");
}

void 
Ojisan::OnActivateTension(){
	_phase=&Ojisan::SwingPhase;
}

void 
Ojisan::FallingPhase(){
	char keyBuff[256];
	DxLib::GetHitKeyStateAll(keyBuff);
	if(keyBuff[KEY_INPUT_SPACE]){
		if(!_isPushJump){
			OnActivateTension();
		}
		_isPushJump=true;
	}else{
		_isPushJump=false;
	}
	OnMove(_pos.x,_pos.y,_vx,_vy);
	_vy+=_g;
	DrawLine(_pos.x,_pos.y,_endPoint.x,0,0xffffffff,2);
	DrawRotaGraph(_pos.x,_pos.y,1.0, (-180 * (DX_PI / 180)),_handle,true,false);
	SetStartPosition(_pos.x,_pos.y);
	CheckGround();//地面衝突チェック＆地面衝突状態へ移行
}

//振り子フェーズ
void 
Ojisan::SwingPhase(){
	if(_pos.y>=GROUND_LINE){///地面に当たったら…
		OnGround(_pos.x,_pos.y,_vx,_vy);
	}
	char keyBuff[256];
	DxLib::GetHitKeyStateAll(keyBuff);
	if(keyBuff[KEY_INPUT_SPACE]){
		if(!_isPushJump){
			OnPushJumpKey(_vx,_vy);
		}
		_isPushJump=true;
	}else{
		_isPushJump=false;
	}
	if(keyBuff[KEY_INPUT_LEFT]){
		OnPushLeftKey(_vx,_vy);
	}
	if(keyBuff[KEY_INPUT_RIGHT]){
		OnPushRightKey(_vx,_vy);
	}

	Vec2 v=(_pos-_endPoint);
	
	v=v.normalized();
	
	_theta = atan2f(v.y,v.x);//ベクトルから現在の角度を計算
	

	float a = cos(_theta);//加速度計算
	_v+=a;//速度へ加算

	

	float vx = -sin(_theta) * _v;//速度を分配(X方向)
	float vy = cos(_theta) * _v;//速度を分配(Y方向)

	if(_isJumped){
		OnMove(_pos.x,_pos.y,_vx,_vy);
		_vy+=_g;
		
	}else{
		OnMove(_pos.x,_pos.y,vx,vy);
		OnAdjust();
	}
	
	

	
	if(!_isJumped){
		DrawLine(_pos.x - _scroll.x,_pos.y,320 - _scroll.x,0,0xffffffff,2);
	}
	DrawRotaGraph(_pos.x - _scroll.x,_pos.y,1.0,(_theta-(-90*(DX_PI/180))),_handle,true,false);
}
void 
Ojisan::FlyingPhase(){
	Vec2 v=(_pos-_endPoint);
	v=v.normalized();
	_theta =atan2f(Cross(v,Vec2(-1,0)),Dot(v,Vec2(-1,0))) ;
	
	CheckGround();//地面衝突チェック＆地面衝突状態へ移行

	char keyBuff[256];
	DxLib::GetHitKeyStateAll(keyBuff);
	//if(keyBuff[KEY_INPUT_SPACE]){
	//	//おじさんを初期状態に戻す
	//	if(!_isPushJump){
	//		ResetOjisan(_endPoint.x,_endPoint.y);
	//		_scroll.x=10;
	//		_scroll.y=0;
	//	}
	//	_isPushJump=true;
	//}else{
	//	_isPushJump=false;
	//}
	

	OnMove(_pos.x, _pos.y, _vx, _vy);

	_vy+=_g*0.25;//重力加速


	DrawRotaGraph(_pos.x-_scroll.x,_pos.y-_scroll.y,1.0,-(_theta -3.14159265358979/2),_handle,true,false);
}

void Ojisan::CheckGround()
{
	if (_pos.y >= GROUND_LINE) {///地面に当たったら…
		OnGround(_pos.x, _pos.y, _vx, _vy);
		_shaker.Shake();
		_phase = &Ojisan::GroundPhase;
		PlaySoundMem(_explosionSE, DX_PLAYTYPE_BACK);
	}
}

void
Ojisan::GroundPhase() {
	char keyBuff[256];
	DxLib::GetHitKeyStateAll(keyBuff);
	if (keyBuff[KEY_INPUT_SPACE]) {
		if (!_isPushJump) {
			ResetOjisan(_endPoint.x, _endPoint.y);
			_scroll.x = 0;
			_scroll.y = 0;
		}
		_isPushJump = true;
	}
	else {
		_isPushJump = false;
	}
	DrawRotaGraph(_pos.x - _scroll.x, _pos.y - _scroll.y, 1.0, -(_theta - 3.14159265358979 / 2), _handle, true, false);
	DxLib::DrawRectRotaGraph2(_pos.x - _scroll.x, _pos.y - _scroll.y, (_frame / 2) * 256, 0, 256, 256, 128, 220, 2.0f, 0.0, _explosionH, true);
	++_frame;
}

void
Ojisan::SetEndPoint(float x,float y){
	_endPoint.x=x;
	_endPoint.y=y;
	Vec2 v = _pos-_endPoint;
	_length=v.Length();
}

void 
Ojisan::SetStartPosition(float x, float y){
	Character::SetPosition(x,y);
	Vec2 v = _pos-_endPoint;
	_length=v.Length();
	_v = 0;
}

void 
Ojisan::ResetOjisan(float x, float y){
	_isJumped=false;
	SetStartPosition(x,y);
	_phase=&Ojisan::FallingPhase;
	_frame = 0;
}


Ojisan::~Ojisan(void)
{
}

void
Ojisan::SetAngle(float yrate){
	_vy=_vx*yrate;
}

void
Ojisan::SetAccel(float ax,float ay){
	_ax=ax;
	_ay=ay;
}

void 
Ojisan::Update(){
	(this->*_phase)();
}

void Ojisan::OnAdjust(){
	Vec2 v=(_pos-_endPoint);
	if(v.Length() > _length){
		_pos = _endPoint + v.normalized()*_length;
	}
}

void //移動イベント
Ojisan::OnMove(float& x, float& y,float vx,float vy){
	//�@ここに移動のための処理を描いてください。
	x+=vx;
	y+=vy;
}

void //キーを押していない時の加速イベント
Ojisan::OnAccel(float& vx,float& vy,const float& ax, const float& ay){
	//�Aここに加速のための処理を書いてください。0.5くらい
	vx+=ax;
	vy+=ay;
}


void //初期化イベント
Ojisan::OnInit(float& vx,float& vy){
	//�Bここに初期化の処理を書いてください。
}

void //着地イベント
Ojisan::OnGround(float& x, float& y,float& vx,float& vy){
	//�Cここに着地時の処理を書いてください
	y=GROUND_LINE;
	vy=0;
	vx=0;
}

void //ジャンプキーイベント
Ojisan::OnPushJumpKey(float& vx, float& vy){

	//�Dここにジャンプキーが押された時の処理を書いてください。-10.0くらい
	Vec2 v=(_pos-_endPoint);
	v=v.normalized();
	_isJumped=true;
	float theta=atan2f(Cross(v,Vec2(-1,0)),Dot(v,Vec2(-1,0)));
	float cost = Dot(v,Vec2(-1,0));
	float sint = Cross(v,Vec2(-1,0));
	_v *= 1.6f;
	vx=_v* -sin(_theta)+sint;
	vy=_v* cos(_theta)+cost +_g;

	_phase=&Ojisan::FlyingPhase;



}
bool 
Ojisan::IsFlying()const {
	return _isJumped;
}

void //左キー押されたイベント
Ojisan::OnPushLeftKey(float& vx,float& vy){
	//�Eここに左キーを押された時の処理を書いてください
	_v+=0.5f;
}


void //右キー押されたイベント
Ojisan::OnPushRightKey(float& vx, float &vy){
	//�Fここに右キーを押された時の処理を書いてください
	_v-=0.5f;
}
