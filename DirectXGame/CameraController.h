#pragma once
#include "ViewProjection.h"
#include "MathUtilityForText.h"

class Player;

/// <summary>
/// カメラコントローラー
/// </summary>
class CameraController 
{
public:

	struct Rect {
		float left = 0.0f;
		float right = 1.0f;
		float bottom = 0.0f;
		float top = 1.0f;
	};

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	//セッター
	void SetTarget(Player* target) { target_ = target; }

	//ゲッター
	const ViewProjection& GetViewProjection() const { return viewProjection_; }

	//リセット
	void Reset();

	void SetMovableArea(Rect area) { movableArea_ = area; }


private:

	//ビュープロジェクション
	ViewProjection viewProjection_;

	Player* target_ = nullptr;

	//追従対象とカメラ座標の差（オフセット）
	Vector3 targetOffset_ = {0.0f, 0.0f, -15.0f};

	//カメラ移動範囲
	Rect movableArea_ = {0, 100, 0, 100};

	//目標地点
	Vector3 targetCoordinate_ = {};

	//座標補間割合
	static inline const float kInterpolationRate = 0.1f;

	//速度掛け算
	static inline const float kVelocityBias = 25.0f;

	//追従対象の各方向へのカメラ移動範囲
	static inline const Rect margin = {-640.0f, 640.0f, -360.0f, 360.0f};
};