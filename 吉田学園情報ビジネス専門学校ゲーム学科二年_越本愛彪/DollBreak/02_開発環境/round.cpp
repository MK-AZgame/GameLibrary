//========================================================
//
//	���E���h�̏���[round.cpp]
//	AUTHOR:�z�{���V
//
//========================================================
#include "main.h"
#include "round.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "enemy.h"
#include "player.h"
#include "time.h"
#include "meshfield.h"
#include <stdlib.h>
#include <time.h>

//�}�N����`
#define NUM_ROUND (1)											//���E���h�̌�
#define ROUND_INTERVALTIME (300)								//���E���h�Ԃ̃C���^�[�o���̎���
#define MAX_ROUND (5)											//���E���h�̍ő吔

//�O���[�o���ϐ�
LPDIRECT3DTEXTURE9 g_pTextureRound = NULL;						//���E���h�̃e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRound = NULL;					//���E���h�̒��_���ւ̃|�C���^
D3DXVECTOR3 g_posRound;											//���E���h�̈ʒu
Round g_Round;													//���E���h�̏����i�[
int g_roundOld;													//�ЂƂO�̃��E���h��ۑ�
float g_fPosZOld, g_fPosXOld;

//========================================================
//				���E���h�̏���������
//========================================================
void InitRound(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "./data/TEXTURE/number000.png", &g_pTextureRound);

	//�O���[�o���ϐ��̏�����
	g_posRound = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�ʒu�̏�����
	g_Round.nIntervalTime = ROUND_INTERVALTIME;					//�C���^�[�o���̎��Ԃ̐ݒ�
	g_Round.nNumRound = 1;										//�ŏ��̃��E���h�̐ݒ�
	g_Round.nState = ROUND_FIRST;	
	g_roundOld = ROUND_FIRST;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * (NUM_ROUND),
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRound,
		NULL);

	VERTEX_2D *pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRound->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntRound = 0; nCntRound < NUM_ROUND; nCntRound++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(1220.0f + (50.0f * nCntRound), 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(1270.0f + (50.0f * nCntRound), 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(1220.0f + (50.0f * nCntRound), 60.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(1270.0f + (50.0f * nCntRound), 60.0f, 0.0f);

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
	g_pVtxBuffRound->Unlock();

	//���E���h���P�ɐݒ�
	ChangeRound(ROUND_FIRST);
}

//========================================================
//				���E���h�̏I������
//========================================================
void UninitRound(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureRound != NULL)
	{
		g_pTextureRound->Release();
		g_pTextureRound = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRound != NULL)
	{
		g_pVtxBuffRound->Release();
		g_pVtxBuffRound = NULL;
	}
}

//========================================================
//				���E���h�̍X�V����
//========================================================
void UpdataRound(void)
{
	FADE fade = GetFade();
	GAMESTATE &pState = *GetGameState();

	//���݂̃C���^�[�o���ȊO�̃��E���h����ۑ�
	if (g_Round.nState != ROUND_INTERVAL)
	{
		g_roundOld = g_Round.nState;
	}

	//���E���h�Ԃ̃C���^�[�o��
	if (g_Round.nState == ROUND_INTERVAL)						
	{
		g_Round.nIntervalTime--;

		if (g_Round.nIntervalTime <= 0)
		{
			if (g_roundOld == ROUND_FIRST)
			{
				g_Round.nState = ROUND_SECOND;
				ChangeRound(ROUND_SECOND);
				//�C���^�[�o���̕b�����Đݒ�
				g_Round.nIntervalTime = ROUND_INTERVALTIME;
			}
			else if (g_roundOld == ROUND_SECOND)
			{
				g_Round.nState = ROUND_THIRD;
				ChangeRound(ROUND_THIRD);
				//�C���^�[�o���̕b�����Đݒ�
				g_Round.nIntervalTime = ROUND_INTERVALTIME;
			}
			else if (g_roundOld == ROUND_THIRD)
			{
				g_Round.nState = ROUND_FOURTH;
				ChangeRound(ROUND_FOURTH);
				//�C���^�[�o���̕b�����Đݒ�
				g_Round.nIntervalTime = ROUND_INTERVALTIME;
			}
			else if (g_roundOld == ROUND_FOURTH)
			{
				g_Round.nState = ROUND_FIFTH;
				ChangeRound(ROUND_FIFTH);
				//�C���^�[�o���̕b�����Đݒ�
				g_Round.nIntervalTime = ROUND_INTERVALTIME;
			}
		}
		else if (g_roundOld == ROUND_FIFTH)
		{
			if (fade == FADE_NONE)
			{
				pState = GAMESTATE_CLEAR;
				//SaveHighScore();

				//�ŏI�I�ȃ^�C����ۑ�
				StopTimer();

				//���U���g��ʂɑJ��
				SetFade(MODE_RESULT);
			}
		}
	}

}

//========================================================
//				���E���h�̕`�揈��
//========================================================
void DrawRound(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRound, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntRound = 0; nCntRound < NUM_ROUND; nCntRound++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureRound);

		//�|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_TRIANGLESTRIP,								//�v���~�e�B�u�̎��
			4 * nCntRound,
			2);													//�v���~�e�B�u�̐�	
	}

	//�e�N�X�`�������ɖ߂�
	pDevice->SetTexture(0,NULL);
}

