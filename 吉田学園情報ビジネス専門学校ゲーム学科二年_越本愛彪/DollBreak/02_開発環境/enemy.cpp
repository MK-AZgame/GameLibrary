//========================================================
//
//	�G�l�~�[���f���̏���[enemy.cpp]
//	AUTHOR:�z�{���V
//
//========================================================
#include <stdio.h>
#include "enemy.h"
#include "player.h"
#include "round.h"
#include "input.h"
#include "shadow.h"
#include "bullet.h"
#include "meshfield.h"
#include "model.h"
#include "loadfileh.h"

//�}�N����`
#define ENEMY_MOVE (1.0f)												//�G�l�~�[�̈ړ���
#define ENEMY_ROTSPEED (0.1f)											//�G�l�~�[�̉�]�̌�����

//�O���[�o���ϐ�
Enemy g_aEnemy[MAX_ENEMY];												//�G�l�~�[�̏����i�[

//========================================================
//					�G�l�~�[����������
//========================================================
void InitEnemy(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�G�l�~�[���̏�����
	for (int nCntEnem = 0; nCntEnem < MAX_ENEMY; nCntEnem++)
	{
		g_aEnemy[nCntEnem].pos = D3DXVECTOR3(0.0f, 20.0f, 0.0f);		//�ʒu�̏�����
		g_aEnemy[nCntEnem].rot = D3DXVECTOR3(0.0f, 3.14f, 0.0f);		//�����̏�����
		g_aEnemy[nCntEnem].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ��ʂ̏�����
		g_aEnemy[nCntEnem].state = ENEMYSTATE_NORMAL;					//��Ԃ̏�����
		g_aEnemy[nCntEnem].rotDest.y = 0;								//�ړI�̊p�x�̏�����
		g_aEnemy[nCntEnem].nEnemyLife = 0;								//���˂݁[�̗̑͂̏�����
		g_aEnemy[nCntEnem].nKey = 0;									//���[�V�����̃L�[�̏�����
		g_aEnemy[nCntEnem].nAttackTime = 0;								//�U���̊Ԋu�̏�����
		g_aEnemy[nCntEnem].bUse = false;								//�g���Ă��Ȃ���Ԃɂ���

		//�p�[�c�̏�����
		for (int nCntEnemyParts = 0; nCntEnemyParts < NUM_ENEMYPARTS; nCntEnemyParts++)
		{
			g_aEnemy[nCntEnem].aModel[nCntEnemyParts].rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
		}
	}
}

//========================================================
//					�G�l�~�[�I������
//========================================================
void UninitEnemy(void)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].aModel[0].pMesh != NULL)
		{
			g_aEnemy[nCntEnemy].aModel[0].pMesh->Release();
			g_aEnemy[nCntEnemy].aModel[0].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (g_aEnemy[nCntEnemy].aModel[0].pBuffMat != NULL)
		{
			g_aEnemy[nCntEnemy].aModel[0].pBuffMat->Release();
			g_aEnemy[nCntEnemy].aModel[0].pBuffMat = NULL;
		}
	}

}

