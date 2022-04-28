#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	const int WindowWidth = 1024;
	const int WindowHeight = 576;

	ChangeWindowMode(true);							//ウィンドウモードにする
	SetGraphMode(WindowWidth, WindowHeight, 32);	//画面モードのセット
	SetBackgroundColor(0, 0, 64);					//背景色 RGB
	if (DxLib_Init() == -1) return -1;				//DxLib初期化設定
	SetDrawScreen(DX_SCREEN_BACK);					//描画先画面を裏画面にセット

	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();			//画面を消去

		//更新

		//描画
		DrawCircle(WindowWidth / 2, WindowHeight / 2, 16, GetColor(128, 255, 128));	//円を描画

		//フリップする
		ScreenFlip();
	}
	DxLib_End();	//DxLib 終了画面
	return 0;		//ソフトの終了
}