#pragma once
#include "Model.h"
#include "WorldTransform.h"

/// <summary>
///	自キャラ
/// </summary>
class Player {

public:
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();


	private:

		//ワールド変換データ
		WorldTransform worldTransform_;

		//モデル
	    Model* model_ = nullptr;

		//
	    ViewProjection* viewProjection_ = nullptr;


		//テクスチャハンドル
	    uint32_t textureHundle_ = 0u;
};