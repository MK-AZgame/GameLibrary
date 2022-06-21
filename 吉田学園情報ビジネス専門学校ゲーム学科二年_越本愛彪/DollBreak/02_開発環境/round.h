//========================================================
//
//	���E���h�̏���[round.h]
//	AUTHOR:�z�{���V
//
//========================================================
#ifndef _ROUND_H_
#define _ROUND_H_

//���E���h�̍\����
typedef struct
{
	int nNumRound;							//���E���h��
	int nIntervalTime;						//���E���h�Ԃ̃C���^�[�o��
	int nState;								//���E���h�̏��
}Round;

//���E���h�̏��
typedef enum
{
	ROUND_NONE = 0,
	ROUND_FIRST,
	ROUND_SECOND,
	ROUND_THIRD,
	ROUND_FOURTH,
	ROUND_FIFTH,
	ROUND_INTERVAL,
	ROUND_MAX
}ROUNDNUM;

//�v���g�^�C�v�錾
void InitRound(void);						//���E���h�̏���������
void UninitRound(void);						//���E���h�̏I������
void UpdataRound(void);						//���E���h�̍X�V����
void DrawRound(void);						//���E���h�̕`�揈��
void SetRound();							//���E���h�̐ݒ菈��
void ChangeRound(ROUNDNUM nextRound);		//���E���h�̏�Ԃ�؂�ւ���
Round *GetRound();							//���E���h�̏����擾

#endif 