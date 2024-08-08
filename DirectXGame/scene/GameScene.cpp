#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "MathUtilityForText.h"

//コンストラクタ
GameScene::GameScene() {}

//デストラクタ
GameScene::~GameScene() { 
	
	delete model_;

	delete player_;

	for (Enemy* enemy : enemies_)
	{
		delete enemy;
	}

	delete deathParticles_;

	delete skydome_;

	delete modelSkydome_;

	delete modelBlock_;

	delete mapChipField_;

	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	//worldTransformBlocks_.clear();

	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ビュープロジェクション生成
	viewProjection_.Initialize();
	viewProjection_.farZ = 500;


	//3Dモデルデータの生成
	model_ = Model::Create();

	// 画像の読み込み
	textureHandle_ = TextureManager::Load("fantasy_ryuukishi.png");

	//３Dモデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	//プレイヤーモデルの生成
	modelPlayer_ = Model::CreateFromOBJ("player", true);

	//敵のモデルの生成
	modelEnemy_ = Model::CreateFromOBJ("enemy", true);

	//デスパーティクルのモデルの生成
	modelDeathParticles_ = Model::CreateFromOBJ("deathParticle", true);

	//ゲームプレイフェーズから開始
	phase_ = Phase::kPlay;

	//座標をマップチップ番号で指定
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(1, 18);

	// 天球の生成
	skydome_ = new Skydome();
	// 天球の初期化
	skydome_->Initialize(modelSkydome_, &viewProjection_);

	// ブロックのモデルを読み込む
	modelBlock_ = Model::CreateFromOBJ("block",true);

	////要素数
	//const uint32_t kNumBlockVirtical = 10;
	//const uint32_t kNumBlockHorizontal = 20;
	////ブロック1個分の横幅
	//const float kBlockWidth = 1.0f;
	//const float kBlockHeight = 1.0f;
	////要素数を変更する
	////配列を設定
	//worldTransformBlocks_.resize(kNumBlockVirtical);
	//for (uint32_t i = 0; i < kNumBlockVirtical; i++) {
	//	// １列の要素数を設定
	//	worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	//}

	////キューブの生成
	//for (uint32_t i = 0; i < kNumBlockVirtical; i++) {
	//	for (uint32_t j = 0; j < kNumBlockHorizontal; j++) {

	//		//if文＋continueで表示しないブロックを指定できる
	//		if ((i + j) % 2 == 0)
	//			continue;

	//		worldTransformBlocks_[i][j] = new WorldTransform();
	//		worldTransformBlocks_[i][j]->Initialize();
	//		worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j;
	//		worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i;
	//	}
	//}

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// マップチップフィールドの生成と初期化
	mapChipField_ = new MapChipField();
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");
	// 表示ブロックの生成
	GenerateBlocks();

	// プレイヤーの生成と初期化
	player_ = new Player();
	player_->Initialize(modelPlayer_, &viewProjection_, playerPosition);

	player_->SetMapChipField(mapChipField_);
	
	//敵の生成と初期化
	for (int32_t i = 0; i < 3; ++i)
	{
		Enemy* newEnemy = new Enemy();
		Vector3 enemyPosition = mapChipField_->GetMapChipPositionByIndex(11 + i * 3, 18 - i);
		newEnemy->Initialize(modelEnemy_, &viewProjection_, enemyPosition);
		enemies_.push_back(newEnemy);
	}

	player_->Update();
	Vector3 position = player_->GetWorldPosition();
	// デスパーティクルの生成（仮）
	deathParticles_ = new DeathParticles;
	deathParticles_->Initialize(modelDeathParticles_, &viewProjection_, position);

	// カメラコントローラーの初期化
	cameraController_ = new CameraController();
	cameraController_->Initialize();
	cameraController_->SetTarget(player_);
	cameraController_->Reset();

	CameraController::Rect cameraArea = {12.0f, 100 - 12.0f, 6.0f, 6.0f};
	cameraController_->SetMovableArea(cameraArea);
}

