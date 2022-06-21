//=============================================================================
//
// �w�i�̏��� [bg.cpp]
// Author : �z�{�@���V
//
//=============================================================================
#include "main.h"
#include "Bg.h"
#include "player.h"

//�}�N����`
#define NUM_BG (2)								//�w�i�̃e�N�X�`����

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureBg[NUM_BG] = {};	//�w�i�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;	//���_�o�b�t�@�̃|�C���^
float g_PosTexX;								//�w�i���W�̒��J�n�ʒu(X)
float g_PosTexY;								//�w�i���W�̒��J�n�ʒu(Y)

//=============================================================================
//			�w�i�̏���������
//=============================================================================
void InitBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	g_PosTexX = 0;
	g_PosTexY = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_BG, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBg, NULL);

	VERTEX_2D *pVtx;							//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

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
	pVtx[0].tex = D3DXVECTOR2(g_PosTexX, g_PosTexY);
	pVtx[1].tex = D3DXVECTOR2(g_PosTexX + 0.01f, g_PosTexY);
	pVtx[2].tex = D3DXVECTOR2(g_PosTexX, g_PosTexY + 0.01f);
	pVtx[3].tex = D3DXVECTOR2(g_PosTexX + 0.01f, g_PosTexY + 0.01f);

	pVtx += 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1340.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 720.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1340.0f, 720.0f, 0.0f);

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
	pVtx[0].tex = D3DXVECTOR2(0.0f,0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f,0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f,1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f,1.0f);

	//���_���W���A�����b�N
	g_pVtxBuffBg->Unlock();
}

//=============================================================================
//			�w�i�̏I������
//=============================================================================
void UninitBg(void)
{
	for (int nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureBg[nCntBg] != NULL)
		{
			g_pTextureBg[nCntBg]->Release();
			g_pTextureBg[nCntBg] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}
}

//=============================================================================
//			�w�i�̍X�V����
//=============================================================================
void UpdataBg(void)
{
	VERTEX_2D *pVtx;

	g_PosTexX += 0.00001f;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(g_PosTexX, g_PosTexY);
	pVtx[1].tex = D3DXVECTOR2(g_PosTexX + 0.3f, g_PosTexY);
	pVtx[2].tex = D3DXVECTOR2(g_PosTexX, g_PosTexY + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(g_PosTexX + 0.3f, g_PosTexY + 1.0f);

	//���_���W���A�����b�N
	g_pVtxBuffBg->Unlock();
}

//=============================================================================
//			�w�i�̕`�揈��
//=============================================================================
void DrawBg(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBg, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBg = 0; nCntBg < NUM_BG; nCntBg++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBg[nCntBg]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
			4 * nCntBg,
			2);								//�v���~�e�B�u�̐�		
	}
}