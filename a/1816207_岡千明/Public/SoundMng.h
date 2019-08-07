#pragma once
#include <map>
#include <vector>

// using�錾
using VEC_INT = std::vector<int>;

// ��`
#define lpSoundMng SoundMng::GetInstance()
#define Sound_ID(X)(SoundMng::GetInstance().GetID(X))

class SoundMng
{
public:
	static SoundMng &GetInstance(void)
	{
		static SoundMng s_Instance;
		return (s_Instance);
	}
	const int &GetID(std::string soundFile, std::string soundName);		// ���y�̓ǂݍ��݁A�Q�ƂŕԂ�
	const int &GetSoundName(std::string soundName);						// ���y�̖��O��Ԃ�

	bool SoundInit(std::string soundFile, std::string soundName);		// �������p(���y̧�٤�t���������O)
	bool SoundInit(std::string soundFile, std::string soundName,int soundVolume);		// �������p(���y̧�٤�t���������O,����0�`100%)
	bool SetSound(std::string soundName);								// ���y�̾��(�������O)��ٰ�ߗp
	bool SetSound(std::string soundName, bool playType);				// ���y�̾��(�������O�Atrue��ٰ��false�Ŕ�ٰ��)
	bool CheckPlaySound(std::string soundName);							// ���y���Đ����Ȃ�true��Ԃ�
	bool StopSound(std::string soundName);								// ���̒�~
	bool UnPausingSound(std::string soundName, bool playType);			// �ꎞ��~�������̍Đ�
private:
	SoundMng();
	~SoundMng();

	std::string soundName;
	std::map<std::string, int> soundMap;		// ���y̧�ٓo�^�pmap
	std::map<std::string, int> soundNameMap;	// ���O�t��map
};

