//========================================================
//
//	�v���C���[���f���̏���[player.cpp]
//	AUTHOR:�z�{���V
//
//========================================================
#include <stdio.h>
#include "player.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "meshfield.h"
#include "model.h"
#include "loadfileh.h"
#include "fade.h"
#include "game.h"
#include "sound.h"

//�}�N����`
#define PLAYER_MOVE (1.0f)								//�v���C���[�̈ړ���
#define PLAYER_ROTSPEED (0.1f)							//�v���C���[�̉�]�̌�����
#define ROT_PLAYERVIEW (0.075f)							//�v���C���[�̉�]�ɔ����J�����̉�]��
#define NUM_PLAYERPARTS (4)								//�v���C���[���\������p�[�c�̐�

//�O���[�o���ϐ�
int g_nIdxShadow;										//�e�̃C���f�b�N�X
Player g_player;										//�v���C���[�̏����i�[
ModelParts g_ModelParts[NUM_PLAYERPARTS];				//���f���p�[�c�̍\����
int g_nBulletInterval;									//���̒e�����܂ł̃C���^�[�o��

//========================================================
//					�v���C���[����������
//========================================================
void InitPlayer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�t�@�C���ǂݍ���
	LoadMotionFile("data/motion.txt",&g_ModelParts[0]);

	//�e���̏�����
	g_player.pos = D3DXVECTOR3(-120.0f, 20.0f, 0.0f);	//�ʒu�̏�����
	g_player.rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);		//�����̏�����
	g_player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏�����
	g_player.State = PLAYERSTATE_NORMAL;				//�v���C���[�̏�Ԃ��h�ʏ�h�ɐݒ�
	g_player.nLife = 10;								//�̗͂�������
	g_nBulletInterval = 5;								//�e���˂̃C���^�[�o���̏�����				

	//�p�[�c�̐e�ԍ��̐ݒ�
	g_ModelParts[0].ParentIdx = -1;						//����
	g_ModelParts[1].ParentIdx = 0;						//��
	g_ModelParts[2].ParentIdx = 0;						//�r�i���j
	g_ModelParts[3].ParentIdx = 0;						//�r�i�E�j

	g_ModelParts[1].pos.y = 4.0f;

	g_player.rotDest.y = 0;								//�ړI�̊p�x�̏�����

	//�e�̐ݒ�
	g_nIdxShadow = SetShadow(D3DXVECTOR3(g_player.pos.x, 0.1f, g_player.pos.z), g_player.rot);
}

//========================================================
//					�v���C���[�I������
//========================================================
void UninitPlayer(void)
{
	//���b�V���̔j��
	if (g_ModelParts[0].pMesh != NULL)
	{
		g_ModelParts[0].pMesh->Release();
		g_ModelParts[0].pMesh = NULL;
	}

	//�}�e���A���̔j��
	if (g_ModelParts[0].pBuffMat != NULL)
	{
		g_ModelParts[0].pBuffMat->Release();
		g_ModelParts[0].pBuffMat = NULL;
	}
}

