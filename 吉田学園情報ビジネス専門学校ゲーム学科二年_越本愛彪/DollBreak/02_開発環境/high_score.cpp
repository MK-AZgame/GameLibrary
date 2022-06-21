//========================================================
//
//	�n�C�X�R�A����[high_score.cpp]
//	AUTHOR:�z�{���V
//
//========================================================
#include <stdio.h>
#include "main.h"
#include "time.h"
#include "game.h"
#include "result.h"
#include "high_score.h"

//�}�N����`
#define NUM_TIMER (3)									//�n�C�X�R�A�̌�
#define ONE_SENT  (60)

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureHighScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHighScore = NULL;
D3DXVECTOR3 g_posHighScore;								//�n�C�X�R�A�̈ʒu
int g_nHighScore;										//�n�C�X�R�A�̒l

//========================================================
//			�n�C�X�R�A�̏���������
//========================================================
void InitHighScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTimer;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/number000.png", &g_pTextureHighScore);

	g_posHighScore = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
	g_nHighScore = 0;									//�n�C�X�R�A�̏�����

	//�n�C�X�R�A��ǂݍ���
	LoadHighScore();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TIMER, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffHighScore, NULL);

	VERTEX_2D *pVtx;									//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTimer = 0; nCntTimer < NUM_TIMER; nCntTimer++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(530.0f + (60.0f * nCntTimer), 450.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(590.0f + (60.0f * nCntTimer), 450.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(530.0f + (60.0f * nCntTimer), 530.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(590.0f + (60.0f * nCntTimer), 530.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;
	}

	//���_���W���A�����b�N
	g_pVtxBuffHighScore->Unlock();

	//�n�C�X�R�A�̐ݒ菈��
	SetHighScore();
}

//========================================================
//			�n�C�X�R�A�̏I������
//========================================================
void UninitHighScore(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureHighScore != NULL)
	{
		g_pTextureHighScore->Release();
		g_pTextureHighScore = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffHighScore != NULL)
	{
		g_pVtxBuffHighScore->Release();
		g_pVtxBuffHighScore = NULL;
	}
}

//========================================================
//			�n�C�X�R�A�̍X�V����
//========================================================
void UpdateHighScore(void)
{
}

//========================================================
//			�n�C�X�R�A�̕`�揈��
//========================================================
void DrawHighScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntTimer;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHighScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntTimer = 0; nCntTimer < NUM_TIMER; nCntTimer++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureHighScore);

		//�|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,									//�v���~�e�B�u�̎��
			4 * nCntTimer,
			2);														//�v���~�e�B�u�̐�	
	}
}

//========================================================
//			�n�C�X�R�A�̐ݒ菈��
//========================================================
void SetHighScore()
{
	VERTEX_2D *pVtx;
	float aPosTexU[NUM_TIMER];										//�e���̐��l���i�[
	int nCntTimer;

	aPosTexU[0] = ((g_nHighScore % 1000) / 100) * 0.1f;
	aPosTexU[1] = ((g_nHighScore % 100) / 10) * 0.1f;
	aPosTexU[2] = (g_nHighScore % 10) * 0.1f;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntTimer = 0; nCntTimer < NUM_TIMER; nCntTimer++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + aPosTexU[nCntTimer], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aPosTexU[nCntTimer], 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aPosTexU[nCntTimer], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aPosTexU[nCntTimer], 1.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		pVtx += 4;
	}

	//���_���W���A�����b�N
	g_pVtxBuffHighScore->Unlock();
}

//========================================================
//			�n�C�X�R�A�̓ǂݍ���
//========================================================
void LoadHighScore(void)
{
	FILE *fp;

	//�t�@�C�����J��
	fp = fopen("highscore.txt", "r");

	if (fp != NULL)
	{//����
		//�t�@�C���ǂݍ���
		fscanf(fp, "%d", &g_nHighScore);
	
		//�t�@�C�������
		fclose(fp);
	}
	else
	{//���s
	}
}

//========================================================
//			�n�C�X�R�A�̃Z�[�u
//========================================================
void SaveHighScore(int nScore)
{
	FILE *fp;

	//�n�C�X�R�A�ǂݍ���
	LoadHighScore();

	if (nScore <= g_nHighScore || g_nHighScore == 0)
	{
		g_nHighScore = nScore;

		//�t�@�C�����J��
		fp = fopen("highscore.txt", "w");

		if (fp != NULL)
		{//����
		 //�t�@�C�������o����
			fprintf(fp, "%d", g_nHighScore);

			//�t�@�C�������
			fclose(fp);
		}
		else
		{//���s
		}
	}
}