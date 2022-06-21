//========================================================
//
//	爆発の処理[explosion.cpp]
//	AUTHOR:越本愛彪
//
//========================================================
#include "main.h"
#include "enemy.h"
#include "explosion.h"
#include "effect.h"

//マクロ定義
#define MAX_TIME (30)					//ボムの呼び出し時間
#define MAX_BOMB (128)

//エフェクト呼び出しの構造体
typedef struct
{
	D3DXVECTOR3 pos;					//位置
	D3DXVECTOR3 move;					//移動量
	D3DXCOLOR col;						//色
	float fRadius;						//半径
	int nLife;							//寿命
	bool bUse;
} EXPLOSION;

//グローバル変数
EXPLOSION g_Explosion[MAX_BOMB];		//ボムの情報を格納
int g_nCountExplosion;

//========================================================
//			ボムの初期化処理
//========================================================
void InitExplosion(void)
{
	int nCountExplosion;

	for (nCountExplosion = 0; nCountExplosion < MAX_BOMB; nCountExplosion++)
	{
		g_Explosion[nCountExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_Explosion[nCountExplosion].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
		g_Explosion[nCountExplosion].fRadius = 0.0f;
		g_Explosion[nCountExplosion].nLife = 0;
		g_Explosion[nCountExplosion].bUse = false;
	}

	g_nCountExplosion = 0;
}

//========================================================
//			ボムの終了処理
//========================================================
void UninitExplosion(void)
{
	
}

//========================================================
//			ボムの更新処理
//========================================================
void UpdateExplosion(void)
{
	float fmove;
	int nCountExplosion;

	for (nCountExplosion = 0; nCountExplosion < MAX_BOMB; nCountExplosion++)
	{
		if (g_Explosion[nCountExplosion].bUse == true)
		{
			for (g_nCountExplosion = 0; g_nCountExplosion < MAX_TIME; g_nCountExplosion++)
			{
				fmove = (float)(rand() % 629);

				fmove -= 314.0f;
				fmove /= 100;

				g_Explosion[nCountExplosion].move.x -= sinf(fmove)*0.1f;
				g_Explosion[nCountExplosion].move.y -= cosf(fmove)*0.1f;

				g_Explosion[nCountExplosion].nLife = rand() % 20 + 5;
				g_Explosion[nCountExplosion].fRadius = (float)(rand() % 20 + 10);

				SetEffect(g_Explosion[nCountExplosion].pos, g_Explosion[nCountExplosion].move, g_Explosion[nCountExplosion].col, g_Explosion[nCountExplosion].fRadius, g_Explosion[nCountExplosion].nLife);
			}

			g_Explosion[nCountExplosion].bUse = false;
		}
	}
}

//========================================================
//			ボムの設定処理
//========================================================
void SetExplosion(D3DXVECTOR3 pos)
{
	D3DXCOLOR ExplosionColor = D3DXCOLOR(1.0f,0.8f,0.1f,0.5f);
	int nCountExplosion;

	for (nCountExplosion = 0; nCountExplosion < MAX_BOMB; nCountExplosion++)
	{
		if (g_Explosion[nCountExplosion].bUse == false)
		{
			g_Explosion[nCountExplosion].pos = pos;
			g_Explosion[nCountExplosion].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			g_Explosion[nCountExplosion].col = ExplosionColor;
			g_Explosion[nCountExplosion].fRadius = 40.0f;
			g_Explosion[nCountExplosion].nLife = 50;
			g_Explosion[nCountExplosion].bUse = true;
		}
	}
}

