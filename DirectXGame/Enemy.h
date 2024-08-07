#pragma once
#include "Model.h"
#include "WorldTransform.h"

/// <summary>
/// 敵
/// </summary>
class Enemy
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, const Vector3& position);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();


private:

	//ワールドトランスフォーム
	WorldTransform worldTransform_;

	//モデルのポインタ
	Model* model_ = nullptr;

	//ビュープロジェクション
	ViewProjection* viewProjection_ = nullptr;
};