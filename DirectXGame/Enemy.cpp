#include "Enemy.h"
#include <cassert>
#include <numbers>
#include "MathUtilityForText.h"

void Enemy::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) 
{
	//NULLポインタチェック
	assert(model);

	// モデルをメンバ変数に記録
	model_ = model;
	viewProjection_ = viewProjection;
	// 初期座標の設定
	worldTransform_.translation_ = position;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// 向きの設定
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / -2.0f;

	//速度を設定する
	velocity_ = {-kWalkSpeed, 0, 0};

	walkTimer_ = 0.0f;
}

void Enemy::Update() 
{
	//移動
	worldTransform_.translation_ += velocity_;

	//タイマーを加算
	walkTimer_ += 1.0f / 60.0f;

	//簡易版の計算
	worldTransform_.rotation_.x = std::sin(2.0f * std::numbers::pi_v<float> * walkTimer_ / kWalkMotionTime);

	//行列の更新
	worldTransform_.UpdateMatrix();
}

void Enemy::Draw() 
{
	//ワールドトランスフォームとビュープロジェクションを渡して３Dモデルを描画する
	model_->Draw(worldTransform_, *viewProjection_); 
}

//ワールド座標を取得
Vector3 Enemy::GetWorldPosition() 
{
	//ワールド座標を入れる変数
	Vector3 worldPos; 
	//ワールド行列の平行移動成分を取得（ワールド座標）
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

//AABBを取得
AABB Enemy::GetAABB() 
{
	Vector3 worldPos = GetWorldPosition();
	
	AABB aabb;
	
	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

void Enemy::OnCollision(const Player* player) { (void)player; }

void Enemy::OnCollision(const Enemy* enemy) 
{ 
	(void)enemy;
	//ジャンプ開始
	velocity_ += Vector3(0.0f, 2.0f, 0.0f);
}
