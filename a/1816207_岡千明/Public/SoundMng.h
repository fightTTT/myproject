#pragma once
#include <map>
#include <vector>

// using宣言
using VEC_INT = std::vector<int>;

// 定義
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
	const int &GetID(std::string soundFile, std::string soundName);		// 音楽の読み込み、参照で返す
	const int &GetSoundName(std::string soundName);						// 音楽の名前を返す

	bool SoundInit(std::string soundFile, std::string soundName);		// 初期化用(音楽ﾌｧｲﾙ､付けたい名前)
	bool SoundInit(std::string soundFile, std::string soundName,int soundVolume);		// 初期化用(音楽ﾌｧｲﾙ､付けたい名前,音量0～100%)
	bool SetSound(std::string soundName);								// 音楽のｾｯﾄ(つけた名前)非ﾙｰﾌﾟ用
	bool SetSound(std::string soundName, bool playType);				// 音楽のｾｯﾄ(つけた名前、trueでﾙｰﾌﾟfalseで非ﾙｰﾌﾟ)
	bool CheckPlaySound(std::string soundName);							// 音楽が再生中ならtrueを返す
	bool StopSound(std::string soundName);								// 音の停止
	bool UnPausingSound(std::string soundName, bool playType);			// 一時停止した音の再生
private:
	SoundMng();
	~SoundMng();

	std::string soundName;
	std::map<std::string, int> soundMap;		// 音楽ﾌｧｲﾙ登録用map
	std::map<std::string, int> soundNameMap;	// 名前付けmap
};