//========================================================
//					�G�l�~�[�X�V����
//========================================================
void UpdateEnemy(void)
{
	Player *pPlayer = GetPlayer();

	for (int nCntEnem = 0; nCntEnem < MAX_ENEMY; nCntEnem++)
	{
		if (g_aEnemy[nCntEnem].bUse == true)
		{
			if (g_aEnemy[nCntEnem].state == ENEMYSTATE_APPEAR)
			{
				//for (int nCnt = 0; nCnt < 80; nCnt++)
				{
					g_aEnemy[nCntEnem].pos.y++;
				}

				if (g_aEnemy[nCntEnem].pos.y >= 30.0f)
				{
					//��Ԃ��h�ʏ�h�ɂ���
					g_aEnemy[nCntEnem].state = ENEMYSTATE_NORMAL;
				}
			}
			else if (g_aEnemy[nCntEnem].state != ENEMYSTATE_APPEAR&&g_aEnemy[nCntEnem].state != ENEMYSTATE_DEATH)
			{
				//posOld�Ɍ��݂̈ʒu��ۑ�
				g_aEnemy[nCntEnem].posOld = g_aEnemy[nCntEnem].pos;

				//�G�l�~�[�̈ړ��ʂ��v�Z
				D3DXVECTOR3 vec = pPlayer->pos - g_aEnemy[nCntEnem].pos;

				//�ړ��ʂ��m�[�}���C�Y
				D3DXVec3Normalize(&vec, &vec);

				//move��vec����
				g_aEnemy[nCntEnem].move = D3DXVECTOR3(vec.x, 0.0f, vec.z);

				//�ʒu�Ɉړ��ʂ����Z���ăG�l�~�[���ړ�������
				g_aEnemy[nCntEnem].pos += g_aEnemy[nCntEnem].move * 0.5f;

				//�G�̉�]�i�v���C���[�̕����������j
				g_aEnemy[nCntEnem].rot.y = atan2f((-pPlayer->pos.x + g_aEnemy[nCntEnem].pos.x), (-pPlayer->pos.z + g_aEnemy[nCntEnem].pos.z));

				////��]�̐��K��
				//�ړI�̊p�x���傫�������菬���������肵�����̌v�Z
				if (g_aEnemy[nCntEnem].rotDest.y - g_aEnemy[nCntEnem].rot.y > D3DX_PI)
				{
					g_aEnemy[nCntEnem].rotDest.y -= D3DX_PI * 2.0f;
				}
				else if (g_aEnemy[nCntEnem].rotDest.y - g_aEnemy[nCntEnem].rot.y < -D3DX_PI)
				{
					g_aEnemy[nCntEnem].rotDest.y += D3DX_PI * 2.0f;
				}

				//��]�̊����̌v�Z
				g_aEnemy[nCntEnem].rot.y += (g_aEnemy[nCntEnem].rotDest.y - g_aEnemy[nCntEnem].rot.y) * ENEMY_ROTSPEED;

				//�v�Z���ʂ��傫�������菬���������肵�����̒���
				if (g_aEnemy[nCntEnem].rot.y < -D3DX_PI)
				{
					g_aEnemy[nCntEnem].rot.y += D3DX_PI * 2.0f;
				}
				else if (g_aEnemy[nCntEnem].rot.y > D3DX_PI)
				{
					g_aEnemy[nCntEnem].rot.y -= D3DX_PI * 2.0f;
				}

				//�e�̍X�V
				SetPositionShadow(g_aEnemy[nCntEnem].nIdxShadow, D3DXVECTOR3(g_aEnemy[nCntEnem].pos.x, 0.1f, g_aEnemy[nCntEnem].pos.z));

				//�s���͈͐���(�ǂƂ̓����蔻��)
				if (g_aEnemy[nCntEnem].pos.x + ENEMY_SIZE >= MESHFIELD_SIZE * 2)
				{//�E
					if (g_aEnemy[nCntEnem].pos.z + ENEMY_SIZE >= MESHFIELD_SIZE * 2)
					{//�E��
						g_aEnemy[nCntEnem].pos.x = (MESHFIELD_SIZE * 2) - ENEMY_SIZE;
						g_aEnemy[nCntEnem].pos.z = (MESHFIELD_SIZE * 2) - ENEMY_SIZE;
					}
					else if (g_aEnemy[nCntEnem].pos.z - ENEMY_SIZE <= -MESHFIELD_SIZE * 2)
					{//�E��O
						g_aEnemy[nCntEnem].pos.x = (MESHFIELD_SIZE * 2) - ENEMY_SIZE;
						g_aEnemy[nCntEnem].pos.z = (-MESHFIELD_SIZE * 2) + ENEMY_SIZE;
					}
					else
					{
						g_aEnemy[nCntEnem].pos.x = (MESHFIELD_SIZE * 2) - ENEMY_SIZE;
					}
				}
				else if (g_aEnemy[nCntEnem].pos.x - ENEMY_SIZE <= -MESHFIELD_SIZE * 2)
				{//��
					if (g_aEnemy[nCntEnem].pos.z + ENEMY_SIZE >= MESHFIELD_SIZE * 2)
					{//����
						g_aEnemy[nCntEnem].pos.x = (-MESHFIELD_SIZE * 2) + ENEMY_SIZE;
						g_aEnemy[nCntEnem].pos.z = (MESHFIELD_SIZE * 2) - ENEMY_SIZE;
					}
					else if (g_aEnemy[nCntEnem].pos.z - ENEMY_SIZE <= -MESHFIELD_SIZE * 2)
					{//�E��O
						g_aEnemy[nCntEnem].pos.x = (-MESHFIELD_SIZE * 2) + ENEMY_SIZE;
						g_aEnemy[nCntEnem].pos.z = (-MESHFIELD_SIZE * 2) + ENEMY_SIZE;
					}
					else
					{
						g_aEnemy[nCntEnem].pos.x = (-MESHFIELD_SIZE * 2) + ENEMY_SIZE;
					}
				}
				else if (g_aEnemy[nCntEnem].pos.z + ENEMY_SIZE >= MESHFIELD_SIZE * 2)
				{//��
					g_aEnemy[nCntEnem].pos.z = (MESHFIELD_SIZE * 2) - ENEMY_SIZE;
				}
				else if (g_aEnemy[nCntEnem].pos.z - ENEMY_SIZE <= (-MESHFIELD_SIZE * 2))
				{//��O
					g_aEnemy[nCntEnem].pos.z = (-MESHFIELD_SIZE * 2) + ENEMY_SIZE;
				}

				//�v���C���[�Ƃ̋�������薢���̏ꍇ�U�����s��
				if (sqrtf((g_aEnemy[nCntEnem].pos.z - pPlayer->pos.z) * (g_aEnemy[nCntEnem].pos.z - pPlayer->pos.z) +
					(g_aEnemy[nCntEnem].pos.x - pPlayer->pos.x) * (g_aEnemy[nCntEnem].pos.x - pPlayer->pos.x)) < 50.0f)
				{
					AttackEnemy(nCntEnem, g_aEnemy[nCntEnem].nAttack);
				}

				//�e��I�u�W�F�N�g�Ƃ̓����蔻��
				CollisionObjectEnemy(nCntEnem);

				//�G�l�~�[���m�̓����蔻��
				CollisionEnemies(nCntEnem);
			}
			else if (g_aEnemy[nCntEnem].state == ENEMYSTATE_DEATH)
			{
				//��]�̊����̌v�Z
				for (int nCntParts = 0; nCntParts < NUM_ENEMYPARTS; nCntParts++)
				{
					////��]�̐��K��
					//�ړI�̊p�x���傫�������菬���������肵�����̌v�Z
					//X
					if (g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.x - g_aEnemy[nCntEnem].aModel[nCntParts].rot.x > D3DX_PI)
					{
						g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.x -= D3DX_PI * 2.0f;
					}
					else if (g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.x - g_aEnemy[nCntEnem].aModel[nCntParts].rot.x < -D3DX_PI)
					{
						g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.x += D3DX_PI * 2.0f;
					}

					//Y
					if (g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.y - g_aEnemy[nCntEnem].aModel[nCntParts].rot.y > D3DX_PI)
					{
						g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.y -= D3DX_PI * 2.0f;
					}
					else if (g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.y - g_aEnemy[nCntEnem].aModel[nCntParts].rot.y < -D3DX_PI)
					{
						g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.y += D3DX_PI * 2.0f;
					}

					//��]�̊����̌v�Z
					g_aEnemy[nCntEnem].aModel[nCntParts].rot.x += (g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.x - g_aEnemy[nCntEnem].aModel[nCntParts].rot.x) * 0.05f;
					g_aEnemy[nCntEnem].aModel[nCntParts].rot.y += (g_aEnemy[nCntEnem].aModel[nCntParts].rotDest.y - g_aEnemy[nCntEnem].aModel[nCntParts].rot.y) * 0.05f;

					//�v�Z���ʂ��傫�������菬���������肵�����̒���
					if (g_aEnemy[nCntEnem].aModel[nCntParts].rot.x < -D3DX_PI)
					{
						g_aEnemy[nCntEnem].aModel[nCntParts].rot.x += D3DX_PI * 2.0f;
					}
					else if (g_aEnemy[nCntEnem].aModel[nCntParts].rot.x > D3DX_PI)
					{
						g_aEnemy[nCntEnem].aModel[nCntParts].rot.x -= D3DX_PI * 2.0f;
					}			

					if (g_aEnemy[nCntEnem].aModel[nCntParts].rot.y < -D3DX_PI)
					{
						g_aEnemy[nCntEnem].aModel[nCntParts].rot.y += D3DX_PI * 2.0f;
					}
					else if (g_aEnemy[nCntEnem].aModel[nCntParts].rot.y > D3DX_PI)
					{
						g_aEnemy[nCntEnem].aModel[nCntParts].rot.y -= D3DX_PI * 2.0f;
					}

					g_aEnemy[nCntEnem].aModel[nCntParts].pos += (g_aEnemy[nCntEnem].aModel[nCntParts].posDest - g_aEnemy[nCntEnem].aModel[nCntParts].pos) * 0.05f;
				}

				//���S�����G��������܂ł̎��Ԃ̐ݒ�
				static int nCnt = 120;

				nCnt--;

				if (nCnt <= 0)
				{
					g_aEnemy[nCntEnem].bUse = false;

					//�G���c���Ă��邩�𔻒�
					RestEnemy();

					nCnt = 120;
				}
			}
		}
	}
}