//========================================================
//					�v���C���[�X�V����
//========================================================
void UpdatePlayer(void)
{
	Camera *pCamera = GetCamera();

	//�e�̔���
	if (g_player.State == PLAYERSTATE_NORMAL)
	{
		if (GetMousePress(0))
		{
			g_nBulletInterval--;

			if (g_nBulletInterval <= 0)
			{
				SetBullet(D3DXVECTOR3(g_player.pos.x,g_player.pos.y - 5.0f,g_player.pos.z), D3DXVECTOR3(-sinf(g_player.rot.y), tanf(g_player.rot.x), -cosf(g_player.rot.y)));

				g_nBulletInterval = 10;
			}
		}

		//�e�������[�h����
		if (GetKeyboardTrigger(DIK_R))
		{
			g_player.State = PLAYERSTATE_RELOAD;
			PlaySound(SOUND_LABEL_RELOAD);
		}
	}

	//�v���C���[�ɂ�����d��
	g_player.move.y--;

	//posOld�Ɍ��݂̈ʒu��ۑ�
	g_player.posOld = g_player.pos;

	//�}�E�X�̈ړ��ʂ��擾
	D3DXVECTOR3 mouseMove = GetMouseMove();

	//�ړ��ʂ��m�[�}���C�Y
	D3DXVec3Normalize(&mouseMove, &mouseMove);

	g_player.rotDest.y += mouseMove.x / 25.0f;
	pCamera->rotDest.y += mouseMove.x / 25.0f;

	//�v���C���[�̈ړ�
	if (GetKeyboardPress(DIK_W))
	{//�����L�[�̏オ�����ꂽ
		if (GetKeyboardPress(DIK_D))
		{//�E�΂�
			g_player.move.x += sinf(pCamera->rot.y + (D3DX_PI * 0.25f)) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y + (D3DX_PI * 0.25f)) * PLAYER_MOVE;
		}
		else if (GetKeyboardPress(DIK_A))
		{//���΂�
			g_player.move.x += sinf(pCamera->rot.y + (D3DX_PI * -0.25f)) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y + (D3DX_PI * -0.25f)) * PLAYER_MOVE;
		}
		else if (GetKeyboardPress(DIK_LSHIFT))
		{
			g_player.move.x += sinf(pCamera->rot.y) * (PLAYER_MOVE + 1.0f);
			g_player.move.z += cosf(pCamera->rot.y) * (PLAYER_MOVE + 1.0f);
			g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI));
		}
		else
		{//�O
			g_player.move.x += sinf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI));
		}
	}
	else if (GetKeyboardPress(DIK_S))
	{//�����L�[�̉��������ꂽ
		if (GetKeyboardPress(DIK_D))
		{//�E�΂�
			g_player.move.x += sinf(pCamera->rot.y + (D3DX_PI * 0.75f)) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y + (D3DX_PI * 0.75f)) * PLAYER_MOVE;
		}
		else if (GetKeyboardPress(DIK_A))
		{//���΂�
			g_player.move.x += sinf(pCamera->rot.y + (D3DX_PI * -0.75f)) * PLAYER_MOVE;
			g_player.move.z += cosf(pCamera->rot.y + (D3DX_PI * -0.75f)) * PLAYER_MOVE;
		}
		else
		{//���
			g_player.move.x -= sinf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.move.z -= cosf(pCamera->rot.y) * PLAYER_MOVE;
			g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI));
		}
	}
	else if (GetKeyboardPress(DIK_A))
	{//��
		g_player.move.x += sinf(pCamera->rot.y + (D3DX_PI * -0.5f)) * PLAYER_MOVE;
		g_player.move.z += cosf(pCamera->rot.y + (D3DX_PI * -0.5f)) * PLAYER_MOVE;
	}
	else if (GetKeyboardPress(DIK_D))
	{//�E
		g_player.move.x += sinf(pCamera->rot.y + (D3DX_PI * 0.5f)) * PLAYER_MOVE;
		g_player.move.z += cosf(pCamera->rot.y + (D3DX_PI * 0.5f)) * PLAYER_MOVE;
	}
	//�W�����v
	else if (GetKeyboardTrigger(DIK_SPACE))
	{
		g_player.move.y += 100.0f;
	}

	//�v���C���[�̌�����O�����ɌŒ�
	g_player.rotDest.y = (pCamera->rot.y + (D3DX_PI));

	//�����̒ǉ�
	g_player.move.x += (0.0f - g_player.move.x) * 0.5f;
	g_player.move.z += (0.0f - g_player.move.z) * 0.5f;

	//�ʒu�Ɉړ��ʂ����Z
	g_player.pos += g_player.move;

	////��]�̐��K��
	//�ړI�̊p�x���傫�������菬���������肵�����̌v�Z
	if (g_player.rotDest.y - g_player.rot.y > D3DX_PI)
	{
		g_player.rotDest.y -= D3DX_PI * 2.0f;
	}
	else if (g_player.rotDest.y - g_player.rot.y < -D3DX_PI)
	{
		g_player.rotDest.y += D3DX_PI * 2.0f;
	}

	//�����̌v�Z
	g_player.rot.y += (g_player.rotDest.y - g_player.rot.y) * PLAYER_ROTSPEED;

	//�v�Z���ʂ��傫�������菬���������肵�����̒���
	if (g_player.rot.y < -D3DX_PI)
	{
		g_player.rot.y += D3DX_PI * 2.0f;
	}
	else if (g_player.rot.y > D3DX_PI)
	{
		g_player.rot.y -= D3DX_PI * 2.0f;
	}

	//�e�̍X�V
	SetPositionShadow(g_nIdxShadow, D3DXVECTOR3(g_player.pos.x, 0.1f, g_player.pos.z));

	//�s���͈͐���(�ǂƂ̓����蔻��)
	if (g_player.pos.x + PLAYER_SIZE >= MESHFIELD_SIZE * 2)
	{//�E
		if (g_player.pos.z + PLAYER_SIZE >= MESHFIELD_SIZE * 2)
		{//�E��
			g_player.pos.x = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
			g_player.pos.z = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
		}
		else if (g_player.pos.z - PLAYER_SIZE <= -MESHFIELD_SIZE * 2)
		{//�E��O
			g_player.pos.x = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
			g_player.pos.z = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
		}
		else
		{
			g_player.pos.x = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
		}
	}
	else if (g_player.pos.x - PLAYER_SIZE <= -MESHFIELD_SIZE * 2)
	{//��
		if (g_player.pos.z + PLAYER_SIZE >= MESHFIELD_SIZE * 2)
		{//����
			g_player.pos.x = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
			g_player.pos.z = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
		}
		else if (g_player.pos.z - PLAYER_SIZE <= -MESHFIELD_SIZE * 2)
		{//�E��O
			g_player.pos.x = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
			g_player.pos.z = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
		}
		else
		{
			g_player.pos.x = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
		}
	}
	else if (g_player.pos.z + PLAYER_SIZE >= MESHFIELD_SIZE * 2)
	{//��
		g_player.pos.z = (MESHFIELD_SIZE * 2) - PLAYER_SIZE;
	}
	else if (g_player.pos.z - PLAYER_SIZE <= (-MESHFIELD_SIZE * 2))
	{//��O
		g_player.pos.z = (-MESHFIELD_SIZE * 2) + PLAYER_SIZE;
	}

	//���Ƃ̓����蔻��
	if (g_player.pos.y - PLAYER_SIZE * 2 <= 0.1f||g_player.pos.y - PLAYER_SIZE * 2 >= -0.1f)
	{
		g_player.pos.y = 0.0f + PLAYER_SIZE * 2;
	}

	CollisionObject();
}

