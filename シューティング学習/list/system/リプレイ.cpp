void MoveUp();
void MoveDown();
void MoveLeft();
void MoveRight();
void Shot();
void Laser();

// スティックとボタンの入力を表す定数：
// 各入力を1ビットで表す。
enum {
	UP=1, DOWN=2, LEFT=4, RIGHT=8,
	BUTTON1=16, BUTTON2=32
} INPUT;

// リプレイデータを保存する構造体：
// スティックとボタンの入力を保存する。
#define MAX_TIME 10000
typedef struct {
	char Input[MAX_TIME];
} REPLAY_DATA;

// 自機を動かす
void MoveMyShip(
	char input,                // スティックとボタンの入力
	bool is_replay,            // リプレイ中ならばtrue
	REPLAY_DATA* replay_data,  // リプレイデータ
	int& time                  // タイマー
) {
	// リプレイの処理：
	// リプレイ中ならば入力をリプレイデータから読み出す。
	// リプレイ中でなければリプレイデータに入力を保存する。
	if (is_replay) {
		input=replay_data->Input[time];
	} else {
		replay_data->Input[time]=input;
	}
	
	// タイマーを進める
	time++;

	// 入力に従って自機を動かす：
	// 移動や射撃の具体的な処理は，
	// MoveUp，MoveDown，MoveLeft，MoveRight，
	// Shot，Laserの各関数で行うとする。
	if (input&UP   ) MoveUp();
	if (input&DOWN ) MoveDown();
	if (input&LEFT ) MoveLeft();
	if (input&RIGHT) MoveRight();
	if (input&BUTTON1) Shot();
	if (input&BUTTON2) Laser();
}

