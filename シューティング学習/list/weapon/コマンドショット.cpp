void ComShot(int id);

//============================================================== (1)
// �X�e�B�b�N�ƃ{�^���̏�Ԃ�\���萔�F
// 2�ȏ�̒萔��g�ݍ��킹�邱�Ƃ��ł���B
// �Ⴆ�΁u����v�́C
// �u��v�Ɓu���v�̑g�ݍ��킹�iUP|LEFT�j�ŕ\���B
#define NONE     0  // �������
#define NEUTRAL  1  // �j���[�g����
#define UP       2  // ��
#define DOWN     4  // ��
#define LEFT     8  // ��
#define RIGHT   16  // �E
#define BUTTON  32  // �{�^��

// ���͗����̌��C���͗���
#define NUM_HISTORY 30
static int History[NUM_HISTORY];

// �R�}���h
typedef struct {
	int Length;              // �R�}���h�̒���
	int Limit;               // ���͎��Ԃ̐���
	int Input[NUM_HISTORY];  // ���͓��e
} COMMAND_TYPE;
#define NUM_COMMAND 2
COMMAND_TYPE Command[NUM_COMMAND];

//============================================================== (2)
// ���͗����ƃR�}���h�̏�����
void InitCommandShot()
{
	// ���͗����̏�����
	for (int i=0; i<NUM_HISTORY; i++) History[i]=NONE;

	// �R�}���h1�i�g�����R�}���h�j
	Command[0].Length=4;
	Command[0].Limit=30;
	Command[0].Input[0]=DOWN;
	Command[0].Input[1]=DOWN|RIGHT;
	Command[0].Input[2]=RIGHT;
	Command[0].Input[3]=BUTTON;

	// �R�}���h2�i�������R�}���h�j
	Command[1].Length=4;
	Command[1].Limit=30;
	Command[1].Input[0]=RIGHT;
	Command[1].Input[1]=DOWN;
	Command[1].Input[2]=DOWN|RIGHT;
	Command[1].Input[3]=BUTTON;
}

//============================================================== (3)
// �R�}���h�V���b�g�̔�����s���֐�
void CommandShot(
	bool up, bool down,     // �X�e�B�b�N�̏�ԁi�㉺���E�j
	bool left, bool right,  
	bool button             // �{�^���̏�ԁi�����ꂽ�Ƃ�true�j
) {
	// ���͗����̋L�^�ʒu
	static int index=0;
	
	// ���͂𗚗��ɋL�^����
	History[index]=
		(up?UP:0)|(down?DOWN:0)|
		(left?LEFT:0)|(right?RIGHT:0)|
		(button?BUTTON:0);

	// �e�R�}���h�����͂��ꂽ���ǂ����𔻒肷��
	int c, j, i;
	for (c=0; c<NUM_COMMAND; c++) {
		for (i=0, j=Command[c].Length-1; j>=0; j--) {
			for (; i<Command[c].Limit; i++) {
				if (History[(index-i+NUM_HISTORY)
					%NUM_HISTORY]==Command[c].Input[j]) break;
			}
			if (i==Command[c].Limit) break;
		}
		
		// �R�}���h�̓��͂��m�F�ł����F
		// �R�}���h�V���b�g�������C�������N���A����B
		// ��̓I�ȏ�����ComShot�֐��ōs���Ƃ���B
		if (j==-1) {
			ComShot(j);
			for (i=0; i<NUM_HISTORY; i++) History[i]=NONE;
		}
	}
	
	// �L�^�ʒu���X�V����
	index=(index+1)%NUM_HISTORY;
}