//========================================================
//				���E���h�̐ݒ菈��
//========================================================
void SetRound()
{
	VERTEX_2D *pVtx;
	float aPosTexU[NUM_ROUND];									//�e���̐��l���i�[

	//aPosTexU[0] = ((g_Round.nNumRound % 100) / 10) * 0.1f;
	aPosTexU[0] = g_Round.nNumRound * 0.1f;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRound->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(0.0f + aPosTexU[0], 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + aPosTexU[0], 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + aPosTexU[0], 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + aPosTexU[0], 1.0f);

	//���_���W���A�����b�N
	g_pVtxBuffRound->Unlock();
}

//========================================================
//				���E���h�̏�Ԃ�؂�ւ���
//========================================================
void ChangeRound(ROUNDNUM nextRound)
{
	Player *pPlayer = GetPlayer();
	float fPosX, fPosZ;											//�G�̗N���ʒu�ݒ�p

	//���E���h��Ԃ̐؂�ւ��i�e���E���h�ł̓G�̐ݒ�j
	switch (nextRound)
	{
	case ROUND_FIRST:											//���E���h�P
		for (int nCntEnemyAppear = 0; nCntEnemyAppear < 5; nCntEnemyAppear++)
		{
			//�����_���Ȓl��ݒ�
			fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
			fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

			//�����ʒu�����Ԃ��Ă����ꍇ���炷
			while (1)
			{
				if (g_fPosZOld - ENEMY_SIZE < fPosZ + ENEMY_SIZE &&
					g_fPosZOld + ENEMY_SIZE > fPosZ - ENEMY_SIZE &&
					g_fPosXOld - ENEMY_SIZE < fPosX + ENEMY_SIZE &&
					g_fPosXOld + ENEMY_SIZE > fPosX - ENEMY_SIZE)
				{
					//�����_���Ȓl��ݒ�
					fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

					//�����ʒu���v���C���[�Ƌ߂������ꍇ�ɂ��炷
					if (pPlayer->pos.z - PLAYER_SIZE < fPosZ + ENEMY_SIZE &&
						pPlayer->pos.z + PLAYER_SIZE > fPosZ - ENEMY_SIZE &&
						pPlayer->pos.x - PLAYER_SIZE < fPosX + ENEMY_SIZE &&
						pPlayer->pos.x + PLAYER_SIZE > fPosX - ENEMY_SIZE)
					{
						fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
						fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					}
				}
				else
				{
					break;
				}
			}

			//����̕����ʒu��ۑ�
			g_fPosZOld = fPosZ; 
			g_fPosXOld = fPosX;

			//�G�l�~�[���Z�b�g�i�ʒu�E�̗́j
			SetEnemy(D3DXVECTOR3(fPosX, -50.0f, fPosZ), 2, 1);
		}

		//�\������郉�E���h�����Z�b�g
		SetRound();
		break;
	case ROUND_SECOND:											//���E���h�Q
		for (int nCntEnemyAppear = 0; nCntEnemyAppear < 8; nCntEnemyAppear++)
		{
			//�����_���Ȓl��ݒ�
			fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
			fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

			//�����ʒu�����Ԃ��Ă����ꍇ���炷
			while (1)
			{
				if (g_fPosZOld - ENEMY_SIZE < fPosZ + ENEMY_SIZE &&
					g_fPosZOld + ENEMY_SIZE > fPosZ - ENEMY_SIZE &&
					g_fPosXOld - ENEMY_SIZE < fPosX + ENEMY_SIZE &&
					g_fPosXOld + ENEMY_SIZE > fPosX - ENEMY_SIZE)
				{
					//�����_���Ȓl��ݒ�
					fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

					//�����ʒu���v���C���[�Ƌ߂������ꍇ�ɂ��炷
					if (pPlayer->pos.z - PLAYER_SIZE < fPosZ + ENEMY_SIZE &&
						pPlayer->pos.z + PLAYER_SIZE > fPosZ - ENEMY_SIZE &&
						pPlayer->pos.x - PLAYER_SIZE < fPosX + ENEMY_SIZE &&
						pPlayer->pos.x + PLAYER_SIZE > fPosX - ENEMY_SIZE)
					{
						fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
						fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					}
				}
				else
				{
					break;
				}
			}

			//�G�l�~�[���Z�b�g�i�ʒu�E�̗́j
			SetEnemy(D3DXVECTOR3(fPosX, -50.0f, fPosZ),4,1);
		}

		//���E���h�������Z
		g_Round.nNumRound++;

		//�\������郉�E���h�����Z�b�g
		SetRound();
		break;
	case ROUND_THIRD:											//���E���h�R
		for (int nCntEnemyAppear = 0; nCntEnemyAppear < 10; nCntEnemyAppear++)
		{
			//�����_���Ȓl��ݒ�
			fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
			fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

			//�����ʒu�����Ԃ��Ă����ꍇ���炷
			while (1)
			{
				if (g_fPosZOld - ENEMY_SIZE < fPosZ + ENEMY_SIZE &&
					g_fPosZOld + ENEMY_SIZE > fPosZ - ENEMY_SIZE &&
					g_fPosXOld - ENEMY_SIZE < fPosX + ENEMY_SIZE &&
					g_fPosXOld + ENEMY_SIZE > fPosX - ENEMY_SIZE)
				{
					//�����_���Ȓl��ݒ�
					fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

					//�����ʒu���v���C���[�Ƌ߂������ꍇ�ɂ��炷
					if (pPlayer->pos.z - PLAYER_SIZE < fPosZ + ENEMY_SIZE &&
						pPlayer->pos.z + PLAYER_SIZE > fPosZ - ENEMY_SIZE &&
						pPlayer->pos.x - PLAYER_SIZE < fPosX + ENEMY_SIZE &&
						pPlayer->pos.x + PLAYER_SIZE > fPosX - ENEMY_SIZE)
					{
						fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
						fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					}
				}
				else
				{
					break;
				}
			}

			//�G�l�~�[���Z�b�g�i�ʒu�E�̗́j
			SetEnemy(D3DXVECTOR3(fPosX, -50.0f, fPosZ),6,2);
		}

		//���E���h�������Z
		g_Round.nNumRound++;

		//�\������郉�E���h�����Z�b�g
		SetRound();
		break;
	case ROUND_FOURTH:											//���E���h�S
		for (int nCntEnemyAppear = 0; nCntEnemyAppear < 13; nCntEnemyAppear++)
		{
			//�����_���Ȓl��ݒ�
			fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
			fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

			//�����ʒu�����Ԃ��Ă����ꍇ���炷
			while (1)
			{
				if (g_fPosZOld - ENEMY_SIZE < fPosZ + ENEMY_SIZE &&
					g_fPosZOld + ENEMY_SIZE > fPosZ - ENEMY_SIZE &&
					g_fPosXOld - ENEMY_SIZE < fPosX + ENEMY_SIZE &&
					g_fPosXOld + ENEMY_SIZE > fPosX - ENEMY_SIZE)
				{
					//�����_���Ȓl��ݒ�
					fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

					//�����ʒu���v���C���[�Ƌ߂������ꍇ�ɂ��炷
					if (pPlayer->pos.z - PLAYER_SIZE < fPosZ + ENEMY_SIZE &&
						pPlayer->pos.z + PLAYER_SIZE > fPosZ - ENEMY_SIZE &&
						pPlayer->pos.x - PLAYER_SIZE < fPosX + ENEMY_SIZE &&
						pPlayer->pos.x + PLAYER_SIZE > fPosX - ENEMY_SIZE)
					{
						fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
						fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					}
				}
				else
				{
					break;
				}
			}

			//�G�l�~�[���Z�b�g�i�ʒu�E�̗́j
			SetEnemy(D3DXVECTOR3(fPosX, -50.0f, fPosZ),6,3);
		}

		//���E���h�������Z
		g_Round.nNumRound++;

		//�\������郉�E���h�����Z�b�g
		SetRound();
		break;
	case ROUND_FIFTH:											//���E���h�T
		for (int nCntEnemyAppear = 0; nCntEnemyAppear < 15; nCntEnemyAppear++)
		{
			//�����_���Ȓl��ݒ�
			fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
			fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

			//�����ʒu�����Ԃ��Ă����ꍇ���炷
			while (1)
			{
				if (g_fPosZOld - ENEMY_SIZE < fPosZ + ENEMY_SIZE &&
					g_fPosZOld + ENEMY_SIZE > fPosZ - ENEMY_SIZE &&
					g_fPosXOld - ENEMY_SIZE < fPosX + ENEMY_SIZE &&
					g_fPosXOld + ENEMY_SIZE > fPosX - ENEMY_SIZE)
				{
					//�����_���Ȓl��ݒ�
					fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;

					//�����ʒu���v���C���[�Ƌ߂������ꍇ�ɂ��炷
					if (pPlayer->pos.z - PLAYER_SIZE < fPosZ + ENEMY_SIZE &&
						pPlayer->pos.z + PLAYER_SIZE > fPosZ - ENEMY_SIZE &&
						pPlayer->pos.x - PLAYER_SIZE < fPosX + ENEMY_SIZE &&
						pPlayer->pos.x + PLAYER_SIZE > fPosX - ENEMY_SIZE)
					{
						fPosX = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
						fPosZ = rand() % (int)(MESHFIELD_SIZE - 1) * 2 - (MESHFIELD_SIZE / 2) * 2;
					}
				}
				else
				{
					break;
				}
			}

			//�G�l�~�[���Z�b�g�i�ʒu�E�̗́j
			SetEnemy(D3DXVECTOR3(fPosX, -50.0f, fPosZ),6,5);
		}

		//���E���h�������Z
		g_Round.nNumRound++;

		//�\������郉�E���h�����Z�b�g
		SetRound();
		break;
	}
}

//===============================================================================================
//									���E���h�̏����擾
//===============================================================================================
Round *GetRound()
{
	return &g_Round;
}