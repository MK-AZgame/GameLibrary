//=============================================================================
//
// �Q�[���̓������� [game.h]
// Author : �z�{�@���V
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

typedef enum
{
	GAMESTATE_NONE = 0,
	GAMESTATE_STAGE1,
	GAMESTATE_STAGE2,
	GAMESTATE_STAGE3,
	GAMESTATE_STAGE4,
	GAMESTATE_STAGE5,
	GAMESTATE_STAGE6,
	GAMESTATE_STAGE7,
	GAMESTATE_CLEAR,
	GAMESTATE_END,
	GAMESTATE_MAX
} GAMESTATE;

typedef struct
{
	bool bDisp;
} PAUSE;

//�v���g�^�C�v�錾
void InitGame(void);				//�Q�[���̏�����
void UninitGame(void);				//�Q�[���̏I��
void UpdataGame(void);				//�Q�[���̍X�V
void DrawGame(void);				//�Q�[���̕`��
void SetGameState(GAMESTATE state);	//�Q�[����Ԃ̐ݒ�
GAMESTATE *GetGameState(void);		//�Q�[�����̎擾
PAUSE *GetPause(void);				//�|�[�Y��Ԃ��擾

#endif 