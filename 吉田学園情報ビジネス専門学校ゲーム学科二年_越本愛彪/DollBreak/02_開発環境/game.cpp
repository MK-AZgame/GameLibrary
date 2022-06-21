//========================================================
//
//	�Q�[����������[game.cpp]
//	Author:�z�{���V
//
//========================================================
#include "main.h"
#include "game.h"
#include "player.h"
#include "enemy.h"
#include "fade.h"
#include "pause.h"
#include "sound.h"
#include "round.h"
#include "input.h"
#include "light.h"
#include "camera.h"
#include "shadow.h"
#include "wall.h"
#include "meshfield.h"
#include "bullet.h"
#include "effect.h"
#include "Explosion.h"
#include "player.h"
#include "line.h"
#include "model.h"
#include "time.h"
#include "reticle.h"
#include "remainingbullet.h"
#include <Windows.h>

//�O���[�o���ϐ�
GAMESTATE g_gameState;
int g_nCounterGameState;
PAUSE g_pause;

//========================================================
//			�Q�[���̏���������
//========================================================
void InitGame(void)
{
	//�|�[�Y�̏�����
	g_pause.bDisp = false;

	//�c�e���̏�����
	InitRemain();
	//�e�̏�����
	Initbullet();
	//�v���C���[�̏���������
	InitPlayer();
	//�G�l�~�[�̏���������
	InitEnemy();
	//�����̏�����
	InitExplosion();
	//�|�[�Y�̏�����
	InitPause();
	//���b�V���t�B�[���h�̏�����
	InitMeshfield();
	//�e�̏�����
	InitShadow();
	//���f���̏�����
	InitModel();
	//�v���C���[�̏�����
	InitPlayer();
	//�r���{�[�h�̏�����
	//InitBillboard();
	//�J�����̏�����
	InitCamera();
	//���C�g�̏�����
	InitLight();
	//�ǂ̏�����
	InitWall();
	//�G�t�F�N�g�̏�����
	InitEffect();
	//���C���̏�����
	InitLine();
	//���E���h�̏�����
	InitRound();
	//�^�C�}�[�̏�����
	InitTimer();
	//���e�B�N���̏�����
	InitReticle();
	
	SetGameState(GAMESTATE_NORMAL);

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_GAME);
}

//========================================================
//			�Q�[���̏I������
//========================================================
void UninitGame(void)
{
	//�|�[�Y�̏I��
	UninitPause();
	//���E���h�̏I��
	UninitRound();	
	//�^�C�}�[�̏I��
	UninitTimer();
	//�G�l�~�[�̏I������
	UninitEnemy();
	//�v���C���[�̏I������
	UninitPlayer();
	//���b�V���t�B�[���h�̏I������
	UninitMeshfield();
	//�v���C���[�̏I������
	UninitPlayer();
	//���C�g�̏I������
	UninitLight();
	//�J�G���̏I������
	UninitCamera();
	//�e�̏I������
	UninitShadow();
	//�ǂ̏I������
	UninitWall();
	//�r���{�[�h�̏I������
	//UninitBillboard();
	//�e�̏I������
	Uninitbullet();
	//�G�t�F�N�g�̏I������
	UninitEffect();
	//���f���̏I������
	UninitModel();
	//���C���̏I������
	UninitLine();
	//���e�B�N���̏I������
	UninitReticle();
	//�c�e���̏I������
	UninitRemain();
	//�����̏I������
	UninitExplosion();

	//�T�E���h�̒�~
	StopSound();
}

