#define NOMINMAX
#define NOMINMIN
#include "CameraController.h"
#include "Player.h"


void CameraController::Initialize() 
{ 
	//ビュープロジェクションの初期化
	viewProjection_.Initialize(); 
}

void CameraController::Update() 
{
	const Vector3& targetVelocity = target_->GetVelocity();

	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetTransform = target_->GetWorldTransform();
	// 追従対象とオフセットから	カメラの座標を計算
	targetCoordinate_ = targetTransform.translation_ + targetOffset_ + targetVelocity * kVelocityBias;

	//座標補間によりゆったり追従
	viewProjection_.translation_ = Lerp(viewProjection_.translation_, targetCoordinate_, kInterpolationRate);

	//移動範囲制限
	viewProjection_.translation_.x = std::max(viewProjection_.translation_.x, movableArea_.left);
	viewProjection_.translation_.x = std::min(viewProjection_.translation_.x, movableArea_.right);
	viewProjection_.translation_.y = std::max(viewProjection_.translation_.y, movableArea_.bottom);
	viewProjection_.translation_.y = std::min(viewProjection_.translation_.y, movableArea_.top);

	//追従対象が画面外に出ないように補正
	viewProjection_.translation_.x = std::max(viewProjection_.translation_.x, targetCoordinate_.x + margin.left);
	viewProjection_.translation_.x = std::min(viewProjection_.translation_.x, targetCoordinate_.x + margin.right);
	viewProjection_.translation_.y = std::max(viewProjection_.translation_.y, targetCoordinate_.y + margin.bottom);
	viewProjection_.translation_.y = std::min(viewProjection_.translation_.y, targetCoordinate_.x + margin.top);


	//行列を更新する
	viewProjection_.UpdateMatrix();
}

void CameraController::Reset() 
{
	//追従対象のワールドトランスフォームを参照
	const WorldTransform& targetTransform = target_->GetWorldTransform();
	//追従対象とオフセットから	カメラの座標を計算
	viewProjection_.translation_ = targetTransform.translation_ + targetOffset_;
}
