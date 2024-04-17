#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"

GameScene::GameScene() {}

GameScene::~GameScene() {
	// デストラクタ
	delete sprite_;
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("fantasy_ryuukishi.png");

	//サウンドデータの読み込み
	soundDataHundle_ = audio_->LoadWave("punch1.wav");

	//音声の再生
	/*audio_->PlayWave(soundDataHundle_);*/

	//音声再生
	voiceHundle_ = audio_->PlayWave(soundDataHundle_, true);

	//スプライトの生成
	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	//モデルの生成
	model_ = Model::Create();

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//ビュープロジェクション
	viewProjection_.Initialize();

	//ライン描画が参照するビュープロジェクションを指定する(アドレス渡し)
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);

	//デバッグカメラ DebugCamera(画面の横幅,画面の縦幅)
	debugCamera_ = new DebugCamera(1280, 720);
}

void GameScene::Update() {

	//スプライトの今の座標を取得
	Vector2 position = sprite_->GetPosition();

	//座標を{ 2, 1 }移動
	position.x += 2.0f;
	position.y += 1.0f;

	//移動した座標をスプライトに反映
	sprite_->SetPosition(position);

	//スペースキーを押した瞬間
	if (input_->TriggerKey(DIK_SPACE))
	{
		//音声停止
		audio_->StopWave(voiceHundle_);
	}


	///--デバッグウィンドウ作成--
	//ImGui::Begin("Debug1");

	//デバッグテキストの表示
	//ImGui::Text("Kamata Tarou %d %d %d", 2050, 12, 31);
	
	//float3入力ボックス←これ便利！！
	//ImGui::InputFloat3("InputFloat3", inputFloat3);
	//float3スライダー←これ便利！！
	//ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 0.0f);

	//デモウィンドウの表示の有効化
	//ImGui::ShowDemoWindow();


	//ImGui::End();
	///--ここまで--

	//デバッグカメラの更新
	debugCamera_->Update();
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

	//3Dモデル描画(PreDrawとPostDrawの間に書く)
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);

	//ラインを描画する
	//PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//スプライトの描画(PreDrawとPostDrawの間に書く)
	/*sprite_->Draw();*/

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}