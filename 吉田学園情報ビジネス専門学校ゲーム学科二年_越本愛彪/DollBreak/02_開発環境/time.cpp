//========================================================
//
//	�^�C�}�[�̏���[time.cpp]
//	AUTHOR:�z�{���V
//
//========================================================
#include "main.h"
#include "time.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "high_score.h"

//�}�N����`
#define NUM_TIMER (3)											//�^�C�}�[�̌�
#define ONE_SENT  (60)											//1�t���[����1/60�b�Ƃ����Ƃ���1�b

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTimer = NULL;						//�^�C�}�[�̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTimer = NULL;					//�^�C�}�[�̒��_���ւ̃|�C���^
D3DXVECTOR3 g_posTimer;											//�^�C�}�[�̈ʒu
Timer g_timer;													//�^�C�}�[�̏����i�[

//========================================================
//			�^�C�}�[�̏���������
//========================================================
void InitTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/number000.png", &g_pTextureTimer);

	//�O���[�o���ϐ��̏�����
	g_posTimer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�ʒu�̏�����
	g_timer.nSec = 0;											//�^�C�}�[�J�E���g�i�b�j�̏�����
	g_timer.nDec = 00;											//�^�C�}�[�J�E���g�i�����_�ȉ��j�̏�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (NUM_TIMER * 2),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTimer,
		NULL);

	VERTEX_2D *pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTimer = 0; nCntTimer < NUM_TIMER * 2; nCntTimer++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(1070.0f + (50.0f * nCntTimer), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1120.0f + (50.0f * nCntTimer), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1070.0f + (50.0f * nCntTimer), 60.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1120.0f + (50.0f * nCntTimer), 60.0f, 0.0f);

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
	g_pVtxBuffTimer->Unlock();
}

//========================================================
//			�^�C�}�[�̏I������
//========================================================
void UninitTimer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureTimer != NULL)
	{
		g_pTextureTimer->Release();
		g_pTextureTimer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTimer != NULL)
	{
		g_pVtxBuffTimer->Release();
		g_pVtxBuffTimer = NULL;
	}
}

//========================================================
//			�^�C�}�[�̍X�V����
//========================================================
void UpdataTimer(void)
{
	GAMESTATE state = *GetGameState();

	//�����_�ȉ��̐��l������
	g_timer.nDec++;

	//�b���̌���
	if (g_timer.nDec >= 60)
	{//�����_�ȉ��̐��l��60�ȏ�ɂȂ�����
		//������ɉȂ̐��l��0�ɖ߂�
		g_timer.nDec = 0;

		//�b�������Z
		g_timer.nSec++;
	}
}

//========================================================
//			�^�C�}�[�̕`�揈��
//========================================================
void DrawTimer(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTimer, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTimer = 0; nCntTimer < NUM_TIMER; nCntTimer++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTimer);

		//�|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,								//�v���~�e�B�u�̎��
			4 * nCntTimer,
			2);													//�v���~�e�B�u�̐�	
	}
}

//========================================================
//			���U���g�^�C���̕\������
//========================================================
void DrawResultTime(int nResultTime)
{
	VERTEX_2D *pVtx;
	float aPosTexU[NUM_TIMER];									//�e���̐��l�����[

	//�e���̐��l���v�Z
	aPosTexU[0] = ((nResultTime % 1000) / 100) * 0.1f;
	aPosTexU[1] = ((nResultTime % 100) / 10) * 0.1f;
	aPosTexU[2] = (nResultTime % 10) * 0.1f;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTimer->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTimer = 0; nCntTimer < NUM_TIMER; nCntTimer++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(530.0f + (60.0f * nCntTimer), 240.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(590.0f + (60.0f * nCntTimer), 240.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(530.0f + (60.0f * nCntTimer), 320.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(590.0f + (60.0f * nCntTimer), 320.0f, 0.0f);

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//�e�N�X�`���̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + aPosTexU[nCntTimer], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aPosTexU[nCntTimer], 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aPosTexU[nCntTimer], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aPosTexU[nCntTimer], 1.0f);

		pVtx += 4;
	}

	//���_���W���A�����b�N
	g_pVtxBuffTimer->Unlock();

	DrawTimer();
}

//========================================================
//			�^�C�}�[���~�߂�
//========================================================
void StopTimer(void)
{
	//�ŏI�I�ȃ^�C����ۑ�
	SetResultTime(g_timer.nSec);
	SaveHighScore(g_timer.nSec);
}