void ComShot(int id);

//============================================================== (1)
// スティックとボタンの状態を表す定数：
// 2つ以上の定数を組み合わせることもできる。
// 例えば「左上」は，
// 「上」と「左」の組み合わせ（UP|LEFT）で表す。
#define NONE     0  // 初期状態
#define NEUTRAL  1  // ニュートラル
#define UP       2  // 上
#define DOWN     4  // 下
#define LEFT     8  // 左
#define RIGHT   16  // 右
#define BUTTON  32  // ボタン

// 入力履歴の個数，入力履歴
#define NUM_HISTORY 30
static int History[NUM_HISTORY];

// コマンド
typedef struct {
	int Length;              // コマンドの長さ
	int Limit;               // 入力時間の制限
	int Input[NUM_HISTORY];  // 入力内容
} COMMAND_TYPE;
#define NUM_COMMAND 2
COMMAND_TYPE Command[NUM_COMMAND];

//============================================================== (2)
// 入力履歴とコマンドの初期化
void InitCommandShot()
{
	// 入力履歴の初期化
	for (int i=0; i<NUM_HISTORY; i++) History[i]=NONE;

	// コマンド1（波動拳コマンド）
	Command[0].Length=4;
	Command[0].Limit=30;
	Command[0].Input[0]=DOWN;
	Command[0].Input[1]=DOWN|RIGHT;
	Command[0].Input[2]=RIGHT;
	Command[0].Input[3]=BUTTON;

	// コマンド2（昇龍拳コマンド）
	Command[1].Length=4;
	Command[1].Limit=30;
	Command[1].Input[0]=RIGHT;
	Command[1].Input[1]=DOWN;
	Command[1].Input[2]=DOWN|RIGHT;
	Command[1].Input[3]=BUTTON;
}

//============================================================== (3)
// コマンドショットの判定を行う関数
void CommandShot(
	bool up, bool down,     // スティックの状態（上下左右）
	bool left, bool right,  
	bool button             // ボタンの状態（押されたときtrue）
) {
	// 入力履歴の記録位置
	static int index=0;
	
	// 入力を履歴に記録する
	History[index]=
		(up?UP:0)|(down?DOWN:0)|
		(left?LEFT:0)|(right?RIGHT:0)|
		(button?BUTTON:0);

	// 各コマンドが入力されたかどうかを判定する
	int c, j, i;
	for (c=0; c<NUM_COMMAND; c++) {
		for (i=0, j=Command[c].Length-1; j>=0; j--) {
			for (; i<Command[c].Limit; i++) {
				if (History[(index-i+NUM_HISTORY)
					%NUM_HISTORY]==Command[c].Input[j]) break;
			}
			if (i==Command[c].Limit) break;
		}
		
		// コマンドの入力が確認できた：
		// コマンドショットを撃ち，履歴をクリアする。
		// 具体的な処理はComShot関数で行うとする。
		if (j==-1) {
			ComShot(j);
			for (i=0; i<NUM_HISTORY; i++) History[i]=NONE;
		}
	}
	
	// 記録位置を更新する
	index=(index+1)%NUM_HISTORY;
}

