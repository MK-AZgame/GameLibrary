//========================================================
//
//	�|�[�Y����[pause.cpp]
//	AUTHOR:�z�{���V
//
//========================================================
#include "main.h"
#include "pause.h"
#include "input.h"
#include "game.h"
#include "fade.h"
#include "sound.h"
#include <Windows.h>

//�}�N����`	
#define MAX_TEX (4)

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTexturePause[MAX_TEX] = {};				//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;					//���_�o�b�t�@�ւ̃|�C���^
int g_nFlug;

//========================================================
//			�|�[�Y�̏���������
//========================================================
void InitPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/pause100.png", &g_pTexturePause[0]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/pause000.png", &g_pTexturePause[1]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/pause001.png", &g_pTexturePause[2]);
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/pause002.png", &g_pTexturePause[3]);

	g_nFlug = 0;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPause, NULL);

	VERTEX_2D *pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(200.0f, 100.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(1080.0f, 100.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(200.0f, 620.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(1080.0f, 620.0f, 0.0f);

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

	//[CONTINUE]
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(300.0f, 150.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(980.0f, 150.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(300.0f, 270.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(980.0f, 270.0f, 0.0f);

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

	//[RETRY]
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(980.0f, 300.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(300.0f, 420.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(980.0f, 420.0f, 0.0f);

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
	//[QUIT]
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(300.0f, 450.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(980.0f, 450.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(300.0f, 570.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(980.0f, 570.0f, 0.0f);

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
	g_pVtxBuffPause->Unlock();
}

//========================================================
//			�|�[�Y�̏I������
//========================================================
void UninitPause(void)
{
	int nCount;

	//�e�N�X�`���̔j��
	for (nCount = 0; nCount < MAX_TEX; nCount++)
	{
		if (g_pTexturePause[nCount] != NULL)
		{
			g_pTexturePause[nCount]->Release();
			g_pTexturePause[nCount] = NULL;
		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}
}

//========================================================
//			�|�[�Y�̍X�V����
//========================================================
void UpdatePause(void)
{
	VERTEX_2D *pVtx;
	GAMESTATE gamestate = *GetGameState();
	PAUSE *pause = GetPause();
	FADE fade = GetFade();
	POINT mousePos;

	//�}�E�X�̈ʒu���擾
	GetCursorPos(&mousePos);

	//ShowCursor(TRUE);

	//�I�����̈ړ�
	if (pause->bDisp == true)
	{
		if (mousePos.x > 300.0f&&mousePos.x < 980.0f&&
			mousePos.y > 150.0f&&mousePos.y < 270.0f)
		{
			g_nFlug = 0;
		}
		else if (mousePos.x > 300.0f&&mousePos.x < 980.0f&&
				mousePos.y > 300.0f&&mousePos.y < 420.0f)
		{
			g_nFlug = 1;
		}
		else if (mousePos.x > 300.0f&&mousePos.x < 980.0f&&
			mousePos.y > 450.0f&&mousePos.y < 570.0f)
		{
			g_nFlug = 2;
		}

		//�I��
		if (fade == FADE_NONE)
		{
			if (GetMouseTrigger(0))
			{
				PlaySound(SOUND_LABEL_SE_DECISION);

				if (g_nFlug == 0)
				{
					pause->bDisp = false;
				}
				else if (g_nFlug == 1)
				{
					SetFade(MODE_GAME);
				}
				else if (g_nFlug == 2)
				{
					SetFade(MODE_TITLE);
				}
			}
		}
	}

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//�I������Ă���ꏊ�̐F�ύX
	for (int nCount = 0; nCount < 3; nCount++)
	{
		pVtx += 4;
		if (nCount == g_nFlug)
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		else
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
		}
	}

	//���_���W���A�����b�N
	g_pVtxBuffPause->Unlock();
}

//========================================================
//			�|�[�Y�̕`�揈��
//========================================================
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	PAUSE *pause = GetPause();
	int nCount;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCount = 0; nCount < MAX_TEX; nCount++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePause[nCount]);

		if (pause->bDisp == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,									//�v���~�e�B�u�̎��
				4 * nCount,
				2);														//�v���~�e�B�u�̐�	
		}
	}
	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

}