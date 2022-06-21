//=============================================================================
//
// �S�[���̏��� [goal.cpp]
// Author : �z�{�@���V
//
//=============================================================================
#include <stdio.h>
#include "main.h"
#include "input.h"
#include "player.h"
#include "Goal.h"
#include "goal.h"
#include "game.h"
#include "fade.h"
#include "timer.h"
#include "high_score.h"
#include "stageinterval.h"

//�}�N����`
#define GOAL_SIZE (40)									//�S�[���̃T�C�Y

//�S�[���\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;									//�ʒu
	D3DXVECTOR3 posOld;
	float fWidth;										//��
	float fHeight;										//����
	bool bUse;											//�g�p���Ă��邩�ǂ���
}Goal;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;			//���_�o�b�t�@�ւ̃|�C���^
Goal g_Goal;											//�S�[���̏��

//=============================================================================
//		�S�[���̏���������
//=============================================================================
void InitGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�S�[���̏��̏�����
	g_Goal.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Goal.fWidth = 0.0f;
	g_Goal.fHeight = 0.0f;
	g_Goal.bUse = false;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffGoal, NULL);

	VERTEX_2D *pVtx;									//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Goal.pos.x - GOAL_SIZE / 2, g_Goal.pos.y - GOAL_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Goal.pos.x + GOAL_SIZE / 2, g_Goal.pos.y - GOAL_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Goal.pos.x - GOAL_SIZE / 2, g_Goal.pos.y + GOAL_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Goal.pos.x + GOAL_SIZE / 2, g_Goal.pos.y + GOAL_SIZE, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_���W���A�����b
	g_pVtxBuffGoal->Unlock();
}

//=============================================================================
//		�S�[���̏I������
//=============================================================================
void UninitGoal(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}
}

//=============================================================================
//		�S�[���̍X�V����
//=============================================================================
void UpdataGoal(void)
{
	Player *pPlayer = GetPlayer();

	if (g_Goal.bUse == true)
	{
		if (pPlayer->pos.x >= SCREEN_WIDTH / 2)
		{
			ScrollGoal(D3DXVECTOR3(pPlayer->move.x, 0.0f, 0.0f));
		}
	}
}

//=============================================================================
//		�S�[���̕`�揈��
//=============================================================================
void DrawGoal(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureGoal);

	if (g_Goal.bUse == true)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,									//�v���~�e�B�u�̎��
			0,
			2);														//�v���~�e�B�u�̐�	
	}
}

//=============================================================================
//		�S�[���̐ݒ菈��
//=============================================================================
void SetGoal(D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Goal.bUse == false)
	{
		//�S�[���̊e���̐ݒ�
		g_Goal.pos = pos;
		g_Goal.fHeight = GOAL_SIZE;
		g_Goal.fWidth = GOAL_SIZE;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_Goal.pos.x - GOAL_SIZE / 2, g_Goal.pos.y - GOAL_SIZE / 2, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_Goal.pos.x + GOAL_SIZE / 2, g_Goal.pos.y - GOAL_SIZE / 2, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_Goal.pos.x - GOAL_SIZE / 2, g_Goal.pos.y + GOAL_SIZE / 2, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_Goal.pos.x + GOAL_SIZE / 2, g_Goal.pos.y + GOAL_SIZE / 2, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//�g�p���Ă����ԂɕύX
		g_Goal.bUse = true;
	}

	//���_���W���A�����b�N
	g_pVtxBuffGoal->Unlock();
}

//=============================================================================
//		�S�[���̓����蔻��
//=============================================================================
void ColisionGoal(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	Player *pPlayer = GetPlayer();
	GAMESTATE &pState = *GetGameState();
	FADE fade = GetFade();

	//�S�[���ɐG�ꂽ�Ƃ��̏���
	if (g_Goal.bUse == true)
	{
		if (pPos->x + fWidth / 2 > g_Goal.pos.x - g_Goal.fWidth / 2 &&
			pPos->x - fWidth / 2 < g_Goal.pos.x + g_Goal.fWidth / 2 &&
			pPos->y > g_Goal.pos.y - g_Goal.fHeight / 2 &&
			pPos->y - fHeight < g_Goal.pos.y + g_Goal.fHeight / 2)
		{
			if (pState == GAMESTATE_STAGE1)
			{//�X�e�[�W�P�N���A��
				SetStageInterval(GAMESTATE_STAGE2);
			}
			else if (pState == GAMESTATE_STAGE2)
			{//�X�e�[�W�Q�N���A��
				SetStageInterval(GAMESTATE_STAGE3);
			}
			else if (pState == GAMESTATE_STAGE3)
			{//�X�e�[�W�R�N���A��
				SetStageInterval(GAMESTATE_STAGE4);
			}
			else if (pState == GAMESTATE_STAGE4)
			{//�X�e�[�W�S�N���A��
				SetStageInterval(GAMESTATE_STAGE5);
			}
			else if (pState == GAMESTATE_STAGE5)
			{//�X�e�[�W�T�N���A��
				SetStageInterval(GAMESTATE_STAGE6);
			}
			else if (pState == GAMESTATE_STAGE6)
			{//�X�e�[�W6�N���A��
				SetStageInterval(GAMESTATE_STAGE7);
			}
			else if (pState == GAMESTATE_STAGE7)
			{//�X�e�[�W7�N���A��
				if (fade == FADE_NONE)
				{
					pPlayer->bDisp = false;
					pState = GAMESTATE_CLEAR;
					SaveHighScore(GetTime());
					SetFade(MODE_RESULT);
					SetResultTime(GetTime());
				}
			}
		}
	}
}

//=============================================================================
//		�u���b�N�̃X�N���[������
//=============================================================================
void ScrollGoal(D3DXVECTOR3 move)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	if (g_Goal.bUse == true)
	{
		g_Goal.pos.x -= move.x;
	}

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_Goal.pos.x - g_Goal.fWidth / 2, g_Goal.pos.y - GOAL_SIZE / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_Goal.pos.x + g_Goal.fWidth / 2, g_Goal.pos.y - GOAL_SIZE / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_Goal.pos.x - g_Goal.fWidth / 2, g_Goal.pos.y + GOAL_SIZE / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_Goal.pos.x + g_Goal.fWidth / 2, g_Goal.pos.y + GOAL_SIZE / 2, 0.0f);

	//�A�����b�N
	g_pVtxBuffGoal->Unlock();
}