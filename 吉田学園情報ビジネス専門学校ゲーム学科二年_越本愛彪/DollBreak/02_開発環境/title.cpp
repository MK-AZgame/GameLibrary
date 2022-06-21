//========================================================
//
//	�^�C�g���̏���[title.cpp]
//	AUTHOR:�z�{���V
//
//========================================================
#include "main.h"
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include <Windows.h>

//�}�N����`
#define NUM_TITLETEXTURE (2)								//�^�C�g���̃e�N�X�`����
#define NUM_TITLEMENU (2)									//�^�C�g���̃��j���[�̐�
#define NUM_TITLEALL (NUM_TITLETEXTURE + NUM_TITLEMENU)		//�^�C�g���Ŏg�p����e�N�X�`���̑���

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureTitle[NUM_TITLEALL] = {};		//�^�C�g���̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;				//�^�C�g���̒��_���ւ̃|�C���^

//========================================================
//					�^�C�g���̏���������
//========================================================
void InitTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/title.jpeg", &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/title.png", &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/title_start.png", &g_pTextureTitle[2]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/title_tutorial.png", &g_pTextureTitle[3]);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_TITLEALL,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffTitle,
		NULL);

	VERTEX_2D *pVtx;												//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	//�^�C�g���E�^�C�g���w�i�̃e�N�X�`��
	for (int nCntTitle = 0; nCntTitle < NUM_TITLETEXTURE; nCntTitle++)
	{
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

		pVtx += 4;
	}

	//�^�C�g�������j���[�̃e�N�X�`��
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(540.0f, 400.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(740.0f, 400.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(540.0f, 500.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(740.0f, 500.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtx += 4;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(540.0f, 520.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(740.0f, 520.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(540.0f, 620.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(740.0f, 620.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_���W���A�����b�N
	g_pVtxBuffTitle->Unlock();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_TITLE);
}

//========================================================
//				�^�C�g���̏I������
//========================================================
void UninitTitle(void)
{
	for (int nCount = 0; nCount < NUM_TITLEALL; nCount++)
	{
		//�e�N�X�`���̔j��
		if (g_pTextureTitle[nCount] != NULL)
		{
			g_pTextureTitle[nCount]->Release();
			g_pTextureTitle[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	//�T�E���h�̒�~
	StopSound();
}

//========================================================
//				�^�C�g���̍X�V����
//========================================================
void UpdateTitle(void)
{
	VERTEX_2D *pVtx;												//���_���ւ̃|�C���^
	FADE fade = GetFade();
	POINT mousePos;

	//�}�E�X�̈ʒu���擾
	GetCursorPos(&mousePos);

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 8;

	if (mousePos.x > 540.0f&&mousePos.x < 740.0f
		&&mousePos.y > 400.0f&&mousePos.y < 500.0f)
	{//�}�E�X�J�[�\�����h�X�^�[�g�h�̈ʒu�ɂ���Ƃ�
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (GetMouseTrigger(0))
		{
			PlaySound(SOUND_LABEL_SE_DECISION);

			SetFade(MODE_GAME);
		}
	}
	else
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	}

	pVtx += 4;

	if (mousePos.x > 540.0f&&mousePos.x < 740.0f
		&&mousePos.y > 520.0f&&mousePos.y < 620.0f)
	{//�}�E�X�J�[�\�����h�V�ѕ��h�̈ʒu�ɂ���Ƃ�
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		if (GetMouseTrigger(0))
		{
			PlaySound(SOUND_LABEL_SE_DECISION);

			SetFade(MODE_TUTORIAL);
		}
	}
	else
	{
		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
	}

	//���_���W���A�����b�N
	g_pVtxBuffTitle->Unlock();
}

//========================================================
//				�^�C�g���̕`�揈��
//========================================================
void DrawTitle(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCount = 0; nCount < NUM_TITLEALL; nCount++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCount]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,									//�v���~�e�B�u�̎��
			4 * nCount,
			2);														//�v���~�e�B�u�̐�
	}

	//�e�N�X�`�������ɖ߂�
	pDevice->SetTexture(0, NULL);
}