//========================================================
//					�G�l�~�[�`�揈��
//========================================================
void DrawEnemy(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DXMATRIX mtxRot, mtxTrans;
	D3DMATERIAL9 matDef;
	D3DXMATERIAL *pMat;

	//���݂̃}�e���A����ێ�
	pDevice->GetMaterial(&matDef);

	for (int nCntEnem = 0; nCntEnem < MAX_ENEMY; nCntEnem++)
	{
		if (g_aEnemy[nCntEnem].bUse == true)
		{
			//���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&g_aEnemy[nCntEnem].mtxWorld);

			//�����𔽓]
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCntEnem].rot.y, g_aEnemy[nCntEnem].rot.x, g_aEnemy[nCntEnem].rot.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnem].mtxWorld, &g_aEnemy[nCntEnem].mtxWorld, &mtxRot);

			//�ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnem].pos.x, g_aEnemy[nCntEnem].pos.y, g_aEnemy[nCntEnem].pos.z);
			D3DXMatrixMultiply(&g_aEnemy[nCntEnem].mtxWorld, &g_aEnemy[nCntEnem].mtxWorld, &mtxTrans);

			//�K�w�\���i�e�q�t���j
			for (int nCntPlayerParts = 0; nCntPlayerParts < NUM_ENEMYPARTS; nCntPlayerParts++)
			{
				//���[���h�}�g���b�N�X�̏�����
				D3DXMatrixIdentity(&g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld);

				//�����𔽓]
				D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aEnemy[nCntEnem].aModel[nCntPlayerParts].rot.y, g_aEnemy[nCntEnem].aModel[nCntPlayerParts].rot.x, g_aEnemy[nCntEnem].aModel[nCntPlayerParts].rot.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld, &g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld, &mtxRot);

				//�ʒu�𔽉f
				D3DXMatrixTranslation(&mtxTrans, g_aEnemy[nCntEnem].aModel[nCntPlayerParts].pos.x, g_aEnemy[nCntEnem].aModel[nCntPlayerParts].pos.y, g_aEnemy[nCntEnem].aModel[nCntPlayerParts].pos.z);
				D3DXMatrixMultiply(&g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld, &g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld, &mtxTrans);

				//�����̐e���f���̃}�g���b�N�X�Ƃ̊|���Z
				if (g_aEnemy[nCntEnem].aModel[nCntPlayerParts].ParentIdx < 0)
				{
					D3DXMatrixMultiply(&g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld, &g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld, &g_aEnemy[nCntEnem].mtxWorld);
				}
				else
				{
					D3DXMatrixMultiply(&g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld, &g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld, &g_aEnemy[nCntEnem].aModel[g_aEnemy[nCntEnem].aModel[nCntPlayerParts].ParentIdx].mtxWorld);
				}

				//���[���h�}�g���b�N�X�̐ݒ�
				pDevice->SetTransform(D3DTS_WORLD, &g_aEnemy[nCntEnem].aModel[nCntPlayerParts].mtxWorld);

				//�}�e���A���f�[�^�̃|�C���^���擾
				pMat = (D3DXMATERIAL*)g_aEnemy[nCntEnem].aModel[nCntPlayerParts].pBuffMat->GetBufferPointer();
				for (int nCntMat = 0; nCntMat < (int)g_aEnemy[nCntEnem].aModel[nCntPlayerParts].nNumMat; nCntMat++)
				{
					//�}�e���A���̐ݒ�
					pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

					//�G�l�~�[�p�[�c�̕`��
					g_aEnemy[nCntEnem].aModel[nCntPlayerParts].pMesh->DrawSubset(nCntMat);
				}
			}
		}
	}

	//�ێ����Ă����}�e���A����Ԃ�
	pDevice->SetMaterial(&matDef);
}

