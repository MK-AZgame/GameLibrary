//=============================================================================
//
// 入力の処理 [input.cpp]
// Author : 越本　愛彪
//
//=============================================================================
#include "input.h"

//マクロ定義
#define NUM_KEY_MAX		(256)														//キーの最大数

//グローバル変数
LPDIRECTINPUT8 g_pInput = NULL;														//DierectInputオブジェクトへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;											//入力デバイスへのポインタ
BYTE g_aKeyState[NUM_KEY_MAX];														//キーボードのプレス情報
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];												//キーボードのトリガー情報
XINPUT_STATE g_joyKeyState;															//ジョイパッドのプレス情報
XINPUT_STATE g_joykeyStateTrigger;

//=============================================================================
//		ジョイパッドの初期化処理
//=============================================================================
HRESULT InitJoypad(void)
{
	//メモリのクリア
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	//xinputのステートを設定
	XInputEnable(true);

	return S_OK;
}

//=============================================================================
//		ジョイパッドの終了処理
//=============================================================================
void UninitJoypad(void)
{
	//Xinputのステートを設定
	XInputEnable(false);
}

//=============================================================================
//		ジョイパッドの更新処理
//=============================================================================
void UpdataJoypad(void)
{
	XINPUT_STATE joyKeyState;

	//ジョイパッドの状態を取得
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		g_joykeyStateTrigger.Gamepad.wButtons = (g_joyKeyState.Gamepad.wButtons ^ joyKeyState.Gamepad.wButtons) & joyKeyState.Gamepad.wButtons;
		g_joyKeyState = joyKeyState;												//ジョイパッドのプレス情報を保存
	}
}

//=============================================================================
//		ジョイパッドのプレス情報を取得
//=============================================================================
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//=============================================================================
//		ジョイパッドのトリガー情報の取得
//=============================================================================
bool GetJoypadTrigger(JOYKEY key)
{
	return(g_joykeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//=============================================================================
//		キーボードの初期化処理
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL)))
	{
		return E_FAIL;
	}

	//入力デバイスの生成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	//データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//協調モードの設定
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//キーボードのアクセス権を獲得
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//=============================================================================
//		キーボードの終了処理
//=============================================================================
void UninitKeyboard(void)
{
	//入力デバイスの破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();												//アクセス権の破棄
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//=============================================================================
//		キーボードの更新処理
//=============================================================================
void UpdataKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];													//キーボードのの入力情報

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey]
				^ aKeyState[nCntKey]) & aKeyState[nCntKey];							//トリガー情報の保存
			g_aKeyState[nCntKey] = aKeyState[nCntKey];								//プレス情報の保存
		}
	}
	else
	{
		//アクセス権の取得
		g_pDevKeyboard->Acquire();
	}
}

//=============================================================================
//		プレス情報の取得
//=============================================================================
bool GetKeyboardPress(int nkey)
{
	return (g_aKeyState[nkey] & 0x80) ? true : false;
}

//=============================================================================
//		トリガー情報の取得
//=============================================================================
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}