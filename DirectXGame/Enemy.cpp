#include "Enemy.h"
#include <numbers>

void Enemy::Initialize(Model* model, const Vector3& position) 
{
	//モデルをメンバ変数に記録
	model_ = model; 

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	//初期座標の設定
	worldTransform_.translation_ = position;

	//向きの設定
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;
}

void Enemy::Update() 
{
	//座標を基に行列の更新を行う
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw() 
{
	//ワールドトランスフォームとビュープロジェクションを渡して３Dモデルを描画する
	model_->Draw(worldTransform_, *viewProjection_); 
}