//========================================================
//					�G�l�~�[�̐ݒ菈��
//========================================================
void SetEnemy(D3DXVECTOR3 pos,int nLife,int nAttack)
{
	for (int nCntEnem = 0; nCntEnem < MAX_ENEMY; nCntEnem++)
	{
		if (g_aEnemy[nCntEnem].bUse == false)
		{
			//�t�@�C���ǂݍ���
			LoadEnemyFile("data/enemy.txt", &g_aEnemy[nCntEnem].aModel[0]);

			//�p�[�c�̐e�ԍ��̐ݒ�
			g_aEnemy[nCntEnem].aModel[0].ParentIdx = -1;				//����
			g_aEnemy[nCntEnem].aModel[1].ParentIdx = 0;					//��
			g_aEnemy[nCntEnem].aModel[2].ParentIdx = 0;					//�r�i�E�j
			g_aEnemy[nCntEnem].aModel[3].ParentIdx = 0;					//�r�i���j
			g_aEnemy[nCntEnem].aModel[4].ParentIdx = 0;					//�����i�E�j
			g_aEnemy[nCntEnem].aModel[5].ParentIdx = 0;					//�����i���j
			g_aEnemy[nCntEnem].aModel[6].ParentIdx = 4;					//�ӂ���͂��i�E�j
			g_aEnemy[nCntEnem].aModel[7].ParentIdx = 5;					//�ӂ���͂��i���j

			//��
			g_aEnemy[nCntEnem].aModel[0].pos.y = 12.0f;
			g_aEnemy[nCntEnem].aModel[0].rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
			//��
			g_aEnemy[nCntEnem].aModel[1].pos.y = 15.0f;
			g_aEnemy[nCntEnem].aModel[1].pos.z = 0.0f;
			g_aEnemy[nCntEnem].aModel[1].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//�E�r
			g_aEnemy[nCntEnem].aModel[2].pos.x = -10.0f;
			g_aEnemy[nCntEnem].aModel[2].pos.y = 12.0f;
			g_aEnemy[nCntEnem].aModel[2].rot.x = 0.0f;
			g_aEnemy[nCntEnem].aModel[2].rot.z = -30.0f;
			//���r
			g_aEnemy[nCntEnem].aModel[3].pos.x = 10.0f;
			g_aEnemy[nCntEnem].aModel[3].pos.y = 12.0f;
			g_aEnemy[nCntEnem].aModel[3].rot.x = 0.0f;
			g_aEnemy[nCntEnem].aModel[3].rot.z = 30.0f;
			//�E����
			g_aEnemy[nCntEnem].aModel[4].pos.x = -5.0f;
			g_aEnemy[nCntEnem].aModel[4].pos.y = -12.0f;
			g_aEnemy[nCntEnem].aModel[4].pos.z = 0.0f;
			g_aEnemy[nCntEnem].aModel[4].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//������
			g_aEnemy[nCntEnem].aModel[5].pos.x = 5.0f;
			g_aEnemy[nCntEnem].aModel[5].pos.y = -12.0f;
			g_aEnemy[nCntEnem].aModel[5].pos.z = 0.0f;
			g_aEnemy[nCntEnem].aModel[5].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//�E�ӂ���͂�
			g_aEnemy[nCntEnem].aModel[6].pos.x = 0.1f;
			g_aEnemy[nCntEnem].aModel[6].pos.y = -18.0f;
			g_aEnemy[nCntEnem].aModel[6].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			//���ӂ���͂�
			g_aEnemy[nCntEnem].aModel[7].pos.x = -0.5f;
			g_aEnemy[nCntEnem].aModel[7].pos.y = -18.0f;
			g_aEnemy[nCntEnem].aModel[7].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			g_aEnemy[nCntEnem].pos = pos;								//�ʒu�̐ݒ�
			g_aEnemy[nCntEnem].nEnemyLife = nLife;						//���C�t�̐ݒ�
			g_aEnemy[nCntEnem].nAttack = nAttack;						//�U���͂̐ݒ�
			g_aEnemy[nCntEnem].state = ENEMYSTATE_APPEAR;				//�G�̏�Ԃ��h�o���h�ɂ���
			g_aEnemy[nCntEnem].nKey = rand() % 2;

			//�e�̐ݒ�
			g_aEnemy[nCntEnem].nIdxShadow = SetShadow(D3DXVECTOR3(g_aEnemy[nCntEnem].pos.x, 0.1f, g_aEnemy[nCntEnem].pos.z), g_aEnemy[nCntEnem].rot);

			g_aEnemy[nCntEnem].bUse = true;								//�g�p���Ă����Ԃɂ���

			break;
		}
	}
}

