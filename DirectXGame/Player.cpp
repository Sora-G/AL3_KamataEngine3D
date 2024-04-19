#include "Player.h"
#include <cassert>

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection) {
	// Nullポインタチェック
	assert(model);

	// 引数として受け取ったデータをメンバ変数に記録する
	model_ = model;
	textureHundle_ = textureHandle;
	viewProjection_ = viewProjection;

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

/// <summary>
/// 更新処理
/// </summary>
void Player::Update() {
	//行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

/// <summary>
/// 描画処理
/// </summary>
void Player::Draw() { 
	model_->Draw(worldTransform_, viewProjection_, textureHundle_);
}