void GameScene::Update() {

	ChangePhase();

#ifdef _DEBUG

	if (input_->TriggerKey(DIK_SPACE))
	{
		isDebugCameraActive_ = true;
	}

#endif // _DEBUG

	if (isDebugCameraActive_) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		//ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.matView = cameraController_->GetViewProjection().matView;
		viewProjection_.matProjection = cameraController_->GetViewProjection().matProjection;
		//ビュープロジェクション行列の更新と転送
		viewProjection_.TransferMatrix();
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// プレイヤーの描画処理
	player_->Draw();

	//敵の描画処理
	for (Enemy* enemy : enemies_)
	{
		enemy->Draw();
	}

	//デスパーティクルの描画
	deathParticles_->Draw();

	// 天球の描画処理
	skydome_->Draw();

	//ブロックの描画
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock)
				continue;
			modelBlock_->Draw(*worldTransformBlock, viewProjection_);
		}
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::GenerateBlocks() 
{
	// 要素数
	uint32_t kNumBlockVirtical = mapChipField_->GetNumBlockVirtical();
	uint32_t kNumBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	// 要素数を変更する
	// 列数を設定
	worldTransformBlocks_.resize(kNumBlockVirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; i++) {
		// １列の要素数を設定
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}

	// キューブの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; i++) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; j++) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock)
			{
				WorldTransform* worldTransform = new WorldTransform();
				worldTransform->Initialize();
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}

void GameScene::CheckAllCollisions() 
{
	#pragma region
	{
		// 対象１と２の座標
		AABB aabb1, aabb2;

		// 自キャラの座標
		aabb1 = player_->GetAABB();

		// 自キャラと敵弾全ての当たり判定
		for (Enemy* enemy : enemies_) {
			// 敵弾の座標
			aabb2 = enemy->GetAABB();

			// AABB同士の交差判定
			if (IsCollision(aabb1, aabb2))
			{
				//自キャラの衝突時コールバックを呼び出す
				player_->OnCollision(enemy);
				//敵弾の衝突時コールバックを呼び出す
				enemy->OnCollision(player_);
			}
			
		}
	}
	#pragma endregion
}

void GameScene::ChangePhase() 
{
	switch (phase_) {
	case Phase::kPlay:
		/// ゲームプレイフェーズの処理
		// 天球の更新
		skydome_->Update();

		// プレイヤーの更新
		player_->Update();
		Vector3 position = player_->GetWorldPosition();

		// 敵の更新
		for (Enemy* enemy : enemies_) {
			enemy->Update();
		}

		// カメラコントローラーの更新
		cameraController_->Update();

		// デバッグカメラの更新
		debugCamera_->Update();

		// ブロックの更新
		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {

			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

				if (!worldTransformBlock)
					continue;

				worldTransformBlock->UpdateMatrix();
			}
		}

		// 全ての当たり判定を行う
		CheckAllCollisions();

		if (player_->IsDead())
		{
			//デス演出フェーズに切り替え
			phase_ = Phase::kDeath;
			//自キャラの座標を取得
			const Vector3& deathParticlePosition = player_->GetWorldPosition();
			//自キャラの座標にデスパーティクルを発生、初期化
			deathParticles_->Initialize(modelDeathParticles_, &viewProjection_, deathParticlePosition);
		}

		break;


	case Phase::kDeath:
		/// デス演出フェーズの処理
		// 天球の更新
		skydome_->Update();

		// 敵の更新
		for (Enemy* enemy : enemies_) {
			enemy->Update();
		}

		// デスパーティクルの更新
		deathParticles_->Update();

		// デバッグカメラの更新
		debugCamera_->Update();

		// ブロックの更新
		for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {

			for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

				if (!worldTransformBlock)
					continue;

				worldTransformBlock->UpdateMatrix();
			}
		}

		if (deathParticles_ && deathParticles_->IsFinished())
		{
			isFinished_ = true;
		}

		break;
	}
}