//========================================================
//			�I�u�W�F�N�g�i���f���j�Ƃ̓����蔻��
//========================================================
void CollisionObjectEnemy(int nIdxEnemy)
{
	MODEL *pModel = GetModel();

	for (int nCntModel = 0; nCntModel < MAX_MODEL; nCntModel++)
	{
		if (pModel->bUse == true)
		{
			D3DXVECTOR3 vtxMax = GetVtxMax(pModel->nType);
			D3DXVECTOR3 vtxMin = GetVtxMin(pModel->nType);

			//�I�u�W�F�N�g�i���f���j�Ƃ̓����蔻��
			if (pModel->pos.x + vtxMin.x >= g_aEnemy[nIdxEnemy].posOld.x + ENEMY_SIZE&&
				pModel->pos.x + vtxMin.x < g_aEnemy[nIdxEnemy].pos.x + ENEMY_SIZE&&
				pModel->pos.z + vtxMin.z < g_aEnemy[nIdxEnemy].pos.z + ENEMY_SIZE&&
				pModel->pos.z + vtxMax.z > g_aEnemy[nIdxEnemy].pos.z - ENEMY_SIZE)
			{
				g_aEnemy[nIdxEnemy].pos.x = pModel->pos.x + vtxMin.x - ENEMY_SIZE;
			}
			if ((pModel->pos.x + vtxMax.x + ENEMY_SIZE) <= g_aEnemy[nIdxEnemy].posOld.x &&
				(pModel->pos.x + vtxMax.x + ENEMY_SIZE) > g_aEnemy[nIdxEnemy].pos.x &&
				pModel->pos.z + vtxMin.z < g_aEnemy[nIdxEnemy].pos.z + ENEMY_SIZE&&
				pModel->pos.z + vtxMax.z > g_aEnemy[nIdxEnemy].pos.z - ENEMY_SIZE)
			{
				g_aEnemy[nIdxEnemy].pos.x = (pModel->pos.x + vtxMax.x + ENEMY_SIZE);
			}
			if (pModel->pos.z + vtxMin.z >= g_aEnemy[nIdxEnemy].posOld.z + ENEMY_SIZE&&
				pModel->pos.z + vtxMin.z < g_aEnemy[nIdxEnemy].pos.z + ENEMY_SIZE&&
				pModel->pos.x + vtxMin.x < g_aEnemy[nIdxEnemy].pos.x + ENEMY_SIZE&&
				pModel->pos.x + vtxMax.x > g_aEnemy[nIdxEnemy].pos.x - ENEMY_SIZE)
			{
				g_aEnemy[nIdxEnemy].pos.z = pModel->pos.z + vtxMin.z - ENEMY_SIZE;
			}
			if (pModel->pos.z + vtxMax.z <= g_aEnemy[nIdxEnemy].posOld.z - ENEMY_SIZE&&
				pModel->pos.z + vtxMax.z > g_aEnemy[nIdxEnemy].pos.z - ENEMY_SIZE&&
				pModel->pos.x + vtxMin.x < g_aEnemy[nIdxEnemy].pos.x + ENEMY_SIZE&&
				pModel->pos.x + vtxMax.x > g_aEnemy[nIdxEnemy].pos.x - ENEMY_SIZE)
			{
				g_aEnemy[nIdxEnemy].pos.z = pModel->pos.z + vtxMax.z + ENEMY_SIZE;
			}
		}
		pModel++;
	}
}

