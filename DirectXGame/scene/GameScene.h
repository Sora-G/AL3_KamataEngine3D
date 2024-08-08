#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Enemy.h"
#include "DeathParticles.h"
#include "Skydome.h"
#include <vector>
#include "DebugCamera.h"
#include "MapChipField.h"
#include "CameraController.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {
	
public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 表示ブロックの生成
	/// </summary>
	void GenerateBlocks();

	//全ての当たり判定を行う
	void CheckAllCollisions();

	//フェーズの切り替え
	void ChangePhase();

	// デスフラグのgetter
	bool IsFinished() const { return isFinished_; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	//ビュープロジェクション生成
	ViewProjection viewProjection_;

	//3Dモデルの生成
	Model* model_ = nullptr;

	//プレイヤーの生成
	Player* player_ = nullptr;

	//敵の生成
	std::list<Enemy*> enemies_;

	//天球の生成
	Skydome* skydome_ = nullptr;

	//3Dモデル
	Model* modelSkydome_ = nullptr;

	//プレイヤーモデル
	Model* modelPlayer_ = nullptr;

	//敵のモデル
	Model* modelEnemy_ = nullptr;

	//デスパーティクルのモデル
	Model* modelDeathParticles_ = nullptr;

	// ゲームのフェーズ(型)
	enum class Phase {
		kPlay,  // ゲームプレイ
		kDeath, // デス演出
	};

	// ゲームの現在のフェーズ
	Phase phase_;

	//デスパーティクル
	DeathParticles* deathParticles_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//ブロックのモデルを読み込む
	Model* modelBlock_ = 0;

	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	//デバッグカメラの有効
	bool isDebugCameraActive_ = false;

	// デバッグカメラの生成
	DebugCamera* debugCamera_ = nullptr;
	
	//マップチップフィールド
	MapChipField* mapChipField_ = nullptr;

	//カメラコントローラー
	CameraController* cameraController_ = nullptr;

	// 終了フラグ
	bool isFinished_ = false; 

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
