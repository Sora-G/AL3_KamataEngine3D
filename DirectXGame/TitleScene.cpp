#include "TitleScene.h"
#include <numbers>

TitleScene::TitleScene() {}

TitleScene::~TitleScene() 
{ 
	delete modelFont_;
	delete modelPlayer_;
}

void TitleScene::Initialize() 
{
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();

	modelFont_ = Model::CreateFromOBJ("titleFont");
	modelPlayer_ = Model::CreateFromOBJ("player");

	viewProjection_.Initialize();

	worldTransformFont_.Initialize();
	worldTransformPlayer_.Initialize();
}

void TitleScene::Update() 
{
	//タイトルシーンの終了条件
	if (Input::GetInstance()->PushKey(DIK_SPACE))
	{
		isFinished_ = true;
	}
}

void TitleScene::Draw() 
{
	//コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	//3Dオブジェクト描画処理
	Model::PreDraw(commandList);

	///ここに3Dオブジェクトの描画処理を追加できる
	modelFont_->Draw(worldTransformFont_, viewProjection_);
	modelPlayer_->Draw(worldTransformPlayer_, viewProjection_);

	//3Dオブジェクト描画後処理
	Model::PostDraw();
}
