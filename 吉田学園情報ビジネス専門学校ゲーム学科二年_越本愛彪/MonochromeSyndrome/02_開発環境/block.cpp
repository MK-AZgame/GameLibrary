//=============================================================================
//
//	�u���b�N�����̏���[block.cpp]
//	Author�F�z�{���V
//
//=============================================================================
#include <stdio.h>
#include "main.h"
#include "input.h"
#include "player.h"
#include "block.h"
#include "goal.h"
#include "sound.h"

//�}�N����`
#define MAX_BLOCK_WIDTH (30)								//�u���b�N��X�����̍ő吔
#define MAX_BLOCK_HEIGHT (20)								//�u���b�N��T�����̍ő吔
#define MAX_BLOCK  (MAX_BLOCK_WIDTH * MAX_BLOCK_HEIGHT)		//�u���b�N�̍ő吔
#define BLOCK_SIZE (SCREEN_HEIGHT / MAX_BLOCK_HEIGHT)		//�u���b�N�̃T�C�Y

//�u���b�N�\���̂̒�`
typedef struct
{
	D3DXVECTOR3 pos;										//�ʒu
	D3DXVECTOR3 posOld;										//�O��̈ʒu
	D3DXVECTOR3 move;										//�ړ���
	float fWidth;											//��
	float fHeight;											//����
	BLOCK_TYPE Type;										//���
	bool bUse;												//�g�p���Ă��邩�ǂ���
}BLOCK;

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureblock = NULL;					//�e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffblock = NULL;				//���_�o�b�t�@�ւ̃|�C���^
BLOCK g_aBlock[MAX_BLOCK];									//�u���b�N�̏��
int g_nBlock[MAX_BLOCK_HEIGHT][MAX_BLOCK_WIDTH];			//�u���b�N�̔z�u���

//=============================================================================
//		�u���b�N�̏���������
//=============================================================================
void InitBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�u���b�N�̏��̏�����
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu�̏�����
		g_aBlock[nCntBlock].posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�O��̈ʒu�̏�����
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏�����
		g_aBlock[nCntBlock].fWidth = 0.0f;								//�u���b�N�̉����̏�����						
		g_aBlock[nCntBlock].fHeight = 0.0f;								//�u���b�N�̍����̏�����
		g_aBlock[nCntBlock].Type = BLOCK_NONE;							//�u���b�N�̎�ނ̏�����
		g_aBlock[nCntBlock].bUse = false;								//�u���b�N���g���Ă��Ȃ���Ԃɂ���
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffblock, NULL);

	VERTEX_2D *pVtx;													//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffblock->Lock(0, 0, (void**)&pVtx, 0);

	//MAX_BLOCK���u���b�N�̏���������
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - BLOCK_SIZE / 2, g_aBlock[nCntBlock].pos.y - BLOCK_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + BLOCK_SIZE / 2, g_aBlock[nCntBlock].pos.y - BLOCK_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - BLOCK_SIZE / 2, g_aBlock[nCntBlock].pos.y + BLOCK_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + BLOCK_SIZE / 2, g_aBlock[nCntBlock].pos.y + BLOCK_SIZE, 0.0f);

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

		pVtx += 4;
	}

	//���_���W���A�����b
	g_pVtxBuffblock->Unlock();
}

//=============================================================================
//		�u���b�N�̏I������
//=============================================================================
void UninitBlock(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureblock != NULL)
	{
		g_pTextureblock->Release();
		g_pTextureblock = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffblock != NULL)
	{
		g_pVtxBuffblock->Release();
		g_pVtxBuffblock = NULL;
	}
}

