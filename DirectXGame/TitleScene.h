#pragma once
#include "Input.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DirectXCommon.h"


/// <summary>
/// タイトルシーン
/// </summary>
class TitleScene
{
public:

	TitleScene();
	~TitleScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	//デスフラグのgetter
	bool IsFinished() const { return isFinished_; }

private:

	//終了フラグ
	bool isFinished_ = false; 
	Model* modelFont_ = nullptr;
	Model* modelPlayer_ = nullptr;

	//ビュープロジェクション
	ViewProjection viewProjection_;

	WorldTransform worldTransformFont_;
	WorldTransform worldTransformPlayer_;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;

	float timer_ = 0.0f;
	static inline const float kMotionTime = 1.0f;


};