//========================================================
//				�G�l�~�[���m�̂����蔻��
//========================================================
void CollisionEnemies(int nIdxEnemy)
{
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			if (g_aEnemy[nIdxEnemy].posOld.x >= g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE * 2&&
				g_aEnemy[nIdxEnemy].pos.x< g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.z> g_aEnemy[nCntEnemy].pos.z - ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.z< g_aEnemy[nCntEnemy].pos.z + ENEMY_SIZE * 2)
			{
				g_aEnemy[nIdxEnemy].pos.x = g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE * 2;
			}
			if (g_aEnemy[nIdxEnemy].posOld.x <= g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.x> g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.z> g_aEnemy[nCntEnemy].pos.z - ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.z< g_aEnemy[nCntEnemy].pos.z + ENEMY_SIZE * 2)
			{
				g_aEnemy[nIdxEnemy].pos.x = g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE * 2;
			}
			if (g_aEnemy[nIdxEnemy].posOld.z >= g_aEnemy[nCntEnemy].pos.z + ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.z < g_aEnemy[nCntEnemy].pos.z + ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.x > g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.x < g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE * 2)
			{
				g_aEnemy[nIdxEnemy].pos.z = g_aEnemy[nCntEnemy].pos.z + ENEMY_SIZE * 2;
			}
			if (g_aEnemy[nIdxEnemy].posOld.z <= g_aEnemy[nCntEnemy].pos.z - ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.z > g_aEnemy[nCntEnemy].pos.z - ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.x > g_aEnemy[nCntEnemy].pos.x - ENEMY_SIZE * 2 &&
				g_aEnemy[nIdxEnemy].pos.x < g_aEnemy[nCntEnemy].pos.x + ENEMY_SIZE * 2)
			{
				g_aEnemy[nIdxEnemy].pos.z = g_aEnemy[nCntEnemy].pos.z - ENEMY_SIZE * 2;
			}
		}
	}
}

