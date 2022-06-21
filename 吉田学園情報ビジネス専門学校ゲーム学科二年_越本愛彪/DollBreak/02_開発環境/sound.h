//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_TITLE = 0,		//�^�C�g��BGM
	SOUND_LABEL_GAME,			//�Q�[����BGM
	SOUND_LABEL_RESULT,			//���U���gBGM
	SOUND_LABEL_GAMEOVER,		//�Q�[���I�[�o�[��BGM
	SOUND_LABEL_RELOAD,			//�����[�hSE
	SOUND_LABEL_SE_DECISION,	//����SE
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
