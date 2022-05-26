#include "DxLib.h"
#include "Vector3.h"


//球の描画
int DrawSphere3D(const Vector3& CenterPos, const float r, const int DivNum,
	const unsigned int DifColor, const unsigned int SpcColor, const int FillFlag);

//線分の描画
int DrawLine3D(const Vector3& Pos1, const Vector3& Pos2, const unsigned int Color);

//カメラの位置と姿勢の設定
// DxLib => int SetCameraPositionAndTargetAndUpVec(VECTOR Position, VECTOR Target, VECTOR Up);
int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,	//カメラの位置
	const Vector3& cameraTarget,	//カメラの注意点
	const Vector3& cameraUp			//カメラの上の向き
);

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
	Vector3 cameraPosition(0.0f, 0.0f, -30.0f);
	//Vector3 cameraPosition(0.0f, 10.0f, 30.0f);
	Vector3 cameraTarget  (0.0f, 0.0f, 0.0f);
	Vector3 cameraUp	  (0.0f, 1.0f, 0.0f);

	SetCameraPositionAndTargetAndUpVec(
		cameraPosition,		//カメラの位置
		cameraTarget,		//カメラの注視点
		cameraUp);			//カメラの上の向き

	Vector3 A(3, -1, 2);
	Vector3 B(1, 5, -4);
	Vector3 C(-1, 7, 6);

	Vector3 AB = B - A;	//ABベクトルの生成
	Vector3 BC = C - B;	//BCベクトルの生成

	Vector3 n = AB.cross(BC);	//法線ベクトルを求める(ABベクトルとBCベクトルの外積を求める)
	n.normalize();				//法線ベクトルの単位ベクトル化

	float th = 270.0f;	//カメラが回る

	//ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//更新
		/*th += 0.2f;
		float radian = th * PI / 180.0f;
		cameraPosition = Vector3(std::cosf(radian) * 30, 0.0f, std::sinf(radian)*30);

		SetCameraPositionAndTargetAndUpVec(
			cameraPosition,
			cameraTarget,
			cameraUp
		);*/

		Vector3 v = cameraPosition - (A + B + C) / 3.0f;	//視点への方向ベクトル
		v.normalize();

		unsigned color = GetColor(255, 255, 255);

		if (v.dot(n) < 0)
		{
			color = GetColor(255, 0, 0);
		}

		//描画
		ClearDrawScreen();	//画面を消去

		DrawLine3D(A, B, color);
		DrawLine3D(B, C, color);
		DrawLine3D(C, A, color);

		//法線の視覚化
		DrawLine3D(A, A + n, GetColor(0, 255, 0));
		DrawLine3D(B, B + n, GetColor(0, 255, 0));
		DrawLine3D(C, C + n, GetColor(0, 255, 0));

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

int SetCameraPositionAndTargetAndUpVec(
	const Vector3& cameraPosition,	//カメラの位置
	const Vector3& cameraTarget,	//カメラの注意点
	const Vector3& cameraUp			//カメラの上の向き
) {
	VECTOR position = { cameraPosition.x,cameraPosition.y,cameraPosition.z };
	VECTOR target = { cameraTarget.x,cameraTarget.y,cameraTarget.z };
	VECTOR up = { cameraUp.x,cameraUp.y,cameraUp.z };

	return SetCameraPositionAndTargetAndUpVec(position, target, up);
}
