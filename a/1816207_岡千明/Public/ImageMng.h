#pragma once
#include <DxLib.h>
#include <map>
#include <vector>
#include <common/Vector2.h>

// using�錾
using VecInt = std::vector<int>;

// ��`^
#define IMAGE_ID(KEY) (ImageMng::GetInstance().GetID(KEY))						// �摜�o�^�������(image/�Z�Z)
#define SET_IMAGE_ID(KEY,F_NAME) (ImageMng::GetInstance().GetID(KEY,F_NAME))	// �摜�o�^�������(�t���������O,image/�Z�Z)

class ImageMng
{
public:
	static ImageMng& GetInstance()		// ���ڽ���~���������߲������Q�Ƃ�
	{
		// nullptr�łȂ���βݽ�ݽ���� �ݸ����
		if (s_Instance == nullptr)
		{
			s_Instance = new ImageMng();
		}
		return (*s_Instance);
	}

	~ImageMng();

	const VecInt& GetID(const std::string& key);												// �摜ID��o�^���n���֐�LoadGraph�p("image/�Z�Z")
	const VecInt& GetID(const std::string& key, const std::string& fileName);					// �摜ID��o�^���n���֐�LoadGraph�p("���������O","image/�Z�Z")

	const VecInt& GetID(const std::string& key, const Vector2& divSize, const Vector2& divCnt);	// �摜ID��o�^���n���֐�LoadDivGraph�p("image/�Z�Z",����1��������̻���,��������)
	const VecInt& GetID(const std::string& key, const std::string& fileName,
		const Vector2& divSize, const Vector2& divCnt);												// �摜ID��o�^���n���֐�LoadDivGraph�p("���������O","image/�Z�Z",����1��������̻���,��������)

private:
	ImageMng();

	std::map<std::string, VecInt> _imgMap;	// �摜̧�ٓo�^�pmap

	static ImageMng *s_Instance;			// �ݽ�ݽ�p
};

// ImageMng�͓��I�ȼݸ����
// const
