#pragma once
#include <DxLib.h>
#include <map>
#include <vector>
#include <common/Vector2.h>

// usingéŒ¾
using VecInt = std::vector<int>;

// ’è‹`^
#define IMAGE_ID(KEY) (ImageMng::GetInstance().GetID(KEY))						// ‰æ‘œ“o˜^¤ˆø”‚Í(image/ZZ)
#define SET_IMAGE_ID(KEY,F_NAME) (ImageMng::GetInstance().GetID(KEY,F_NAME))	// ‰æ‘œ“o˜^¤ˆø”‚Í(•t‚¯‚½‚¢–¼‘O,image/ZZ)

class ImageMng
{
public:
	static ImageMng& GetInstance()		// ±ÄŞÚ½‚ª—~‚µ‚¢‚½‚ßÎß²İÀ°‚©QÆ‚Å
	{
		// nullptr‚Å‚È‚¯‚ê‚Î²İ½Àİ½‚·‚é ¼İ¸ŞÙÄİ
		if (s_Instance == nullptr)
		{
			s_Instance = new ImageMng();
		}
		return (*s_Instance);
	}

	~ImageMng();

	const VecInt& GetID(const std::string& key);												// ‰æ‘œID‚ğ“o˜^‚µ“n‚·ŠÖ”LoadGraph—p("image/ZZ")
	const VecInt& GetID(const std::string& key, const std::string& fileName);					// ‰æ‘œID‚ğ“o˜^‚µ“n‚·ŠÖ”LoadGraph—p("‚Â‚¯‚½‚¢–¼‘O","image/ZZ")

	const VecInt& GetID(const std::string& key, const Vector2& divSize, const Vector2& divCnt);	// ‰æ‘œID‚ğ“o˜^‚µ“n‚·ŠÖ”LoadDivGraph—p("image/ZZ",•ªŠ„1–‡‚ ‚½‚è‚Ì»²½Ş,‘•ªŠ„”)
	const VecInt& GetID(const std::string& key, const std::string& fileName,
		const Vector2& divSize, const Vector2& divCnt);												// ‰æ‘œID‚ğ“o˜^‚µ“n‚·ŠÖ”LoadDivGraph—p("‚Â‚¯‚½‚¢–¼‘O","image/ZZ",•ªŠ„1–‡‚ ‚½‚è‚Ì»²½Ş,‘•ªŠ„”)

private:
	ImageMng();

	std::map<std::string, VecInt> _imgMap;	// ‰æ‘œÌ§²Ù“o˜^—pmap

	static ImageMng *s_Instance;			// ²İ½Àİ½—p
};

// ImageMng‚Í“®“I‚È¼İ¸ŞÙÄİ
// const