//=============================================================================
//		�u���b�N�̍X�V����
//=============================================================================
void UpdataBlock(void)
{
	VERTEX_2D *pVtx;
	Player *pPlayer = GetPlayer();

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffblock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//�g�p����Ă���ꍇ
			if (pPlayer->pos.x >= SCREEN_WIDTH / 2)
			{
				ScrollBlock(D3DXVECTOR3(pPlayer->move.x, 0.0f, 0.0f),nCntBlock);
			}

			if (g_aBlock[nCntBlock].Type == BLOCK_MOVE)
			{//BLOCK_TYPE �� BLOCK_MOVE�̎�
				//posOld �� pos ��ۑ�
				g_aBlock[nCntBlock].posOld = g_aBlock[nCntBlock].pos;

				//�ړ��ʂ��X�V
				g_aBlock[nCntBlock].pos += g_aBlock[nCntBlock].move;

				//�����蔻��
				CollisionPlayer(&g_aBlock[nCntBlock].pos, &g_aBlock[nCntBlock].posOld, &g_aBlock[nCntBlock].move, 
					g_aBlock[nCntBlock].fWidth, g_aBlock[nCntBlock].fHeight);

				//���_���W�̐ݒ�
				pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2, g_aBlock[nCntBlock].pos.y - BLOCK_SIZE / 2, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2, g_aBlock[nCntBlock].pos.y - BLOCK_SIZE / 2, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2, g_aBlock[nCntBlock].pos.y + BLOCK_SIZE / 2, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2, g_aBlock[nCntBlock].pos.y + BLOCK_SIZE / 2, 0.0f);

				//�u���b�N�̃��[�v
				if (g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight / 2 <= 0.0f)
				{//��ʏ㕔�ɓ��B��
					g_aBlock[nCntBlock].pos.y = SCREEN_HEIGHT + g_aBlock[nCntBlock].fHeight / 2;
				}
				else if (g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2 >= SCREEN_HEIGHT)
				{//��ʉ����ɓ��B��
					g_aBlock[nCntBlock].pos.y = 0.0f - g_aBlock[nCntBlock].fHeight / 2;
				}
			}
		}
		pVtx += 4;
	}
	//���_���W���A�����b�N
	g_pVtxBuffblock->Unlock();
}

//=============================================================================
//		�u���b�N�̕`�揈��
//=============================================================================
void DrawBlock(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffblock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureblock);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//bUse��true�̎�
			//�|���S���̕`��
			pDevice->DrawPrimitive(
				D3DPT_TRIANGLESTRIP,				//�v���~�e�B�u�̎��
				4 * nCntBlock,
				2);									//�v���~�e�B�u�̐�	
		}
	}
}

//=============================================================================
//		�u���b�N�̐ݒ菈��
//=============================================================================
void SetBlock(D3DXVECTOR3 pos,float fWidth, D3DXVECTOR3 move,BLOCK_TYPE block)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffblock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == false)
		{
			//�u���b�N�̊e���̐ݒ�
			g_aBlock[nCntBlock].pos = pos;
			g_aBlock[nCntBlock].move = move;
			g_aBlock[nCntBlock].fHeight = BLOCK_SIZE;
			g_aBlock[nCntBlock].fWidth = fWidth;
			g_aBlock[nCntBlock].Type = block;

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth / 2, g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth / 2, g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - fWidth / 2, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight / 2, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + fWidth / 2, g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight / 2, 0.0f);

			if (g_aBlock[nCntBlock].Type == BLOCK_NORMAL)
			{//�ʏ�̃u���b�N�̐F�ݒ�
				//���_�J���[�̐ݒ�
				pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
				pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
				pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
				pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
			}

			//�e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(fWidth / (BLOCK_SIZE / 2), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(fWidth / (BLOCK_SIZE / 2), 1.0f);

			//�g�p���Ă����ԂɕύX
			g_aBlock[nCntBlock].bUse = true;
			break;
		}
		pVtx += 4;
	}

	//���_���W���A�����b�N
	g_pVtxBuffblock->Unlock();
}

//=============================================================================
//		�u���b�N�̓����蔻��
//=============================================================================
bool ColisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight)
{
	bool bIsLanding = false;											//���n���Ă��邩�ǂ���

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{//�g�p����Ă���Ƃ�
				//�u���b�N�ƃv���C���[�̓����蔻��
				//�ォ�牺
			if (pPosOld->y <= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2 &&
				pPos->y >= g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2 &&
				pPos->x + fWidth / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2 &&
				pPos->x - fWidth / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2)
			{
				bIsLanding = true;									//���n���Ă����Ԃɂ���
				pPos->y = g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2;
				pMove->y = 0;
				if (g_aBlock[nCntBlock].Type == BLOCK_MOVE)
				{//�����u���b�N�̈ړ��ʂ̍X�V
					pPos->x += g_aBlock[nCntBlock].move.x;
					pPos->y += g_aBlock[nCntBlock].move.y;
				}
			}
			if (pPosOld->y - fHeight >= g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight / 2 &&
				pPos->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight / 2 &&
				pPos->x + fWidth / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2 &&
				pPos->x - fWidth / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2)
			{//�������
				pPos->y = g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight / 2 + fHeight;
				pMove->y = 1;
			}

			if (pPosOld->y > g_aBlock[nCntBlock].pos.y - g_aBlock[nCntBlock].fHeight / 2 &&
				pPosOld->y - fHeight < g_aBlock[nCntBlock].pos.y + g_aBlock[nCntBlock].fHeight / 2)
			{
				//������E
				if (pPosOld->x + fWidth / 2 <= g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2 &&
					pPos->x + fWidth / 2 > g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2)
				{
					pPos->x = g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2 - fWidth / 2;
					pMove->x = 0;
				}

				//�E���獶
				if (pPosOld->x - fWidth / 2 >= g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2 &&
					pPos->x - fWidth / 2 < g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2)
				{
					pPos->x = g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2 + fWidth / 2;
					pMove->x = 0;
				}
			}
		}
	}
	return bIsLanding;
}