//========================================================
//					�v���C���[�`�揈��
//========================================================
void DrawPlayer(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&g_player.mtxWorld);

	//�����𔽓]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, g_player.rot.y, g_player.rot.x, g_player.rot.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, g_player.pos.x, g_player.pos.y, g_player.pos.z);
	D3DXMatrixMultiply(&g_player.mtxWorld, &g_player.mtxWorld, &mtxTrans);

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	//�K�w�\���i�e�q�t���j
	for (int nCntPlayerParts = 0; nCntPlayerParts < NUM_PLAYERPARTS; nCntPlayerParts++)
	{
		//���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&g_ModelParts[nCntPlayerParts].mtxWorld);

		//�����𔽓]
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_ModelParts[nCntPlayerParts].rot.y, g_ModelParts[nCntPlayerParts].rot.x, g_ModelParts[nCntPlayerParts].rot.z);
		D3DXMatrixMultiply(&g_ModelParts[nCntPlayerParts].mtxWorld, &g_ModelParts[nCntPlayerParts].mtxWorld, &mtxRot);

		//�ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_ModelParts[nCntPlayerParts].pos.x, g_ModelParts[nCntPlayerParts].pos.y, g_ModelParts[nCntPlayerParts].pos.z);
		D3DXMatrixMultiply(&g_ModelParts[nCntPlayerParts].mtxWorld, &g_ModelParts[nCntPlayerParts].mtxWorld, &mtxTrans);

		//�����̐e���f���̃}�g���b�N�X�Ƃ̊|���Z
		if (g_ModelParts[nCntPlayerParts].ParentIdx < 0)
		{
			D3DXMatrixMultiply(&g_ModelParts[nCntPlayerParts].mtxWorld, &g_ModelParts[nCntPlayerParts].mtxWorld, &g_player.mtxWorld);
		}
		else
		{
			D3DXMatrixMultiply(&g_ModelParts[nCntPlayerParts].mtxWorld, &g_ModelParts[nCntPlayerParts].mtxWorld, &g_ModelParts[g_ModelParts[nCntPlayerParts].ParentIdx].mtxWorld);
		}

		//���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_ModelParts[nCntPlayerParts].mtxWorld);

		//�}�e���A���f�[�^�̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_ModelParts[nCntPlayerParts].pBuffMat->GetBufferPointer();
		for (int nCntMat = 0; nCntMat < (int)g_ModelParts[nCntPlayerParts].nNumMat; nCntMat++)
		{
			//�}�e���A���̐ݒ�
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//�v���C���[�p�[�c�̕`��
			g_ModelParts[nCntPlayerParts].pMesh->DrawSubset(nCntMat);
		}
	}

	//�ێ����Ă����}�e���A����Ԃ�
	pDevice->SetMaterial(&matDef);
}

