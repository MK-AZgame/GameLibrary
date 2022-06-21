//========================================================
//
//	�c�e���̏���[remainingbullet.cpp]
//	AUTHOR:�z�{���V
//
//========================================================
#include "main.h"
#include "bullet.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "enemy.h"

//�}�N����`
#define NUM_REMAIN (2)												//�c�e���̌�

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureRemain = NULL;							//�c�e���̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRemain = NULL;					//�c�e���̒��_���ւ̃|�C���^
D3DXVECTOR3 g_posRemain;											//�c�e���̈ʒu

//========================================================
//			�c�e���̏���������
//========================================================
void InitRemain(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/number000.png", &g_pTextureRemain);

	//�O���[�o���ϐ��̏�����
	g_posRemain = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�ʒu�̏�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_REMAIN,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRemain,
		NULL);

	VERTEX_2D *pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRemain->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRemain = 0; nCntRemain < NUM_REMAIN; nCntRemain++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(0.0f + (50.0f * nCntRemain), 660.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(50.0f + (50.0f * nCntRemain), 660.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f + (50.0f * nCntRemain), 720.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(50.0f + (50.0f * nCntRemain), 720.0f, 0.0f);

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
	g_pVtxBuffRemain->Unlock();
}

//========================================================
//			�c�e���̏I������
//========================================================
void UninitRemain(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureRemain != NULL)
	{
		g_pTextureRemain->Release();
		g_pTextureRemain = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRemain != NULL)
	{
		g_pVtxBuffRemain->Release();
		g_pVtxBuffRemain = NULL;
	}
}

//========================================================
//			�c�e���̍X�V����
//========================================================
void UpdateRemain(void)
{

}

//========================================================
//			�c�e���̕`�揈��
//========================================================
void DrawRemain(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRemain, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntRemain = 0; nCntRemain < NUM_REMAIN; nCntRemain++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRemain);

		//�|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,								//�v���~�e�B�u�̎��
			4 * nCntRemain,
			2);													//�v���~�e�B�u�̐�	
	}
}

//========================================================
//			�c�e���̐ݒ菈��
//========================================================
void SetRemain()
{
	VERTEX_2D *pVtx;
	float aPosTexU[NUM_REMAIN];									//�e���̐��l���i�[
	int remainingBullet = GetBullet();							//�e�̏����擾

	aPosTexU[0] = ((remainingBullet % 100) / 10) * 0.1f;
	aPosTexU[1] = (remainingBullet % 10) * 0.1f;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRemain->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRemain = 0; nCntRemain < NUM_REMAIN; nCntRemain++)
	{
		pVtx[0].tex = D3DXVECTOR2(0.0f + aPosTexU[nCntRemain], 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + aPosTexU[nCntRemain], 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + aPosTexU[nCntRemain], 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + aPosTexU[nCntRemain], 1.0f);

		pVtx += 4;
	}

	//���_���W���A�����b�N
	g_pVtxBuffRemain->Unlock();
}