//=============================================================================
//
// ���U���g�̏��� [result.cpp]
// Author : �z�{�@���V
//
//=============================================================================
#include "main.h"
#include "result.h"
#include "player.h"
#include "input.h"
#include "fade.h"
#include "timer.h"
#include "sound.h"
#include "game.h"
#include "high_score.h"

//�}�N����`
#define NUM_BACKGROUND (4)											//���U���g��ʂ̔w�i�Ɏg���e�N�X�`���̐�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureResult[NUM_BACKGROUND] = {};			//���U���g�̃e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffResult = NULL;					//���U���g�̒��_���̃|�C���^
int g_nResultTime;													//���U���g�^�C�����i�[

//=============================================================================
//		���U���g�̏���������
//=============================================================================
void InitResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	GAMESTATE state = *GetGameState();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/result.jpg", &g_pTextureResult[0]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/clearUI.png", &g_pTextureResult[1]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/besttime.png", &g_pTextureResult[2]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/gameover.png", &g_pTextureResult[3]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BACKGROUND, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffResult, NULL);

	VERTEX_2D *pVtx;												//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffResult->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1280.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1280.0f, 720.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	if (state == GAMESTATE_CLEAR)
	{
		pVtx += 4;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(500.0f, 100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(800.0f, 100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(500.0f, 240.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(800.0f, 240.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(500.0f, 400.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(800.0f, 400.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(500.0f, 540.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(800.0f, 540.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		PlaySound(SOUND_LABEL_BGM004);
	}
	else if (state == GAMESTATE_END)
	{
		pVtx += 12;

		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(200.0f, 100.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1000.0f, 100.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(200.0f, 620.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1000.0f, 620.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		PlaySound(SOUND_LABEL_BGM002);
	}

	//���_���W���A�����b�N
	g_pVtxBuffResult->Unlock();

	InitTimer();
	InitHighScore();
}

//=============================================================================
//		���U���g�̏I������
//=============================================================================
void UninitResult(void)
{
	UninitTimer();
	UninitHighScore();

	//�e�N�X�`���̔j��
	for (int nCntTexture = 0; nCntTexture < NUM_BACKGROUND; nCntTexture++)
	{
		if (g_pTextureResult[nCntTexture] != NULL)
		{
			g_pTextureResult[nCntTexture]->Release();
			g_pTextureResult[nCntTexture] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffResult != NULL)
	{
		g_pVtxBuffResult->Release();
		g_pVtxBuffResult = NULL;
	}

	//�T�E���h�̒�~
	StopSound();
}

//=============================================================================
//		���U���g�̍X�V����
//=============================================================================
void UpdataResult(void)
{
	FADE fade = GetFade();

	if (fade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_RETURN) || GetJoypadPress(JOYKEY_A) == true || GetJoypadTrigger(JOYKEY_B) == true ||
			GetJoypadTrigger(JOYKEY_X) == true || GetJoypadTrigger(JOYKEY_Y) == true)
		{
			//ENTER�L�[�������ꂽ
			SetFade(MODE_TITLE);
		}
	}
}

//=============================================================================
//		���U���g�̕`�揈��
//=============================================================================
void DrawResult(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	GAMESTATE &pState = *GetGameState();
	
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffResult, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);


	for (int nCntTexture = 0; nCntTexture < NUM_BACKGROUND; nCntTexture++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureResult[nCntTexture]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,									//�v���~�e�B�u�̎��
			4 * nCntTexture,
			2);														//�v���~�e�B�u�̐�
	}

	if (pState == GAMESTATE_CLEAR)
	{
		DrawResultTime(g_nResultTime);
		DrawHighScore();
	}
}

//===============================================================================================
//									�ŏI�I�ȃ^�C���̎擾
//===============================================================================================
void SetResultTime(int nTime)
{
	g_nResultTime = nTime;
}