#include "DxLib.h"
#include "Vector3.h"


//球の描画
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

//線分の描画
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color);

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	const int WindowWidth = 1024;
	const int WindowHeight = 576;

	ChangeWindowMode(true);							//ウィンドウモードにする
	SetGraphMode(WindowWidth, WindowHeight, 32);	//画面モードのセット
	SetBackgroundColor(0, 0, 64);					//背景色 RGB
	if (DxLib_Init() == -1) return -1;				//DxLib初期化設定
	SetDrawScreen(DX_SCREEN_BACK);					//描画先画面を裏画面にセット

	//クリップ面	  近	 遠
	SetCameraNearFar(1.0f, 1000.0f);		//カメラの有効範囲を設定
	SetCameraScreenCenter(WindowWidth / 2.0f, WindowHeight / 2.0f);	//画面の中心をカメラの中心に合わせる
	SetCameraPositionAndTargetAndUpVec(
		VGet(0.0f, 0.0f, -100.0f),	//カメラの位置
		VGet(0.0f, 0.0f, 0.0f),		//カメラの注視点
		VGet(0.0f, 1.0f, 0.0f));	//カメラの上の向き

	Vector3 position(0, 0, 0);			//位置
	Vector3 velocity(0.0f, 0.0f, 0.5f); //速度

	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//更新
		position += velocity;

		//描画
		ClearDrawScreen();	//画面を消去
		DrawSphere3D(position, 80.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);

		//フリップする
		ScreenFlip();
	}
	DxLib_End();	//DxLib 終了画面
	return 0;		//ソフトの終了
}

//Vector3型を利用しやすくするためのオーバーロード関数群

//球の描画
//DxLib -> int DrawSphere3D(VECTOR, float r,int DivNum, unsigned int DifColor, unsigned int SpcColor, int FillFlag);
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag)
{
	VECTOR centerPos = { CenterPos.x,CenterPos.y,CenterPos.z };	//構造体 初期化子リスト

	return DrawSphere3D(centerPos, r, DivNum, DifColor, SpcColor, FillFlag);	//DxLib関数の呼び出し
}

//線分の描画
//DxLib -> int DrawLine3D(VECTOR Pos1, VECTOR Pos2, unsigned int Color);
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color)
{
	VECTOR p1 = { Pos1.x,Pos1.y,Pos1.z }; //構造体 初期化子リスト
	VECTOR p2 = { Pos2.x,Pos2.y,Pos2.z }; //構造体 初期化子リスト

	return DrawLine3D(p1, p2, Color);	  //DxLib関数の呼び出し
}