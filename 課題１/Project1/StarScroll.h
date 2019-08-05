#pragma once
#include <tuple>
#include <vector>
#include <array>
#include "common/Vector2.h"

enum class STAR_TYPE
{
	SLOW,	 // ���̐�
	NORMAL,	 // �^�񒆂̐�
	FAST,	 // ��O�̐�
	MAX
};

using StarData = std::tuple<Vector2, STAR_TYPE,int,bool>;	// _pos,���̃^�C�v�A�X�s�[�h,��ʊO�ɂ��邩�Btrue...��ʊO�ɂ���

class StarScroll
{
public:
	StarScroll();
	~StarScroll();
	void UpDate();

	// ����`�悷��
	void DrawStar(void);

private:

	void Init(void);

	// �ʏ�̓����B���͈ړ����Ȃ�
	void NormalStar(void);

	// ���@���O�ɐi��ł��鎞�̓����B���͏ォ�牺�Ɉړ�����B
	void DownStar(void);

	// ���@���L���v�`�����ꂽ���̐��̓���
	void UpStar(void);

	std::vector<StarData> starDeath(std::vector<StarData> star);

	std::array<std::vector<StarData>,static_cast<int>(STAR_TYPE::MAX)> _starData;

	void (StarScroll::*move)(void);

};

