#include "DxLib.h"
#include "SoundMng.h"



const int & SoundMng::GetID(std::string soundFile, std::string soundName)
{
	if (soundMap.find(soundFile) == soundMap.end())
	{
		// 音楽ファイルの追加
		soundMap[soundFile] = LoadSoundMem(soundFile.c_str());

		// 呼び出す名前の設定
		soundNameMap[soundName] = soundMap[soundFile];
	}

	return soundMap[soundFile];
}

const int & SoundMng::GetSoundName(std::string soundName)
{
	return soundNameMap[soundName];
}

bool SoundMng::SoundInit(std::string soundFile, std::string soundName)
{
	GetID(soundFile, soundName);
	return true;
}

bool SoundMng::SoundInit(std::string soundFile, std::string soundName, int soundVolume)
{
	GetID(soundFile, soundName);
	ChangeVolumeSoundMem((255 * soundVolume) / 100, soundNameMap[soundName]);
	return true;
}

bool SoundMng::SetSound(std::string soundName)
{
	return PlaySoundMem(GetSoundName(soundName), DX_PLAYTYPE_BACK);
}

bool SoundMng::SetSound(std::string soundName, bool playType)
{
	if (playType)
	{
		// trueならﾙｰﾌﾟ
		return PlaySoundMem(GetSoundName(soundName), DX_PLAYTYPE_LOOP);
	}
	else
	{
		// falseなら非ﾙｰﾌﾟ
		return PlaySoundMem(GetSoundName(soundName), DX_PLAYTYPE_BACK);
	}

	return true;
}

bool SoundMng::CheckPlaySound(std::string soundName)
{
	if (CheckSoundMem(soundNameMap[soundName]))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool SoundMng::StopSound(std::string soundName)
{
	// 音楽の停止
	return StopSoundMem(GetSoundName(soundName));
}

bool SoundMng::UnPausingSound(std::string soundName , bool playType)
{
	if (playType)
	{
		// trueならﾙｰﾌﾟ
		return PlaySoundMem(GetSoundName(soundName), DX_PLAYTYPE_LOOP,false);
	}
	else
	{
		// falseなら非ﾙｰﾌﾟ
		return PlaySoundMem(GetSoundName(soundName), DX_PLAYTYPE_BACK,false);
	}
}

SoundMng::SoundMng()
{
}


SoundMng::~SoundMng()
{
}
