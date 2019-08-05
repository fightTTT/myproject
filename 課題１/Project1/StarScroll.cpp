#include <time.h>
#include <DxLib.h>
#include <algorithm>
#include "StarScroll.h"
#include "SceneMng.h"

StarScroll::StarScroll()
{
	Init();
}


StarScroll::~StarScroll()
{
}

void StarScroll::Init(void)
{
	srand(time(NULL));
	_starData[0].reserve(60);
	_starData[1].reserve(40);
	_starData[2].reserve(30);

	for (int i = 0; i < _starData.size(); i++)
	{
		while (_starData[i].size() <  _starData[i].capacity())
		{
			_starData[i].emplace_back(Vector2(rand() % lpSceneMng.gameScreenSize.x, rand() % lpSceneMng.gameScreenSize.y),
									 static_cast<STAR_TYPE>(i), 2 * (i + 1),false);
		}
		
	}

	move = &StarScroll::DownStar;
}

void StarScroll::UpDate()
{
	(this->*move)();
}

void StarScroll::NormalStar(void)
{

}

void StarScroll::DownStar(void)
{
	for (int i = 0; i < _starData.size(); i++)
	{
		if (_starData[i].size() < _starData[i].capacity())
		{
			_starData[i].emplace_back(Vector2(rand() % lpSceneMng.gameScreenSize.x,0), 
									  static_cast<STAR_TYPE>(i), 2 * (i + 1), false);
		}
	}


	for (auto &star : _starData)
	{
		for(auto &data : star)
		{
			std::get<0>(data).y += std::get<2>(data);

			// ‰æ–ÊŠO‚És‚Á‚Ä‚µ‚Ü‚Á‚½‚çdeath‚ğtrue‚É‚·‚é
			if (std::get<0>(data).y >= lpSceneMng.gameScreenSize.y)
			{
				std::get<3>(data) = true;
			}
		}

		star = starDeath(star);
	}

}

void StarScroll::UpStar(void)
{
}

std::vector<StarData> StarScroll::starDeath(std::vector<StarData> star)
{
	auto deth_itr = std::remove_if(star.begin(), star.end(), [](StarData data) {return std::get<3>(data); });
	star.erase(deth_itr, star.end());

	return star;
}

void StarScroll::DrawStar(void)
{
	for (auto &data : _starData)
	{
		for (auto &star : data)
		{
			DrawPixel(std::get<0>(star).x, std::get<0>(star).y, 0xffffff);
		}
	}
	
}
