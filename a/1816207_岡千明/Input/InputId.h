#pragma once

// ｷｰ入力用enum
enum class INPUT_ID
{
	LEFT,	// 左
	RIGHT,	// 右
	UP,		// 上
	DOWN,	// 下
	BTN_1,	// ﾎﾞﾀﾝ1
	BTN_2,	// ﾎﾞﾀﾝ2
	BTN_3,	// ﾎﾞﾀﾝ3
	BTN_4,	// ﾎﾞﾀﾝ4
	MAX
};

// for分用ｵﾍﾟﾚｰﾀｰのｵｰﾊﾞｰﾛｰﾄﾞ
INPUT_ID begin(INPUT_ID);
INPUT_ID end(INPUT_ID);
INPUT_ID operator++(INPUT_ID& key);
INPUT_ID operator* (INPUT_ID& key);

// enumとenumclassの違い
// enumは暗黙的にint
// enumclassは型を変えれる,int以外にもできる