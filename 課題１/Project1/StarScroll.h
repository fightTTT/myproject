#pragma once
#include <tuple>
#include <vector>
#include <array>
#include "common/Vector2.h"

enum class STAR_TYPE
{
	SLOW,	 // 奥の星
	NORMAL,	 // 真ん中の星
	FAST,	 // 手前の星
	MAX
};

using StarData = std::tuple<Vector2, STAR_TYPE,int,bool>;	// _pos,星のタイプ、スピード,画面外にいるか。true...画面外にいる

class StarScroll
{
public:
	StarScroll();
	~StarScroll();
	void UpDate();

	// 星を描画する
	void DrawStar(void);

private:

	void Init(void);

	// 通常の動き。星は移動しない
	void NormalStar(void);

	// 自機が前に進んでいる時の動き。星は上から下に移動する。
	void DownStar(void);

	// 自機がキャプチャされた時の星の動き
	void UpStar(void);

	std::vector<StarData> starDeath(std::vector<StarData> star);

	std::array<std::vector<StarData>,static_cast<int>(STAR_TYPE::MAX)> _starData;

	void (StarScroll::*move)(void);

};

