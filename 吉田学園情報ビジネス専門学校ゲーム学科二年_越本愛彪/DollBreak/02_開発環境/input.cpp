//========================================================
//
//	入力の処理[input.cpp]
//	AUTHIR:越本愛彪
//
//========================================================
#include "input.h"
#include <Windows.h>

//マクロ定義
#define NUM_KEY_MAX		(256)											//キーの最大数
#define NUM_MOUSE_MAX   (4)												//マウスの最大数

//グローバル変数
LPDIRECTINPUT8 g_pInput = NULL;											//DierectInputオブジェクトへのポインタ
LPDIRECTINPUT8 g_pInputMouse = NULL;
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;								//入力デバイスへのポインタ
LPDIRECTINPUTDEVICE8 g_pDevMouse = NULL;								//マウスデバイスへのポインタ
DIMOUSESTATE2 g_aMouseState;												//マウスの状態
DIMOUSESTATE2 g_aMouseStateTrigger;										//マウスのトリガー状態
BYTE g_aKeyState[NUM_KEY_MAX];											//キーボードのプレス情報
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];									//キーボードのトリガー情報
XINPUT_STATE g_joyKeyState;												//ジョイパッドのプレス情報
XINPUT_STATE g_joykeyStateTrigger;										//ジョイパッドのトリガー情報

//========================================================
//					ジョイパッドの初期化処理
//========================================================
HRESULT InitJoypad(void)
{
	//メモリのクリア
	memset(&g_joyKeyState, 0, sizeof(XINPUT_STATE));

	//xinputのステートを設定
	XInputEnable(true);

	return S_OK;
}

//========================================================
//				ジョイパッドの終了処理
//========================================================
void UninitJoypad(void)
{
	//Xinputのステートを設定
	XInputEnable(false);
}

//========================================================
//					ジョイパッドの更新処理
//========================================================
void UpdateJoypad(void)
{
	XINPUT_STATE joyKeyState;

	//ジョイパッドの状態を取得
	if (XInputGetState(0, &joyKeyState) == ERROR_SUCCESS)
	{
		g_joykeyStateTrigger.Gamepad.wButtons = (g_joyKeyState.Gamepad.wButtons ^ joyKeyState.Gamepad.wButtons) & joyKeyState.Gamepad.wButtons;
		g_joyKeyState = joyKeyState;							//ジョイパッドのプレス情報を保存
	}
}

//========================================================
//				ジョイパッドのプレス情報を取得
//========================================================
bool GetJoypadPress(JOYKEY key)
{
	return (g_joyKeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//========================================================
//				ジョイパッドのトリガー情報の取得
//========================================================
bool GetJoypadTrigger(JOYKEY key)
{
	return(g_joykeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//========================================================
//				キーボードの初期化処理
//========================================================
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

//========================================================
//					キーボードの終了処理
//========================================================
void UninitKeyboard(void)
{
	//入力デバイスの破棄
	if (g_pDevKeyboard != NULL)
	{
		g_pDevKeyboard->Unacquire();									//アクセス権の破棄
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

//========================================================
//					キーボードの更新処理
//========================================================
void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];										//キーボードのの入力情報

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			g_aKeyStateTrigger[nCntKey] = (g_aKeyState[nCntKey]
				^ aKeyState[nCntKey]) & aKeyState[nCntKey];				//トリガー情報の保存
			g_aKeyState[nCntKey] = aKeyState[nCntKey];					//プレス情報の保存
		}
	}
	else
	{
		//アクセス権の取得
		g_pDevKeyboard->Acquire();
	}
}

//========================================================
//					プレス情報の取得
//========================================================
bool GetKeyboardPress(int nkey)
{
	return (g_aKeyState[nkey] & 0x80) ? true : false;
}

//========================================================
//					トリガー情報の取得
//========================================================
bool GetKeyboardTrigger(int nKey)
{
	return(g_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}

//========================================================
//					マウスの初期化処理
//========================================================
HRESULT InitMouse(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT ret = S_FALSE;

	// DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInputMouse, NULL)))
	{
		return E_FAIL;
	}

	if (g_pInput == NULL)
	{
		return false;
	}

	//マウス用にデバイスオブジェクトを生成
	ret = g_pInputMouse->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL);
	if (FAILED(ret))
	{
		//デバイスの作成に失敗
		return false;
	}

	// データフォーマットを設定
	ret = g_pDevMouse->SetDataFormat(&c_dfDIMouse2);						// マウス用のデータ・フォーマットを設定
	if (FAILED(ret)) {
		// データフォーマットに失敗
		return false;
	}

	// モードを設定（フォアグラウンド＆非排他モード）
	ret = g_pDevMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(ret)) {
		// モードの設定に失敗
		return false;
	}

	// デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;									// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）

	ret = g_pDevMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	if (FAILED(ret)) {
		// デバイスの設定に失敗
		return false;
	}

	// 入力制御開始
	g_pDevMouse->Acquire();

	return true;
}

//========================================================
//					マウス終了処理
//========================================================
void UninitMouse(void)
{
	//入力デバイスの破棄
	if (g_pDevMouse != NULL)
	{
		g_pDevMouse->Unacquire();										//アクセス権の破棄
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	//DirectInputオブジェクトの破棄
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//========================================================
//					マウスの更新処理
//========================================================
void UpdateMouse(void)
{
	DIMOUSESTATE2 zdiMouseState_bak;										// マウス情報(変化検知用)

	//入力デバイスからデータを取得
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(zdiMouseState_bak), &zdiMouseState_bak)))
	{
		for (int nCntMouse = 0; nCntMouse < NUM_MOUSE_MAX; nCntMouse++)
		{
			g_aMouseStateTrigger.rgbButtons[nCntMouse] = (g_aMouseState.rgbButtons[nCntMouse]
				^ zdiMouseState_bak.rgbButtons[nCntMouse]) & zdiMouseState_bak.rgbButtons[nCntMouse];	
																		//トリガー情報の保存
		}
		g_aMouseState = zdiMouseState_bak;								//マウスの状態

	}
	else
	{
		//アクセス権の取得
		g_pDevMouse->Acquire();
	}
}

//========================================================
//					プレス情報の取得
//========================================================
bool GetMousePress(int nMouse)
{
	return (g_aMouseState.rgbButtons[nMouse] & 0x80) ? true : false;
}

//========================================================
//					トリガー情報の取得
//========================================================
bool GetMouseTrigger(int nMouse)
{
	return(g_aMouseStateTrigger.rgbButtons[nMouse] & 0x80) ? true : false;
}

//========================================================
//				マウスの移動量を取得
//========================================================
D3DXVECTOR3 GetMouseMove(void)
{
	return D3DXVECTOR3(g_aMouseState.lX,g_aMouseState.lY,g_aMouseState.lZ);
}