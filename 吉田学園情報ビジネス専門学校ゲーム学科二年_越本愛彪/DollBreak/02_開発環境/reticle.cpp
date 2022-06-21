//========================================================
//
//	���e�B�N���̏���[reticle.cpp]
//	AUTHOR:�z�{���V
//
//========================================================
#include "main.h"
#include "game.h"

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureReticle = NULL;						//���e�B�N���̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffReticle = NULL;					//���e�B�N���̒��_���ւ̃|�C���^
D3DXVECTOR3 g_posReticle;											//���e�B�N���̈ʒu

//========================================================
//			���e�B�N���̏���������
//========================================================
void InitReticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/reticle.png", &g_pTextureReticle);

	//�O���[�o���ϐ��̏�����
	g_posReticle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�ʒu�̏�����

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffReticle,
		NULL);

	VERTEX_2D *pVtx;												//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffReticle->Lock(0, 0, (void**)&pVtx, 0);

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

	//���_���W���A�����b�N
	g_pVtxBuffReticle->Unlock();
}

//========================================================
//			���e�B�N���̏I������
//========================================================
void UninitReticle(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureReticle != NULL)
	{
		g_pTextureReticle->Release();
		g_pTextureReticle = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffReticle != NULL)
	{
		g_pVtxBuffReticle->Release();
		g_pVtxBuffReticle = NULL;
	}
}

//========================================================
//			���e�B�N���̍X�V����
//========================================================
void UpdateReticle(void)
{
}

//========================================================
//			���e�B�N���̕`�揈��
//========================================================
void DrawReticle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffReticle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureReticle);

	//�|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,										//�v���~�e�B�u�̎��
		0,
		2);															//�v���~�e�B�u�̐�	

	//�e�N�X�`���̕���
	pDevice->SetTexture(0, NULL);
}