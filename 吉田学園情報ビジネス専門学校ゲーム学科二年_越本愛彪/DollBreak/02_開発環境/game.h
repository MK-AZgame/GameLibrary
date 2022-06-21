//========================================================
//
//	�Q�[����������[game.h]
//	Author:�z�{���V
//
//========================================================
#ifndef _GAME_H_
#define _GAME_H_

typedef enum
{
	GAMESTATE_NONE = 0,
	GAMESTATE_NORMAL,
	GAMESTATE_CLEAR,
	GAMESTATE_END,
	GAMESTATE_MAX
} GAMESTATE;

typedef struct
{
	bool bDisp;
} PAUSE;

//�v���g�^�C�v�錾
void InitGame(void);				//�Q�[��������
void UninitGame(void);				//�Q�[���I��
void UpdateGame(void);				//�Q�[���X�V
void DrawGame(void);				//�Q�[���`��
void SetGameState(GAMESTATE state);	//�Q�[����Ԃ̐ݒ�
GAMESTATE *GetGameState(void);		//�Q�[����Ԃ̎擾
PAUSE *GetPause(void);				//�|�[�Y�̏��̎擾

#endif 
