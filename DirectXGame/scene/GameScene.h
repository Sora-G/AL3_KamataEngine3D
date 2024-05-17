#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Skydome.h"
#include <vector>
#include "DebugCamera.h"

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

	//天球の生成
	Skydome* skydome_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//ブロックのモデルを読み込む
	Model* modelBlock_ = 0;

	std::vector<std::vector<WorldTransform*>> worldTransformBlocks_;

	//デバッグカメラの有効
	bool isDebugCameraActive_ = false;

	// デバッグカメラの生成
	DebugCamera* debugCamera_ = nullptr;
	

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
