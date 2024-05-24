#pragma once
#include <DirectXCommon.h>
#include <Vector3.h>

enum class MapChipType
{
	kBlank,//空白
	kBlock,//ブロック
};

struct MapChipData
{
	std::vector<std::vector<MapChipType>> data;
};

/// <summary>
/// マップチップフィールド
/// </summary>
class MapChipField
{
	//１ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;
	//ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	MapChipData mapChipData_;

	public:

	//リセット
	void ResetMapChipData();
	//読み込み
	void LoadMapChipCsv(const std::string& filePath);
	//マップチップ種別の取得
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);
	//マップチップ座標の取得
	Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	//ブロックの縦方向の個数を取得
	uint32_t GetNumBlockVirtical() { return kNumBlockVirtical; }
	// ブロックの横方向の個数を取得
	uint32_t GetNumBlockHorizontal() { return kNumBlockHorizontal; }
};