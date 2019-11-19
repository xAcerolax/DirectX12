#pragma once
#include <wrl.h>
#include <vector>
#include <memory>

struct ID3D12DescriptorHeap;
struct ID3D12Resource;

class List;
class SwapChain;

class Render
{
	//コンストラクタ
	Render(std::weak_ptr<SwapChain>swap);
	//デストラクタ
	~Render();

	//画面のクリア
	void Clear(std::weak_ptr<List>list, ID3D12DescriptorHeap* depth = nullptr);

	//リソースの取得
	ID3D12Resource* Get(void) const;

private:
	//ヒープの生成
	void CreateHeap(void);

	//リソースの生成
	void CreateRsc(void);

	//スワップチェイン
	std::weak_ptr<SwapChain> swap;
	
	//ヒープ
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> heap;

	//リソース
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> rsc;
};