//========================================================
//			�I�u�W�F�N�g�i���f���j�Ƃ̓����蔻��
//========================================================
void CollisionObject(void)
{
	MODEL *pModel = GetModel();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (pModel->bUse == true)
		{
			D3DXVECTOR3 vtxMax = GetVtxMax(pModel->nType);
			D3DXVECTOR3 vtxMin = GetVtxMin(pModel->nType);

			//�I�u�W�F�N�g�i���f���j�Ƃ̓����蔻��
			if (pModel->pos.x + vtxMin.x >= g_player.posOld.x + PLAYER_SIZE&&
				pModel->pos.x + vtxMin.x < g_player.pos.x + PLAYER_SIZE&&
				pModel->pos.z + vtxMin.z < g_player.pos.z + PLAYER_SIZE&&
				pModel->pos.z + vtxMax.z > g_player.pos.z - PLAYER_SIZE)
			{
				g_player.pos.x = pModel->pos.x + vtxMin.x - PLAYER_SIZE;
			}
			if ((pModel->pos.x + vtxMax.x + PLAYER_SIZE) <= g_player.posOld.x &&
				(pModel->pos.x + vtxMax.x + PLAYER_SIZE) > g_player.pos.x &&
				pModel->pos.z + vtxMin.z < g_player.pos.z + PLAYER_SIZE&&
				pModel->pos.z + vtxMax.z > g_player.pos.z - PLAYER_SIZE)
			{
				g_player.pos.x = (pModel->pos.x + vtxMax.x + PLAYER_SIZE);
			}
			if (pModel->pos.z + vtxMin.z >= g_player.posOld.z + PLAYER_SIZE&&
				pModel->pos.z + vtxMin.z < g_player.pos.z + PLAYER_SIZE&&
				pModel->pos.x + vtxMin.x < g_player.pos.x + PLAYER_SIZE&&
				pModel->pos.x + vtxMax.x > g_player.pos.x - PLAYER_SIZE)
			{
				g_player.pos.z = pModel->pos.z + vtxMin.z - PLAYER_SIZE;
			}
			if (pModel->pos.z + vtxMax.z <= g_player.posOld.z - PLAYER_SIZE&&
				pModel->pos.z + vtxMax.z > g_player.pos.z - PLAYER_SIZE&&
				pModel->pos.x + vtxMin.x < g_player.pos.x + PLAYER_SIZE&&
				pModel->pos.x + vtxMax.x > g_player.pos.x - PLAYER_SIZE)
			{
				g_player.pos.z = pModel->pos.z + vtxMax.z + PLAYER_SIZE;
			}
		}
		pModel++;
	}

}

//========================================================
//				�G�l�~�[�̍U���������������̏���
//========================================================
void HitEnemyAttack(int nAttack)
{
	GAMESTATE &pState = *GetGameState();
	FADE fade = GetFade();

	g_player.nLife -= nAttack;

	if (g_player.nLife <= 0)
	{
		if (fade == FADE_NONE)
		{
			pState = GAMESTATE_END;
			SetFade(MODE_RESULT);
		}
	}
}

//========================================================
//				�v���C���[���̎擾
//========================================================
Player *GetPlayer(void)
{
	return &g_player;
}