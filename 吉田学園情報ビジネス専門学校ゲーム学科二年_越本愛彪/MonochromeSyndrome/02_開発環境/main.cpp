//=============================================================================
//
// メインの処理 [main.cpp]
// Author : 越本　愛彪
//
//=============================================================================
#include "main.h"
#include "player.h"
#include "bg.h"
#include "input.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "tutorial.h"

//マクロ定義
#define CLASS_NAME		 "WindowsClass"								//ウィンドウクラスの名前
#define Window_NAME		 "2Daction"									//ウィンドウの名前

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);

//グローバル変数
LPDIRECT3D9          g_pD3D = NULL;									//Direct3Dオブジェクトのポインタ
LPDIRECT3DDEVICE9    g_pD3DDevice = NULL;							//Direct3Dデバイスへのポインタ
MODE g_mode = MODE_TITLE;											//現在のモード

//=============================================================================
//		メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstanceprev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),											//WNDCLASSEXのメモリサイズ
		CS_CLASSDC,													//ウィンドウのスタイル
		WindowProc,													//ウィンドウプロシージャ
		0,															//
		0,															//
		hInstance,													//インスタンスハンドル
		LoadIcon(NULL,IDI_APPLICATION),								//タスクバーのアイコン
		LoadCursor(NULL,IDC_ARROW),									//マウスカーソル
		(HBRUSH)(COLOR_WINDOW + 1),									//クライアント領域の背景色
		NULL,														//メニューバー
		CLASS_NAME,													//ウィンドウクラスの名前
		LoadIcon(NULL,IDI_APPLICATION)								//ファイルのアイコン
	};

	HWND hWnd;														//ウィンドウハンドル
	MSG msg;														//メッセージの格納

	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };					//画面のサイズ

	//ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	//クライアント領域を指定のサイズに調整
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//ウィンドウを生成
	hWnd = CreateWindowEx(0,										//拡張ウィンドウスタイル
		CLASS_NAME,													//ウィンドウクラスの名前
		Window_NAME,												//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,										//ウィンドウスタイル
		CW_USEDEFAULT,												//ウィンドウの左上X座標
		CW_USEDEFAULT,												//ウィンドウの左上Y座標
		(rect.right - rect.left),									//ウィンドウの幅
		(rect.bottom - rect.top),									//ウィンドウの高さ
		NULL,														//親ウィンドウのハンドル
		NULL,														//メニューハンドル又は子ウィンドウID
		hInstance,													//インスタンスハンドル
		NULL);														//ウィンドウ作成データ

	DWORD dwCurrentTime;											//現在時刻
	DWORD dwExecLastTime;											//最後に処理した時刻

	//初期化処理
	if (FAILED(Init(hInstance, hWnd, FALSE)))
	{//初期化が失敗した場合
		return -1;
	}

	//分解能を設定
	timeBeginPeriod(1);
	dwCurrentTime = 0;												//初期化する
	dwExecLastTime = timeGetTime();									//現在時刻の取得

	//ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);										//ウィンドウの表示状態の設定
	UpdateWindow(hWnd);												//クライアント領域を更新

	//メッセージループ
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//Windowsの処理
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//メッセージの設定
				TranslateMessage(&msg);								//仮想メッセージを文字メッセージへ変換
				DispatchMessage(&msg);								//ウィンドウプロシージャへメッセージを送出
			}
		}
		else
		{//DirectXの処理
			dwCurrentTime = timeGetTime();							//現在時刻を取得

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{//60分の1秒経過
				dwExecLastTime = dwCurrentTime;						//処理開始時刻を保存

				//更新処理
				Update();

				//描画処理
				Draw();
			}
		}
	}

	//終了処理
	Uninit();

	//分解能を戻す
	timeEndPeriod(1);

	//ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return(int)msg.wParam;
}

