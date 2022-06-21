//===============================================================
//
//	ファイル読み込みの処理[loadfile.h]
//	AUTHOR:越本愛彪
//
//===============================================================
#ifndef _LOADFILE_H_
#define _LOADFILE_H_

#include "main.h"
#include "player.h"
#include "enemy.h"
#include "model.h"

//ファイル読み込みの構造体
typedef struct
{
	char loadName[256];
	int  nMaxLoad;
} LOADFILE;

//読み込む情報の種類
typedef enum
{
	ROADTYPE_PLAYER = 0,
	LOADTYPE_ENEMY = 1,
	LOADTYPE_MODEL = 2,
	ROADTYPE_MAX
} LOADTYPE;

//プロトタイプ宣言
void LoadMotionFile(char *pfilename,ModelParts *pModelParts);	//モーションファイル読み込み様関数
void LoadEnemyFile(char *pfilename, EnemyModel *pEnemyModel);	//エネミーファイル読み込み関数
void LoadModelFile(char *pfilename, ModelInfo *ModelInfo);		//モデルファイルの読み込み

#endif