//=============================================================================
//		�u���b�N�̃X�N���[������
//=============================================================================
void ScrollBlock(D3DXVECTOR3 move,int nCntBlock)
{
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffblock->Lock(0, 0, (void**)&pVtx, 0);

	if (g_aBlock[nCntBlock].bUse == true)
	{
		g_aBlock[nCntBlock].pos -= move;
	}

	pVtx += 4 * nCntBlock;

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2, g_aBlock[nCntBlock].pos.y - BLOCK_SIZE / 2, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2, g_aBlock[nCntBlock].pos.y - BLOCK_SIZE / 2, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x - g_aBlock[nCntBlock].fWidth / 2, g_aBlock[nCntBlock].pos.y + BLOCK_SIZE / 2, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aBlock[nCntBlock].pos.x + g_aBlock[nCntBlock].fWidth / 2, g_aBlock[nCntBlock].pos.y + BLOCK_SIZE / 2, 0.0f);

	//�A�����b�N
	g_pVtxBuffblock->Unlock();
}

//=============================================================================
//		�t�@�C���̓ǂݍ���
//=============================================================================
void ScanFile(char *pfilename)
{
	FILE *fp;															//�t�@�C���|�C���^

	//�t�@�C�����J��
	fp = fopen(pfilename, "r");

	if (fp != NULL)
	{//����
		for (int nCntBlockHeight = 0; nCntBlockHeight < MAX_BLOCK_HEIGHT; nCntBlockHeight++)
		{
			for (int nCntBlockWidth = 0; nCntBlockWidth < MAX_BLOCK_WIDTH; nCntBlockWidth++)
			{//�t�@�C���ǂݍ���
				fscanf(fp, "%d", &g_nBlock[nCntBlockHeight][nCntBlockWidth]);
			}
		}
		//�t�@�C�������
		fclose(fp);
	}
	else
	{//���s
	}

	//�e��u���b�N���ƂɃ}�b�v�𐶐�
	for (int nCntBlockHeight = 0; nCntBlockHeight < MAX_BLOCK_HEIGHT; nCntBlockHeight++)
	{
		for (int nCntBlockWidth = 0; nCntBlockWidth < MAX_BLOCK_WIDTH; nCntBlockWidth++)
		{
			if (g_nBlock[nCntBlockHeight][nCntBlockWidth] == 1)
			{//�ʏ�u���b�N�̐���
				SetBlock(D3DXVECTOR3(nCntBlockWidth * BLOCK_SIZE + (BLOCK_SIZE / 2.0f), nCntBlockHeight * BLOCK_SIZE + (BLOCK_SIZE / 2.0f), 0.0f), BLOCK_SIZE, D3DXVECTOR3(0.0f, 0.0f, 0.0f), BLOCK_NORMAL);
			}
			else if (g_nBlock[nCntBlockHeight][nCntBlockWidth] == 2)
			{//�����u���b�N(��ړ�)�̐���
				SetBlock(D3DXVECTOR3(nCntBlockWidth * BLOCK_SIZE + (BLOCK_SIZE / 2.0f), nCntBlockHeight * BLOCK_SIZE + (BLOCK_SIZE / 2.0f), 0.0f), BLOCK_SIZE, D3DXVECTOR3(0.0f, -1.0f, 0.0f), BLOCK_MOVE);
			}
			else if (g_nBlock[nCntBlockHeight][nCntBlockWidth] == 3)
			{//�����u���b�N(���ړ�)�̐���
				SetBlock(D3DXVECTOR3(nCntBlockWidth * BLOCK_SIZE + (BLOCK_SIZE / 2.0f), nCntBlockHeight * BLOCK_SIZE + (BLOCK_SIZE / 2.0f), 0.0f), BLOCK_SIZE, D3DXVECTOR3(0.0f, 1.0f, 0.0f), BLOCK_MOVE);
			}
			else if (g_nBlock[nCntBlockHeight][nCntBlockWidth] == 99)
			{//�S�[���̐���

			}
		}
	}
}