//========================================================
//
//	�t�@�C���ǂݍ��݂̏���[loadfile.cpp]
//	AUTHOR:�z�{���V
//
//========================================================
#include <stdio.h>
#include "loadfileh.h"

//�}�N����`
LOADFILE g_loadFile;

//========================================================
//			���[�V�����t�@�C���ǂݍ��݊֐�
//========================================================
void LoadMotionFile(char *pfilename,ModelParts *pModelParts)
{
	FILE *fp;											//�t�@�C���|�C���^
	
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�t�@�C�����J��
	fp = fopen(pfilename, "r");

	if (fp != NULL)
	{//����
		char skipWord[128];
		char aJudge[128];

		while(fscanf(fp, "%s", &aJudge[0]) != EOF)
		{
			int nCnt = 0;

			if (strcmp(&aJudge[0], "NUM_MODEL") == 0)
			{//�ǂݍ��񂾕�����"NUM_MODEL"��������
				fscanf(fp, "%s", &skipWord[0]);
				fscanf(fp, "%d", &g_loadFile.nMaxLoad);
			}
			if (strcmp(&aJudge[0], "MODEL_FILENAME") == 0)
			{//�ǂݍ��񂾕�����"MODEL_FILENAME"��������
				fscanf(fp, "%s", &skipWord[0]);
				fscanf(fp, "%s", &g_loadFile.loadName[0]);

				D3DXLoadMeshFromX(&g_loadFile.loadName[0], D3DXMESH_SYSTEMMEM, pDevice, NULL, &pModelParts->pBuffMat, NULL, &pModelParts->nNumMat, &pModelParts->pMesh);

				pModelParts++;
			}
		}
		//�t�@�C�������
		fclose(fp);
	}
	else
	{//���s
	}
}

//========================================================
//			�G�l�~�[�t�@�C���̓ǂݍ���
//========================================================
void LoadEnemyFile(char *pfilename, EnemyModel *pEnemyModel)
{
	FILE *fp;											//�t�@�C���|�C���^

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�t�@�C�����J��
	fp = fopen(pfilename, "r");

	if (fp != NULL)
	{//����
		char skipWord[128];
		char aJudge[128];

		while (fscanf(fp, "%s", &aJudge[0]) != EOF)
		{
			int nCnt = 0;

			if (strcmp(&aJudge[0], "NUM_MODEL") == 0)
			{//�ǂݍ��񂾕�����"NUM_MODEL"��������
				fscanf(fp, "%s", &skipWord[0]);
				fscanf(fp, "%d", &g_loadFile.nMaxLoad);
			}
			if (strcmp(&aJudge[0], "MODEL_FILENAME") == 0)
			{//�ǂݍ��񂾕�����"MODEL_FILENAME"��������
				fscanf(fp, "%s", &skipWord[0]);
				fscanf(fp, "%s", &g_loadFile.loadName[0]);

				D3DXLoadMeshFromX(&g_loadFile.loadName[0], D3DXMESH_SYSTEMMEM, pDevice, NULL, &pEnemyModel->pBuffMat, NULL, &pEnemyModel->nNumMat, &pEnemyModel->pMesh);

				pEnemyModel++;
			}
		}
		//�t�@�C�������
		fclose(fp);
	}
	else
	{//���s
	}
}

//========================================================
//			���f���t�@�C���̓ǂݍ���
//========================================================
void LoadModelFile(char *pfilename, ModelInfo *pModelInfo)
{
	FILE *fp;											//�t�@�C���|�C���^

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//�t�@�C�����J��
	fp = fopen(pfilename, "r");

	if (fp != NULL)
	{//����
		char skipWord[128];
		char aJudge[128];

		while (fscanf(fp, "%s", &aJudge[0]) != EOF)
		{
			int nCnt = 0;

			if (strcmp(&aJudge[0], "NUM_MODEL") == 0)
			{//�ǂݍ��񂾕�����"NUM_MODEL"��������
				fscanf(fp, "%s", &skipWord[0]);
				fscanf(fp, "%d", &g_loadFile.nMaxLoad);
			}
			if (strcmp(&aJudge[0], "MODEL_FILENAME") == 0)
			{//�ǂݍ��񂾕�����"MODEL_FILENAME"��������
				fscanf(fp, "%s", &skipWord[0]);
				fscanf(fp, "%s", &g_loadFile.loadName[0]);

				D3DXLoadMeshFromX(&g_loadFile.loadName[0], D3DXMESH_SYSTEMMEM, pDevice, NULL, &pModelInfo->pBuffMatModel, NULL, &pModelInfo->nNumMatModel, &pModelInfo->pMeshModel);

				pModelInfo++;
			}
			//if(srcmp(&aJudge[0],""))
		}
		//�t�@�C�������
		fclose(fp);
	}
	else
	{//���s
	}
}
