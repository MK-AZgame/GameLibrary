//=============================================================================
//
// �X�e�[�W�Ԃ̃t�F�[�h�̏��� [stageinterval.cpp]
// Author : �z�{�@���V
//
//=============================================================================
#include "stageinterval.h"
#include "player.h"

//�O���[�o���ϐ�
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStageInterval = NULL;		//�X�e�[�W�Ԃ̃t�F�[�h�̒��_���̃|�C���^
INTERVAL g_StageInterval;									//�X�e�[�W�Ԃ̃t�F�[�h�̏����i�[
GAMESTATE g_Nextstage;										//���̃X�e�[�W�̏����i�[
D3DXCOLOR g_Interval;										//�X�e�[�W�Ԃ̃t�F�[�h�̓����x

//=============================================================================
//		�t�F�[�h�̏���������
//=============================================================================
void InitStageInterval(GAMESTATE Nextstage)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_StageInterval = INTERVAL_IN;
	g_Nextstage = Nextstage;
	g_Interval = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffStageInterval, NULL);

	VERTEX_2D *pVtx;												//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffStageInterval->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_���W���A�����b�N
	g_pVtxBuffStageInterval->Unlock();

	//���[�h�ݒ�
	SetGameState(g_Nextstage);
}

//=============================================================================
//		�t�F�[�h�̏I������
//=============================================================================
void UninitStageInterval(void)
{
	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffStageInterval != NULL)
	{
		g_pVtxBuffStageInterval->Release();
		g_pVtxBuffStageInterval = NULL;
	}
}

//=============================================================================
//		�t�F�[�h�̍X�V����
//=============================================================================
void UpdataStageInterval(void)
{
	VERTEX_2D *pVtx;												//���_���ւ̃|�C���^

	if (g_StageInterval != INTERVAL_NONE)
	{
		if (g_StageInterval == INTERVAL_IN)
		{//�t�F�[�h�C�����
			g_Interval.a -= 0.025f;
			if (g_Interval.a <= 0.0f)
			{
				g_Interval.a = 0.0f;
				g_StageInterval = INTERVAL_NONE;
			}
		}
		else if (g_StageInterval == INTERVAL_OUT)
		{//�t�F�[�h�A�E�g���
			g_Interval.a += 0.025f;
			if (g_Interval.a >= 1.0f)
			{
				SetPlayerPos(D3DXVECTOR3(50.0f, 660.0f, 0.0f));
				g_Interval.a = 1.0f;
				g_StageInterval = INTERVAL_IN;

				//���[�h�ݒ�
				SetGameState(g_Nextstage);
			}
		}
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffStageInterval->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_Interval.a);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_Interval.a);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_Interval.a);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, g_Interval.a);

	//���_���W���A�����b�N
	g_pVtxBuffStageInterval->Unlock();
}

//=============================================================================
//		�t�F�[�h�̕`�揈��
//=============================================================================
void DrawStageInterval(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStageInterval, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,									//�v���~�e�B�u�̎��
		0,
		2);														//�v���~�e�B�u�̐�
}

//=============================================================================
//		�t�F�[�h�̐ݒ菈��
//=============================================================================
void SetStageInterval(GAMESTATE Nextstage)
{
	g_StageInterval = INTERVAL_OUT;
	g_Nextstage = Nextstage;
	g_Interval = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//=============================================================================
//		�t�F�[�h�̎擾����
//=============================================================================
INTERVAL GetStageInterval(void)
{
	return g_StageInterval;
}