//========================================================
//					�e�Ɠ����������̏���
//========================================================
void HitBullet(int nIdxEnemy)
{
	//�G�l�~�[�̃��C�t������
	g_aEnemy[nIdxEnemy].nEnemyLife--;

	//�G�l�~�[�̃��C�t��0�ȉ��ɂȂ�����
	if (g_aEnemy[nIdxEnemy].nEnemyLife <= 0)
	{
		//��Ԃ��h���S�h�ɂ���
		g_aEnemy[nIdxEnemy].state = ENEMYSTATE_DEATH;

		//�p�[�c�̐e�ԍ��̐ݒ�
		g_aEnemy[nIdxEnemy].aModel[0].ParentIdx = -1;				//����
		g_aEnemy[nIdxEnemy].aModel[1].ParentIdx = -1;				//��
		g_aEnemy[nIdxEnemy].aModel[2].ParentIdx = -1;				//�r�i�E�j
		g_aEnemy[nIdxEnemy].aModel[3].ParentIdx = -1;				//�r�i���j
		g_aEnemy[nIdxEnemy].aModel[4].ParentIdx = -1;				//�����i�E�j
		g_aEnemy[nIdxEnemy].aModel[5].ParentIdx = -1;				//�����i���j
		g_aEnemy[nIdxEnemy].aModel[6].ParentIdx = -1;				//�ӂ���͂��i�E�j
		g_aEnemy[nIdxEnemy].aModel[7].ParentIdx = -1;				//�ӂ���͂��i���j

		//��
		g_aEnemy[nIdxEnemy].aModel[0].posDest.y = -30.0f;
		g_aEnemy[nIdxEnemy].aModel[0].rotDest.x = 1.57f;
		//��
		g_aEnemy[nIdxEnemy].aModel[1].posDest.y = -30.0f;
		g_aEnemy[nIdxEnemy].aModel[1].posDest.z = 30.0f;
		g_aEnemy[nIdxEnemy].aModel[1].rotDest.x = 1.57f;
		//�E�r
		g_aEnemy[nIdxEnemy].aModel[2].posDest.x = -10.0f;
		g_aEnemy[nIdxEnemy].aModel[2].posDest.y = -30.0f;
		g_aEnemy[nIdxEnemy].aModel[2].rotDest.x = 1.57f;
		//���r
		g_aEnemy[nIdxEnemy].aModel[3].posDest.x = 10.0f;
		g_aEnemy[nIdxEnemy].aModel[3].posDest.y = -30.0f;
		g_aEnemy[nIdxEnemy].aModel[3].rotDest.x = 1.57f;
		//�E����
		g_aEnemy[nIdxEnemy].aModel[4].posDest.x = -10.0f;
		g_aEnemy[nIdxEnemy].aModel[4].posDest.y = -30.0f;
		g_aEnemy[nIdxEnemy].aModel[4].posDest.z = -20.0f;
		g_aEnemy[nIdxEnemy].aModel[4].rotDest.x = 1.57f;
		g_aEnemy[nIdxEnemy].aModel[4].rotDest.y = 2.67f;
		//������
		g_aEnemy[nIdxEnemy].aModel[5].posDest.x = 10.0f;
		g_aEnemy[nIdxEnemy].aModel[5].posDest.y = -30.0f;
		g_aEnemy[nIdxEnemy].aModel[5].posDest.z = -20.0f;
		g_aEnemy[nIdxEnemy].aModel[5].rotDest.x = 1.57f;
		g_aEnemy[nIdxEnemy].aModel[5].rotDest.y = -1.26f;
		//�E�ӂ���͂�
		g_aEnemy[nIdxEnemy].aModel[6].posDest.x = -10.0f;
		g_aEnemy[nIdxEnemy].aModel[6].posDest.y = -30.0f;
		g_aEnemy[nIdxEnemy].aModel[6].rotDest.x = 1.57f;
		g_aEnemy[nIdxEnemy].aModel[6].rotDest.y = -1.57f;
		//���ӂ���͂�
		g_aEnemy[nIdxEnemy].aModel[7].posDest.x = -10.0f;
		g_aEnemy[nIdxEnemy].aModel[7].posDest.y = -30.0f;
		g_aEnemy[nIdxEnemy].aModel[7].rotDest.x = 1.57f;
		g_aEnemy[nIdxEnemy].aModel[7].rotDest.y = 1.57f;

		//�e�̏���
		DeleteShadow(g_aEnemy[nIdxEnemy].nIdxShadow);
	}
}

