//===============================================================
//
//	�t�@�C���ǂݍ��݂̏���[loadfile.h]
//	AUTHOR:�z�{���V
//
//===============================================================
#ifndef _LOADFILE_H_
#define _LOADFILE_H_

#include "main.h"
#include "player.h"
#include "enemy.h"
#include "model.h"

//�t�@�C���ǂݍ��݂̍\����
typedef struct
{
	char loadName[256];
	int  nMaxLoad;
} LOADFILE;

//�ǂݍ��ޏ��̎��
typedef enum
{
	ROADTYPE_PLAYER = 0,
	LOADTYPE_ENEMY = 1,
	LOADTYPE_MODEL = 2,
	ROADTYPE_MAX
} LOADTYPE;

//�v���g�^�C�v�錾
void LoadMotionFile(char *pfilename,ModelParts *pModelParts);	//���[�V�����t�@�C���ǂݍ��ݗl�֐�
void LoadEnemyFile(char *pfilename, EnemyModel *pEnemyModel);	//�G�l�~�[�t�@�C���ǂݍ��݊֐�
void LoadModelFile(char *pfilename, ModelInfo *ModelInfo);		//���f���t�@�C���̓ǂݍ���

#endif