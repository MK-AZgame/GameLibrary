//=============================================================================
//
// �v���C���[�̗͂̏��� [playerlife.cpp]
// Author : �z�{�@���V
//
//=============================================================================
#include "main.h"
#include "timer.h"
#include "game.h"
#include "result.h"
#include "player.h"

//�}�N����`
#define NUM_PLAYERLIFE (2)												//�v���C���[���C�t�̌�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePlayerLife = NULL;							//�v���C���[���C�t�̃e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayerLife = NULL;					//�v���C���[���C�t�̒��_���̃|�C���^
D3DXVECTOR3 g_posPlayerLife;											//�v���C���[���C�t�̈ʒu
int g_nPlayerLife;														//�v���C���[���C�t�̒l

//=============================================================================
//		�v���C���[���C�t�̏���������
//=============================================================================
void InitPlayerLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/playerlife.png", &g_pTexturePlayerLife);

	g_posPlayerLife = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�ʒu�̏�����
	g_nPlayerLife = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_PLAYERLIFE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPlayerLife, NULL);

	VERTEX_2D *pVtx;													//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayerLife->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPlayerLife = 0; nCntPlayerLife < NUM_PLAYERLIFE; nCntPlayerLife++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f + (50.0f * nCntPlayerLife), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f + (50.0f * nCntPlayerLife), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(.0f + (50.0f * nCntPlayerLife), 50.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f + (50.0f * nCntPlayerLife), 50.0f, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);

		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}

	//���_���W���A�����b�N
	g_pVtxBuffPlayerLife->Unlock();
}

//=============================================================================
//		�v���C���[���C�t�̏I������
//=============================================================================
void UninitPlayerLife(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayerLife != NULL)
	{
		g_pTexturePlayerLife->Release();
		g_pTexturePlayerLife = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayerLife != NULL)
	{
		g_pVtxBuffPlayerLife->Release();
		g_pVtxBuffPlayerLife = NULL;
	}
}

//=============================================================================
//		�v���C���[���C�t�̍X�V����
//=============================================================================
void UpdataPlayerLife(void)
{
	
}

//=============================================================================
//		�v���C���[���C�t�̕`�揈��
//=============================================================================
void DrawPlayerLife(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	Player *pPlayer = GetPlayer();

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayerLife, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntPlayerLife = 0; nCntPlayerLife < pPlayer->nLife; nCntPlayerLife++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePlayerLife);

		//�|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,									//�v���~�e�B�u�̎��
			4 * nCntPlayerLife,
			2);														//�v���~�e�B�u�̐�	
	}
}