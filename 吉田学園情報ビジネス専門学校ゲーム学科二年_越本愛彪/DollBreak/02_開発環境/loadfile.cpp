//========================================================
//
//	ファイル読み込みの処理[loadfile.cpp]
//	AUTHOR:越本愛彪
//
//========================================================
#include <stdio.h>
#include "loadfileh.h"

//マクロ定義
LOADFILE g_loadFile;

//========================================================
//			モーションファイル読み込み関数
//========================================================
void LoadMotionFile(char *pfilename,ModelParts *pModelParts)
{
	FILE *fp;											//ファイルポインタ
	
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ファイルを開く
	fp = fopen(pfilename, "r");

	if (fp != NULL)
	{//成功
		char skipWord[128];
		char aJudge[128];

		while(fscanf(fp, "%s", &aJudge[0]) != EOF)
		{
			int nCnt = 0;

			if (strcmp(&aJudge[0], "NUM_MODEL") == 0)
			{//読み込んだ文字列が"NUM_MODEL"だった時
				fscanf(fp, "%s", &skipWord[0]);
				fscanf(fp, "%d", &g_loadFile.nMaxLoad);
			}
			if (strcmp(&aJudge[0], "MODEL_FILENAME") == 0)
			{//読み込んだ文字列が"MODEL_FILENAME"だった時
				fscanf(fp, "%s", &skipWord[0]);
				fscanf(fp, "%s", &g_loadFile.loadName[0]);

				D3DXLoadMeshFromX(&g_loadFile.loadName[0], D3DXMESH_SYSTEMMEM, pDevice, NULL, &pModelParts->pBuffMat, NULL, &pModelParts->nNumMat, &pModelParts->pMesh);

				pModelParts++;
			}
		}
		//ファイルを閉じる
		fclose(fp);
	}
	else
	{//失敗
	}
}

//========================================================
//			エネミーファイルの読み込み
//========================================================
void LoadEnemyFile(char *pfilename, EnemyModel *pEnemyModel)
{
	FILE *fp;											//ファイルポインタ

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ファイルを開く
	fp = fopen(pfilename, "r");

	if (fp != NULL)
	{//成功
		char skipWord[128];
		char aJudge[128];

		while (fscanf(fp, "%s", &aJudge[0]) != EOF)
		{
			int nCnt = 0;

			if (strcmp(&aJudge[0], "NUM_MODEL") == 0)
			{//読み込んだ文字列が"NUM_MODEL"だった時
				fscanf(fp, "%s", &skipWord[0]);
				fscanf(fp, "%d", &g_loadFile.nMaxLoad);
			}
			if (strcmp(&aJudge[0], "MODEL_FILENAME") == 0)
			{//読み込んだ文字列が"MODEL_FILENAME"だった時
				fscanf(fp, "%s", &skipWord[0]);
				fscanf(fp, "%s", &g_loadFile.loadName[0]);

				D3DXLoadMeshFromX(&g_loadFile.loadName[0], D3DXMESH_SYSTEMMEM, pDevice, NULL, &pEnemyModel->pBuffMat, NULL, &pEnemyModel->nNumMat, &pEnemyModel->pMesh);

				pEnemyModel++;
			}
		}
		//ファイルを閉じる
		fclose(fp);
	}
	else
	{//失敗
	}
}

//========================================================
//			モデルファイルの読み込み
//========================================================
void LoadModelFile(char *pfilename, ModelInfo *pModelInfo)
{
	FILE *fp;											//ファイルポインタ

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	//ファイルを開く
	fp = fopen(pfilename, "r");

	if (fp != NULL)
	{//成功
		char skipWord[128];
		char aJudge[128];

		while (fscanf(fp, "%s", &aJudge[0]) != EOF)
		{
			int nCnt = 0;

			if (strcmp(&aJudge[0], "NUM_MODEL") == 0)
			{//読み込んだ文字列が"NUM_MODEL"だった時
				fscanf(fp, "%s", &skipWord[0]);
				fscanf(fp, "%d", &g_loadFile.nMaxLoad);
			}
			if (strcmp(&aJudge[0], "MODEL_FILENAME") == 0)
			{//読み込んだ文字列が"MODEL_FILENAME"だった時
				fscanf(fp, "%s", &skipWord[0]);
				fscanf(fp, "%s", &g_loadFile.loadName[0]);

				D3DXLoadMeshFromX(&g_loadFile.loadName[0], D3DXMESH_SYSTEMMEM, pDevice, NULL, &pModelInfo->pBuffMatModel, NULL, &pModelInfo->nNumMatModel, &pModelInfo->pMeshModel);

				pModelInfo++;
			}
			//if(srcmp(&aJudge[0],""))
		}
		//ファイルを閉じる
		fclose(fp);
	}
	else
	{//失敗
	}
}
