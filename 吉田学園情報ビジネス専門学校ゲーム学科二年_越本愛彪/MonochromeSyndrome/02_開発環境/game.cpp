//=============================================================================
//
// �Q�[���̓������� [game.cpp]
// Author : �z�{�@���V
//
//=============================================================================
#include "main.h"
#include "game.h"
#include "block.h"
#include "goal.h"
#include "player.h"
#include "Bg.h"
#include "fade.h"
#include "pause.h"
#include "sound.h"
#include "timer.h"
#include "input.h"
#include "playerlife.h"
#include "stageinterval.h"

//�O���[�o���ϐ�
GAMESTATE g_gameState;		//�Q�[���̏��
PAUSE g_pause;

//=============================================================================
//		�Q�[���̏���������
//=============================================================================
void InitGame(void)
{
	g_pause.bDisp = false;

	//�X�e�[�W�Ԃ̃t�F�[�h�̏�����
	InitStageInterval(g_gameState);
	//�w�i�̏���������
	InitBg();
	//�v���C���[�̏���������
	InitPlayer();
	//�S�[���̏�����
	InitGoal();
	//�|�[�Y�̏�����
	InitPause();
	//�^�C�}�[�̏�����
	InitTimer();
	//�v���C���[�̗͕\���̏�����
	InitPlayerLife();
	
	SetGameState(GAMESTATE_STAGE1);

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_BGM001);
}

//=============================================================================
//		�Q�[���̏I������
//=============================================================================
void UninitGame(void)
{
	//�w�i�̏I������
	UninitBg();
	//�u���b�N�̏I������
	UninitBlock();
	//�S�[���̏I������
	UninitGoal();
	//�|�[�Y�̏I��
	UninitPause();
	//�^�C�}�[�̏I��
	UninitTimer();
	//�v���C���[�̏I������
	UninitPlayer();
	//�X�e�[�W�Ԃ̃t�F�[�h�̏I��
	UninitStageInterval();
	//�v���C���[�̗͕̑\���I��
	UninitPlayerLife();

	//�T�E���h�̒�~
	StopSound();
}

//=============================================================================
//		�Q�[���̍X�V����
//=============================================================================
void UpdataGame(void)
{
	INTERVAL interval = GetStageInterval();
	PAUSE *pause = GetPause();

	//�|�[�Y
	if (GetKeyboardTrigger(DIK_P) || GetJoypadPress(JOYKEY_START) == true)
	{
		pause->bDisp = true;
	}

	if (interval == INTERVAL_NONE)
	{
		if (g_pause.bDisp == false)
		{
			//�w�i�̍X�V����
			UpdataBg();
			//�v���C���[�̍X�V����
			UpdataPlayer();
			//�u���b�N�̍X�V����
			UpdataBlock();
			//�S�[���̍X�V����
			UpdataGoal();
			//�^�C�}�[�̍X�V����
			UpdataTimer();
			//�v���C���[�̗͕̑\���̍X�V
			UpdataPlayerLife();
		}
		//�|�[�Y�̍X�V
		UpdataPause();
	}

	//�X�e�[�W�Ԃ̃t�F�[�h�̍X�V
	UpdataStageInterval();

	//�f�o�b�O�@�\
	if (GetKeyboardTrigger(DIK_0) == true)
	{
		SetGameState(GAMESTATE_STAGE1);
	}
	else if (GetKeyboardTrigger(DIK_1) == true)
	{
		SetGameState(GAMESTATE_STAGE2);
	}
	else if (GetKeyboardTrigger(DIK_2) == true)
	{
		SetGameState(GAMESTATE_STAGE3);
	}
	else if (GetKeyboardTrigger(DIK_3) == true)
	{
		SetGameState(GAMESTATE_STAGE4);
	}
	else if (GetKeyboardTrigger(DIK_4) == true)
	{
		SetGameState(GAMESTATE_STAGE5);
	}
	else if (GetKeyboardTrigger(DIK_5) == true)
	{
		SetGameState(GAMESTATE_STAGE6);
	}
	else if (GetKeyboardTrigger(DIK_6) == true)
	{
		SetGameState(GAMESTATE_STAGE7);
	}
}

//=============================================================================
//		�Q�[���̕`�揈��
//=============================================================================
void DrawGame(void)
{
	//�w�i�̕`�揈��
	DrawBg();
	//�v���C���[�̕`�揈��
	DrawPlayer();
	//�S�[���̏I������
	DrawGoal();
	//�u���b�N�̕`�揈��
	DrawBlock();
	//�|�[�Y�̕`��
	DrawPause();
	//�^�C�}�[�̕`��
	DrawTimer();
	//�v���C���[�̗͕̑\���̕`��
	DrawPlayerLife();
	//�X�e�[�W�Ԃ̃t�F�[�h�̕`��
	DrawStageInterval();
}

//=============================================================================
//		�Q�[���̏�Ԃ̐ݒ�
//=============================================================================
void SetGameState(GAMESTATE state)
{
	//�u���b�N�̏I��
	UninitBlock();
	//�u���b�N�̏�����
	InitBlock();
	//�S�[���̏I��
	UninitGoal();
	//�S�[���̏�����
	InitGoal();

	//�X�e�[�W�̓ǂݍ���
	switch (state)
	{
	case GAMESTATE_STAGE1:
		ScanFile("./stage/TEXT/stage.txt");
		break;
	case GAMESTATE_STAGE2:
		ScanFile("./stage/TEXT/stage2.txt");
		break;
	case GAMESTATE_STAGE3:
		ScanFile("./stage/TEXT/stage3.txt");
		break;
	case GAMESTATE_STAGE4:
		ScanFile("./stage/TEXT/stage4.txt");
		break;
	case GAMESTATE_STAGE5:
		ScanFile("./stage/TEXT/stage5.txt");
		break;
	case GAMESTATE_STAGE6:
		ScanFile("./stage/TEXT/stage6.txt");
		break;
	case GAMESTATE_STAGE7:
		ScanFile("./stage/TEXT/stage7.txt");
		break;
	}
	g_gameState = state;
}
//=============================================================================
//		�Q�[���̏�Ԃ̎擾
//=============================================================================
GAMESTATE *GetGameState(void)
{
	return &g_gameState;
}

//=============================================================================
//		�|�[�Y�̏�Ԃ̎擾
//=============================================================================
PAUSE *GetPause(void)
{
	return &g_pause;
}