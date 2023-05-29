#include "Mesh.h"

void Mesh::Create(GraphicsDevice* pGraphicsDevice)
{
	m_pDevice = pGraphicsDevice;

	// 頂点の座標
	m_vertices.emplace_back(Math::Vector3(-0.75f, -0.75f, 0.0f), Math::Vector2(0.0f, 1.0f));
	m_vertices.emplace_back(Math::Vector3(-0.75f, 0.75f, 0.0f), Math::Vector2(0.0f, 0.0f));
	m_vertices.emplace_back(Math::Vector3(0.75f, -0.75f, 0.0f), Math::Vector2(1.0f, 1.0f));
	m_vertices.emplace_back(Math::Vector3(0.75f, 0.75f, 0.0f), Math::Vector2(1.0f, 0.0f));

	D3D12_HEAP_PROPERTIES heapProp = {};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
	heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

	D3D12_RESOURCE_DESC resDesc = {};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;

	//? 更新
	resDesc.Width = sizeof(Vertex) * m_vertices.size();
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.Format = DXGI_FORMAT_UNKNOWN;
	resDesc.SampleDesc.Count = 1;
	resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// 頂点バッファ作成
	auto hr = m_pDevice->GetDevice()->CreateCommittedResource(&heapProp,
		D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_pVBuffer));

	if (FAILED(hr))assert(0 && "頂点バッファー作成失敗");

	// 頂点バッファのデータをビューに書き込む
	m_vbView.BufferLocation = m_pVBuffer->GetGPUVirtualAddress();
	m_vbView.SizeInBytes = (UINT)resDesc.Width;
	m_vbView.StrideInBytes = sizeof(Vertex);

	// インデックスデータ
	m_indices.emplace_back(0);
	m_indices.emplace_back(1);
	m_indices.emplace_back(2);
	m_indices.emplace_back(2);
	m_indices.emplace_back(1);
	m_indices.emplace_back(3);

	resDesc.Width = sizeof(UINT) * m_indices.size();

	// インデックスバッファ作成
	hr = m_pDevice->GetDevice()->CreateCommittedResource(&heapProp,
		D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_pIBuffer));

	if (FAILED(hr))assert(0 && "インデックスバッファー作成失敗");

	// インデックスバッファのデータをビューに書き込む
	m_ibView.BufferLocation = m_pIBuffer->GetGPUVirtualAddress();
	m_ibView.SizeInBytes = (UINT)resDesc.Width;
	m_ibView.Format = DXGI_FORMAT_R32_UINT;

	// 頂点バッファに情報を書き込む
	Vertex* vbMap = nullptr;
	{
		m_pVBuffer->Map(0, nullptr, (void**)&vbMap);
		std::copy(std::begin(m_vertices), std::end(m_vertices), vbMap);
		m_pVBuffer->Unmap(0, nullptr);
	}

	// インデックスバッファに情報を書き込む
	UINT* ibMap = nullptr;
	{
		m_pIBuffer->Map(0, nullptr, (void**)&ibMap);
		std::copy(std::begin(m_indices), std::end(m_indices), ibMap);
		m_pIBuffer->Unmap(0, nullptr);
	}
}

void Mesh::DrawInstanced()const
{
	m_pDevice->GetCmdList()->IASetVertexBuffers(0, 1, &m_vbView);
	m_pDevice->GetCmdList()->IASetIndexBuffer(&m_ibView);

	m_pDevice->GetCmdList()->DrawIndexedInstanced(6, 1, 0, 0, 0);
}