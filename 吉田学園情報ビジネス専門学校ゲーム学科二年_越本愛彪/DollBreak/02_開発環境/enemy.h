//========================================================
//
//	�G�l�~�[�̏���[enemy.h]
//	AUTHOR:�z�{���V
//
//========================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

#define NUM_ENEMYPARTS (8)					//�G�l�~�[���\������p�[�c�̐�

//�G�l�~�[��Ԃ̗񋓌^
typedef enum
{
	ENEMYSTATE_NORMAL = 0,					//�ʏ�			
	ENEMYSTATE_APPEAR,						//�o������
	ENEMYSTATE_HIT,							//�e����������
	ENEMYSTATE_ATTACK,						//�U����
	ENEMYSTATE_DEATH,						//���S
	ENEMYSTATE_MAX
}ENEMYSTATE;

//���f���\����
typedef struct
{
	LPD3DXMESH pMesh;						//���b�V���ւ̃|�C���^
	LPD3DXBUFFER pBuffMat;					//���_�o�b�t�@�ւ̃|�C���^
	DWORD nNumMat;
	char modelfilename;						//���f���̃t�@�C����
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;						//�p�[�c�̈ʒu
	D3DXVECTOR3 posDest;					//�p�[�c�̖ړI�̈ʒu
	D3DXVECTOR3 rot;						//�p�[�c�̌���
	D3DXVECTOR3 rotDest;					//�ړI�̌���
	int ParentIdx;							//�e�̔ԍ�
	int nMaxModelNum;						//���f���̐�
}EnemyModel;

//�G�l�~�[�\����
typedef struct
{
	D3DXVECTOR3 pos;						//�ʒu
	D3DXVECTOR3 posOld;						//�O��̈ʒu
	D3DXVECTOR3 move;						//�ړ���
	D3DXVECTOR3 rot;						//����
	D3DXMATRIX mtxWorld;					//���[���h�}�g���b�N�X
	D3DXVECTOR3 rotDest;					//�ړI�̌���
	ENEMYSTATE state;						//�G�l�~�[�̏��
	int nEnemyLife;							//�G�l�~�[�̗̑�
	int nIdxShadow;							//�e�̃C���f�b�N�X
	int nAttack;							//�G�̍U����
	int nAttackTime;						//�U���̊Ԋu
	int nKey;								//���[�V�����̐؂�ւ�
	bool bUse;								//�g�p����Ă��邩�ǂ���
	EnemyModel aModel[NUM_ENEMYPARTS];		//�G�l�~�[�̃��f��
} Enemy;

//�}�N����`
#define ENEMY_SIZE (20.0f)					//�G�l�~�[�̃T�C�Y
#define MAX_ENEMY (128)						//�G�̍ő吔

//�v���g�^�C�v�錾
void InitEnemy(void);						
void UninitEnemy(void);						
void UpdateEnemy(void);						
void DrawEnemy(void);						
void CollisionObjectEnemy(int nIdxEnemy);	//�I�u�W�F�N�g�i���f���j�Ƃ̓����蔻��
void CollisionEnemies(int nIdxEnemy);		//�G�l�~�[���m�̓����蔻��
void HitBullet(int nIdxEnemy);				//�e�Ƃ̓����蔻��
void SetEnemy(D3DXVECTOR3 pos,int nLife,
	int nAttack);							//�G�l�~�[�̐ݒ菈��
void EnemyMotion(void);						//�G�l�~�[�̃��[�V����
void AttackEnemy(int nIdxEnemy,
	int nAttack);							//�G�l�~�[�̍U���̏���
void RestEnemy(void);						//�G�l�~�[�̎c��𔻒�
Enemy *GetEnemy(void);						//�G�l�~�[�̏��̎擾

#endif