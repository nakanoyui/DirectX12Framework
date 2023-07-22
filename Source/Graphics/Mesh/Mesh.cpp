#include "Mesh.h"

void Mesh::Create(GraphicsDevice* pGraphicsDevice, const std::vector<MeshVertex>& vertices,
	const std::vector<MeshFace>& faces, const Material& material)
{
	m_pDevice = pGraphicsDevice;
	m_material = material;

	if (static_cast<int>(vertices.size()) == 0)
	{
		assert(0 && "頂点が1つもありません");
		return;
	}

	m_instanceCount = static_cast<UINT>(faces.size() * 3);

	D3D12_HEAP_PROPERTIES heapProp = {};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;
	heapProp.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	heapProp.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

	D3D12_RESOURCE_DESC resDesc = {};
	resDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resDesc.Width = sizeof(MeshVertex) * vertices.size();
	resDesc.Height = 1;
	resDesc.DepthOrArraySize = 1;
	resDesc.MipLevels = 1;
	resDesc.Format = DXGI_FORMAT_UNKNOWN;
	resDesc.SampleDesc.Count = 1;
	resDesc.Flags = D3D12_RESOURCE_FLAG_NONE;
	resDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	auto hr = m_pDevice->GetDevice()->CreateCommittedResource(&heapProp,
		D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_pVBuffer));

	if (FAILED(hr))
	{
		assert(0 && "頂点バッファー作成失敗");
		return;
	}

	m_vbView.BufferLocation = m_pVBuffer->GetGPUVirtualAddress();
	m_vbView.SizeInBytes = (UINT)resDesc.Width;
	m_vbView.StrideInBytes = sizeof(MeshVertex);

	resDesc.Width = sizeof(MeshFace) * faces.size();

	// インデックスバッファ作成
	hr = m_pDevice->GetDevice()->CreateCommittedResource(&heapProp,
		D3D12_HEAP_FLAG_NONE, &resDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_pIBuffer));

	if (FAILED(hr))
	{
		assert(0 && "インデックスバッファー作成失敗");
		return;
	}

	// インデックスバッファのデータをビューに書き込む
	m_ibView.BufferLocation = m_pIBuffer->GetGPUVirtualAddress();
	m_ibView.SizeInBytes = (UINT)resDesc.Width;
	m_ibView.Format = DXGI_FORMAT_R32_UINT;

	// 頂点バッファに情報を書き込む
	MeshVertex* vbMap = nullptr;
	{
		m_pVBuffer->Map(0, nullptr, (void**)&vbMap);
		std::copy(std::begin(vertices), std::end(vertices), vbMap);
		m_pVBuffer->Unmap(0, nullptr);
	}

	// インデックスバッファに情報を書き込む
	MeshFace* ibMap = nullptr;
	{
		m_pIBuffer->Map(0, nullptr, (void**)&ibMap);
		std::copy(std::begin(faces), std::end(faces), ibMap);
		m_pIBuffer->Unmap(0, nullptr);
	}
}

void Mesh::DrawInstanced(UINT vertexCount)const
{
	m_pDevice->GetCmdList()->IASetVertexBuffers(0, 1, &m_vbView);
	m_pDevice->GetCmdList()->IASetIndexBuffer(&m_ibView);

	m_pDevice->GetCmdList()->DrawIndexedInstanced(vertexCount, 1, 0, 0, 0);
}