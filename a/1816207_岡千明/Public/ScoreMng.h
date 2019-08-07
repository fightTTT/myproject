#pragma once

// ��`
#define lpScoreMng ScoreMng::GetInstance()

class ScoreMng
{
public:
	static ScoreMng& GetInstance()	// ���ڽ���~���������߲������Q�Ƃ�
	{
		return (*s_Instance);		// *�Œ��g(�׽�̎���)��Ԃ�
	}

	const void AddScore(int score);	// ��������Z
	void ScoreReset(void);			// ����̏�����(0�ɂ���)
	void Draw(void);				// �`��

private:
	// �֐���޼ު��
	// �޽�׸����Ă�
	struct ScoreMngDeleter
	{
		void operator()(ScoreMng* sceneMng)const
		{
			delete sceneMng;
		}
	};
	ScoreMng();
	~ScoreMng();

	bool Init(void);	// �������p
	int _score;			// ����ۑ��p
	static std::unique_ptr<ScoreMng, ScoreMngDeleter> s_Instance;	// �ݽ�ݽ�p�ư��߲���
};

