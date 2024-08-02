#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "MathUtilityForText.h"

enum class LRDirection 
{ 
	kRight, kLeft 
};

class MapChipField;

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
	void Initialize(Model* model, ViewProjection* viewProjection,const Vector3& position);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	const WorldTransform& GetWorldTransform() const { return worldTransform_; }

	const Vector3& GetVelocity() const { return velocity_; }

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	void InputMove();

	struct  CollisionMapInfo 
	{
		bool ceiling = false;//天井衝突フラグ
		bool landing = false;//着地フラグ
		bool hitWall = false;
		Vector3 move;
	};

	void CheckMapCollision(CollisionMapInfo& info);
	void CheckMapCollisionUp(CollisionMapInfo& info);
	void CheckMapCollisionDown(CollisionMapInfo& info);
	void CheckMapCollisionRight(CollisionMapInfo& info);
	void CheckMapCollisionLeft(CollisionMapInfo& info);

	//角
	enum Corner
	{
		kRightBottom,
		kLeftBottom,
		kRightTop,
		kLeftTop,
		kNumCorner
	};

	Vector3 CornerPosition(const Vector3& center, Corner corner);

	void CheckMapChipCollisionHit(const CollisionMapInfo& info);

	void CellingContactHit(const CollisionMapInfo& info);

	void CellingSwitch(const CollisionMapInfo& info);

private:
	//マップチップによるフィールド
	MapChipField* mapChipField_ = nullptr;

	// ワールド変換データ
	WorldTransform worldTransform_;

	// モデル
	Model* model_ = nullptr;

	//
	ViewProjection* viewProjection_ = nullptr;

	Vector3 velocity_ = {};

	static inline const float kAcceleration = 0.01f;
	static inline const float kAttenuation = 0.01f;
	static inline const float kLimitRunSpeed = 0.1f;

	LRDirection lrDirection_ = LRDirection::kRight;

	//旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	//旋回タイマー
	float turnTimer_ = 0.0f;

	//旋回時間<秒>
	static inline const float kTimeTurn = 0.5f;

	//接地状態フラグ
	bool onGround_ = true;

	//重力加速度
	static inline float kGravityAcceleration = 0.5f;
	//最大落下速度
	static inline float kLimitFallSpeed = 0.3f;
	//ジャンプ初速
	static inline float kJumpAcceleration = 1.5f;

	static inline const float kBlank = 5.0f;

	//プレイヤーの当たり判定
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;

	//着地時の速度減衰率
	static inline const float kAttenuationLanding = 1.0f;
};