//========================================================
//			�Q�[���̍X�V����
//========================================================
void UpdateGame(void)
{
	PAUSE *pause = GetPause();
	Enemy *penemy = GetEnemy();
	POINT mousePos;
	//debug
	FADE fade = GetFade();
	GAMESTATE &state = *GetGameState();
	//
	//�|�[�Y
	if (GetKeyboardTrigger(DIK_P) || GetJoypadPress(JOYKEY_START) == true)
	{
		pause->bDisp = true;
	}

	//debug
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		if (fade == FADE_NONE)
		{
			StopTimer();
			state = GAMESTATE_CLEAR;
			SetFade(MODE_RESULT);
		}
	}
	//else if (GetKeyboardTrigger(DIK_1))
	//{
	//	if (fade == FADE_NONE)
	//	{
	//		state = GAMESTATE_END;
	//		SetFade(MODE_RESULT);
	//	}
	//}

	if (g_pause.bDisp == false)
	{
		//�}�E�X���\���ɂ���
		ShowCursor(FALSE);

		//�}�E�X�̈ʒu���擾
		GetCursorPos(&mousePos);

		mousePos.x = 640.0f;
		mousePos.y = 360.0f;

		//�}�E�X�̈ʒu��ݒ�
		SetCursorPos(mousePos.x, mousePos.y);

		//�v���C���[�̍X�V����
		UpdatePlayer();
		//�G�l�~�[�̍X�V����
		UpdateEnemy();
		//�G�l�~�[�̃��[�V����
		EnemyMotion();
		//���b�V���t�B�[���h�̍X�V����
		UpdateMeshfield();
		//�J�����̍X�V����
		UpdateCamera();
		//�e�̍X�V����
		UpdataShadow();
		//���C�g�̍X�V����
		UpdateLight();
		//�ǂ̍X�V����
		UpdataWall();
		//�r���{�[�h�̍X�V����
		//UpdataBillboard();
		//�e�̍X�V����
		Updatebullet();
		//�G�t�F�N�g�̍X�V����
		UpdateEffect();
		//���f���̍X�V����
		UpdateModel();
		//���C���̍X�V����
		UpdateLine();
		//���E���h�̍X�V����
		UpdataRound();
		//�^�C�}�[�̍X�V����
		UpdataTimer();
		//�����̍X�V����
		UpdateExplosion();
	}
	else
	{
		//�}�E�X��\���ɂ���
		ShowCursor(TRUE);

		//�|�[�Y�̍X�V
		UpdatePause();
	}
}

//========================================================
//			�Q�[���̕`�揈��
//========================================================
void DrawGame(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DVIEWPORT9 viewport;
	pDevice->GetViewport(&viewport);

	for (int nCntCamera = 0; nCntCamera < MAX_CAMERA; nCntCamera++)
	{
		//�J�����̏I������
		SetCamera(nCntCamera);

		//��ʃN���A
		pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

		//�`��J�n
		if (SUCCEEDED(pDevice->BeginScene()))
		{//�`��J�n�����������ꍇ
		 //�e��I�u�W�F�N�g�̕`�揈��

			//�v���C���[�̕`�揈��
			DrawPlayer();
			//�G�l�~�[�̕`�揈��
			DrawEnemy();
			//���b�V���t�B�[���h�̕`�揈��
			DrawMeshfield();
			//�ǂ̕`�揈��
			DrawWall();
			//�r���{�[�h�̕`�揈��
			//DrawBillboard();
			//���f���̕`�揈��
			DrawModel();
			//�e�̕`�揈��
			DrawShadow();
			//�e�̕`�揈��
			Drawbullet();
			//�G�t�F�N�g�`�揈��
			DrawEffect();
			//���C���̕`�揈��
			DrawLine();
			//���E���h�̕`��
			DrawRound();
			//���e�B�N���̕`��
			DrawReticle();
			//�c�e���̕`��
			DrawRemain();
			//�|�[�Y�̕`��
			DrawPause();

			//�`��I��
			pDevice->EndScene();
		}
	}

	//�r���[�|�[�g�����ɖ߂�
	pDevice->SetViewport(&viewport);

}

//========================================================
//			�Q�[���̏�Ԃ̐ݒ�
//========================================================
void SetGameState(GAMESTATE state)
{
	g_gameState = state;

	g_nCounterGameState = 0;
}
//========================================================
//			�Q�[���̏�Ԃ̎擾
//========================================================
GAMESTATE *GetGameState(void)
{
	return &g_gameState;
}

//========================================================
//			�|�[�Y�̏�Ԃ̎擾
//========================================================
PAUSE *GetPause(void)
{
	return &g_pause;
}