//=============================================================================
//		ウィンドウプロシージャ
//=============================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;														//返り値を格納
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };			//ウィンドウの領域

	switch (uMsg)
	{
	case WM_DESTROY:
		//WM_QUITメッセージを送る
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:												//キー押下のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:												//[ESC]キーが押された
			nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO|MB_TOPMOST);

			if (nID == IDYES)
			{
				//ウィンドウを破棄する(WM_DESTOROYメッセージを送る）
				DestroyWindow(hWnd);
			}
			break;
		}
		break;

	case WM_CLOSE:													//閉じるボタン押下のメッセージ
		nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO);

		if (nID == IDYES)
		{
			//ウィンドウを破棄する(WM_DESTOROYメッセージを送る）
			DestroyWindow(hWnd);
		}
		else
		{
			return 0;
		}
		break;

	case WM_LBUTTONDOWN:											//マウス左クリックのメッセージ
																	//ウィンドウにフォーカスを合わせる
		SetFocus(hWnd);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);				//既定の処理を返す
}

//=============================================================================
//		初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;											//ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;									//プレゼンテーションパラメータ

	//Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}

	//現在のディスプレイモードを取得
	if (g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm))
	{
		return E_FAIL;
	}

	//デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								//パラメータのゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							//ゲーム画面サイズ（幅）
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							//ゲーム画面サイズ（高さ）
	d3dpp.BackBufferFormat = d3ddm.Format;							//バックバッファの形成
	d3dpp.BackBufferCount = 1;										//バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						//ダブルバッファの切り替え
	d3dpp.EnableAutoDepthStencil = TRUE;							//デプスバッファとステンシルバッファを形成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						//デプスバッファとして１６bitを使う
	d3dpp.Windowed = bWindow;										//ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		//リフレッシュレート
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//インターバル

																	//Direct3Dデバイスの生成（描画処理と頂点処理をハードウェアで行う）
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		//Direct3Dデバイスの生成（描画処理はハードウェア、頂点処理はCPUで行う）
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			//Direct3Dデバイスの生成(描画処理と頂点処理をCPUで行う)
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	//レンダーステートの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//キーボードの初期化
	if (FAILED(InitKeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//各種オブジェクトの初期化処理
	//サウンドの初期化
	InitSound(hWnd);
	//フェードの初期化
	InitFade(g_mode);

	return S_OK;
}

//=============================================================================
//		終了処理
//=============================================================================
void Uninit(void)
{
	//各種オブジェクトの終了処理
	//フェードの終了
	UninitFade();
	//タイトル画面の終了
	UninitTitle();
	//ゲーム画面の終了
	UninitGame();
	//リザルト画面の終了
	UninitResult();
	////サウンドの終了処理
	UninitSound();
	//キーボードの終了
	UninitKeyboard();
	//ジョイパッドの終了処理
	UninitJoypad();

	//Direct3Dデバイスの破棄
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}
	//Direct3Dオブジェクトの破棄
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//=============================================================================
//		更新処理
//=============================================================================
void Update(void)
{
	//キーボードの更新
	UpdataKeyboard();
	//ジョイパッドの更新処理
	UpdataJoypad();
	//各種オブジェクトの更新処理
	switch (g_mode)
	{
	case MODE_TITLE:
		UpdataTitle();
		break;
	case MODE_GAME:
		UpdataGame();
		break;
	case MODE_RESULT:
		UpdataResult();
		break;
	case MODE_TUTORIAL:
		UpdataTutorial();
		break;
	}

	//フェードの更新
	UpdataFade();
}

//=============================================================================
//		描画処理
//=============================================================================
void Draw(void)
{
	//画面クリア
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//描画開始が成功した場合
	 //各種オブジェクトの描画処理
		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;
		case MODE_GAME:
			DrawGame();
			break;
		case MODE_RESULT:
			DrawResult();
			break;
		case MODE_TUTORIAL:
			DrawTutorial();
			break;
		}

		//フェードの描画
		DrawFade();

		//描画終了
		g_pD3DDevice->EndScene();
	}
	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
//		モードの設定
//=============================================================================
void SetMode(MODE mode)
{
	//現在のモードの終了処理
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;
	case MODE_GAME:
		UninitGame();
		break;
	case MODE_RESULT:
		UninitResult();
		break;
	case MODE_TUTORIAL:
		UninitTutorial();
		break;
	}

	//新しい画面の初期化処理
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;
	case MODE_GAME:
		InitGame();
		break;
	case MODE_RESULT:
		InitResult();
		break;
	case MODE_TUTORIAL:
		InitTutorial();
		break;
	}

	g_mode = mode;
}

//=============================================================================
//		デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}