//========================================================
//					�G�l�~�[�̃��[�V����
//========================================================
void EnemyMotion(void)
{
	//���[�V����
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			if (g_aEnemy[nCntEnemy].state == ENEMYSTATE_NORMAL)
			{//�ړ����[�V����
				if (g_aEnemy[nCntEnemy].nKey == 0)
				{
					//�E��E�E��
					g_aEnemy[nCntEnemy].aModel[2].rot.x += 0.02f;

					//����E����
					g_aEnemy[nCntEnemy].aModel[3].rot.x -= 0.02f;

					if (g_aEnemy[nCntEnemy].aModel[2].rot.x >= 1.2f)
					{
						g_aEnemy[nCntEnemy].aModel[2].rot.x = 1.2f;
						g_aEnemy[nCntEnemy].aModel[3].rot.x = -1.2f;

						g_aEnemy[nCntEnemy].nKey = 1;
					}
				}
				else
				{
					//�E��E�E��
					g_aEnemy[nCntEnemy].aModel[2].rot.x -= 0.02f;

					//����E����
					g_aEnemy[nCntEnemy].aModel[3].rot.x += 0.02f;

					if (g_aEnemy[nCntEnemy].aModel[2].rot.x <= -1.2f)
					{
						g_aEnemy[nCntEnemy].aModel[2].rot.x = -1.2f;
						g_aEnemy[nCntEnemy].aModel[3].rot.x = 1.2f;

						g_aEnemy[nCntEnemy].nKey = 0;
					}
				}
			}
			else if(g_aEnemy[nCntEnemy].state == ENEMYSTATE_ATTACK)
			{//�U�����[�V����
				if (g_aEnemy[nCntEnemy].nKey == 0)
				{
					//�E��E�E��
					g_aEnemy[nCntEnemy].aModel[2].rot.x += 0.04f;

					//����E����
					g_aEnemy[nCntEnemy].aModel[3].rot.x += 0.04f;

					if (g_aEnemy[nCntEnemy].aModel[2].rot.x >= 2.4f)
					{
						g_aEnemy[nCntEnemy].aModel[2].rot.x = 2.4f;
						g_aEnemy[nCntEnemy].aModel[3].rot.x = 2.4f;

						g_aEnemy[nCntEnemy].nKey = 1;
					}
				}
				else
				{
					//�E��E�E��
					g_aEnemy[nCntEnemy].aModel[2].rot.x -= 0.04f;

					//����E����
					g_aEnemy[nCntEnemy].aModel[3].rot.x -= 0.04f;

					if (g_aEnemy[nCntEnemy].aModel[2].rot.x <= 0.0f)
					{
						g_aEnemy[nCntEnemy].aModel[2].rot.x = 0.0f;
						g_aEnemy[nCntEnemy].aModel[3].rot.x = 0.0f;

						//g_aEnemy[nCntEnemy].nKey = 0;
						g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
					}
				}

			}
			
			if(g_aEnemy[nCntEnemy].state != ENEMYSTATE_DEATH)
			{
				if (g_aEnemy[nCntEnemy].nKey == 0)
				{
					//�E��E�E��
					g_aEnemy[nCntEnemy].aModel[4].rot.x -= 0.01f;

					//����E����
					g_aEnemy[nCntEnemy].aModel[5].rot.x += 0.01f;

					if (g_aEnemy[nCntEnemy].aModel[4].rot.x <= -0.6f)
					{
						g_aEnemy[nCntEnemy].aModel[4].rot.x = -0.6f;
						g_aEnemy[nCntEnemy].aModel[5].rot.x = 0.6f;
					}
				}
				else
				{
					//�E��E�E��
					g_aEnemy[nCntEnemy].aModel[4].rot.x += 0.01f;

					//����E����
					g_aEnemy[nCntEnemy].aModel[5].rot.x -= 0.01f;

					if (g_aEnemy[nCntEnemy].aModel[4].rot.x >= 0.6f)
					{
						g_aEnemy[nCntEnemy].aModel[4].rot.x = 0.6f;
						g_aEnemy[nCntEnemy].aModel[5].rot.x = -0.6f;
					}
				}

			}
		}
	}
}

//========================================================
//					�G�l�~�[�̍U���̏���
//========================================================
void AttackEnemy(int nIdxEnemy,int nAttack)
{
	g_aEnemy[nIdxEnemy].nAttackTime++;

	if (g_aEnemy[nIdxEnemy].nAttackTime >= 40)
	{
		//�U�����[�V�����ɓ��钼�O�ɘr�̉�]�̏����ʒu�����߂Ă���
		g_aEnemy[nIdxEnemy].aModel[2].rot.x = 0.0f;
		g_aEnemy[nIdxEnemy].aModel[3].rot.x = 0.0f;

		g_aEnemy[nIdxEnemy].state = ENEMYSTATE_ATTACK;
		g_aEnemy[nIdxEnemy].nAttackTime = 0;
		HitEnemyAttack(nAttack);
	}
	else
	{
		//g_aEnemy[nIdxEnemy].nAttackTime = 60;
	}
}

//========================================================
//					�G�l�~�[���̎擾
//========================================================
void RestEnemy(void)
{
	Round *pRound = GetRound();

	//�G�l�~�[���c���Ĉȉ��𔻒肷��ϐ�
	int nfalseEnemy = 0;

	//�G�l�~�[���c���Ă��邩�𔻒肷�鏈��
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{
			nfalseEnemy++;												//��Ԃ�false�̃G�l�~�[�̐������Z
		}
	}

	if (nfalseEnemy == MAX_ENEMY)
	{//��Ԃ�false�̃G�l�~�[�̐���MAX_ENEMY�Ɠ����������ꍇ
		pRound->nState = ROUND_INTERVAL;								//���E���h�̏�Ԃ�ROUND_INTERVAL�ɕύX
	}
}

//========================================================
//					�G�l�~�[���̎擾
//========================================================
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}