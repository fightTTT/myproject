void MoveUp();
void MoveDown();
void MoveLeft();
void MoveRight();
void Shot();
void Laser();

// �X�e�B�b�N�ƃ{�^���̓��͂�\���萔�F
// �e���͂�1�r�b�g�ŕ\���B
enum {
	UP=1, DOWN=2, LEFT=4, RIGHT=8,
	BUTTON1=16, BUTTON2=32
} INPUT;

// ���v���C�f�[�^��ۑ�����\���́F
// �X�e�B�b�N�ƃ{�^���̓��͂�ۑ�����B
#define MAX_TIME 10000
typedef struct {
	char Input[MAX_TIME];
} REPLAY_DATA;

// ���@�𓮂���
void MoveMyShip(
	char input,                // �X�e�B�b�N�ƃ{�^���̓���
	bool is_replay,            // ���v���C���Ȃ��true
	REPLAY_DATA* replay_data,  // ���v���C�f�[�^
	int& time                  // �^�C�}�[
) {
	// ���v���C�̏����F
	// ���v���C���Ȃ�Γ��͂����v���C�f�[�^����ǂݏo���B
	// ���v���C���łȂ���΃��v���C�f�[�^�ɓ��͂�ۑ�����B
	if (is_replay) {
		input=replay_data->Input[time];
	} else {
		replay_data->Input[time]=input;
	}
	
	// �^�C�}�[��i�߂�
	time++;

	// ���͂ɏ]���Ď��@�𓮂����F
	// �ړ���ˌ��̋�̓I�ȏ����́C
	// MoveUp�CMoveDown�CMoveLeft�CMoveRight�C
	// Shot�CLaser�̊e�֐��ōs���Ƃ���B
	if (input&UP   ) MoveUp();
	if (input&DOWN ) MoveDown();
	if (input&LEFT ) MoveLeft();
	if (input&RIGHT) MoveRight();
	if (input&BUTTON1) Shot();
	if (input&BUTTON2) Laser();
}

