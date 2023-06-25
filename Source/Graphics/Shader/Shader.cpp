#include "Shader.h"

void Shader::Create(GraphicsDevice* pGraphicsDevice, const std::wstring& filePath,
	const RenderingSetting& renderingSetting, const std::vector<RangeType>& rangeTypes)
{
	m_pDevice = pGraphicsDevice;

	LoadShaderFile(filePath);

	m_upRootSignature = std::make_unique<RootSignature>();
	m_upRootSignature->Create(pGraphicsDevice, rangeTypes, m_cbvCount);

	m_upPipeline = std::make_unique<Pipeline>();
	m_upPipeline->SetRenderSettings(pGraphicsDevice, m_upRootSignature.get(), renderingSetting.InputLayouts,
		renderingSetting.CullMode, renderingSetting.BlendMode, renderingSetting.PrimitiveTopologyType);
	m_upPipeline->Create({ m_pVSBlob ,m_pHSBlob ,m_pDSBlob ,m_pGSBlob ,m_pPSBlob }, renderingSetting.Formats,
		renderingSetting.IsDepth, renderingSetting.IsDepthMask, renderingSetting.RTVCount, renderingSetting.IsWireFrame);
}

void Shader::Begin(int w, int h)
{
	m_pDevice->GetCmdList()->SetPipelineState(m_upPipeline->GetPipeline());

	// ルートシグネチャのセット
	m_pDevice->GetCmdList()->SetGraphicsRootSignature(m_upRootSignature->GetRootSignature());

	D3D12_PRIMITIVE_TOPOLOGY_TYPE topologyType =
		static_cast<D3D12_PRIMITIVE_TOPOLOGY_TYPE>(m_upPipeline->GetTopologyType());

	switch (topologyType)
	{
	case D3D12_PRIMITIVE_TOPOLOGY_TYPE_POINT:
		m_pDevice->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
		break;
	case D3D12_PRIMITIVE_TOPOLOGY_TYPE_LINE:
		m_pDevice->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		break;
	case D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE:
		m_pDevice->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		break;
	case D3D12_PRIMITIVE_TOPOLOGY_TYPE_PATCH:
		m_pDevice->GetCmdList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST);
		break;
	}

	D3D12_VIEWPORT viewport = {};
	D3D12_RECT rect = {};

	viewport.Width = static_cast<float>(w);
	viewport.Height = static_cast<float>(h);

	rect.right = w;
	rect.bottom = h;

	GraphicsDevice::Instance().GetCmdList()->RSSetViewports(1, &viewport);
	GraphicsDevice::Instance().GetCmdList()->RSSetScissorRects(1, &rect);
}

void Shader::DrawMesh(const Mesh& mesh)
{
	SetMaterial(mesh.GetMaterial());

	mesh.DrawInstanced(mesh.GetInstanceCount());
}

void Shader::DrawModel(const ModelData& modelData)
{
	// ノードを全て描画
	for (auto& node : modelData.GetNodes())
	{
		DrawMesh(*node.spMesh);
	}
}

void Shader::LoadShaderFile(const std::wstring& filePath)
{
	ID3DInclude* include = D3D_COMPILE_STANDARD_FILE_INCLUDE;
	UINT flag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
	ID3DBlob* pErrorBlob = nullptr;

	std::wstring format = L".hlsl";
	std::wstring currentPath = L"Asset/Shader/";

	// 頂点シェーダーのコンパイル
	{
		std::wstring fullFilepath = currentPath + filePath + L"_VS" + format;
		auto hr = D3DCompileFromFile(fullFilepath.c_str(), nullptr, include, "main",
			"vs_5_0", flag, 0, &m_pVSBlob, &pErrorBlob);

		if (FAILED(hr))
		{
			assert(0 && "頂点シェーダーのコンパイルに失敗しました");
			return;
		}
	}

	// ハルシェーダーのコンパイル
	{
		std::wstring fullFilepath = currentPath + filePath + L"_HS" + format;
		auto hr = D3DCompileFromFile(fullFilepath.c_str(), nullptr, include, "main",
			"hs_5_0", flag, 0, &m_pHSBlob, &pErrorBlob);

		// ハルシェーダーはなくてもいい
	}

	// ドメインシェーダーのコンパイル
	{
		std::wstring fullFilepath = currentPath + filePath + L"_DS" + format;
		auto hr = D3DCompileFromFile(fullFilepath.c_str(), nullptr, include, "main",
			"ds_5_0", flag, 0, &m_pDSBlob, &pErrorBlob);

		// ドメインシェーダーはなくてもいい
	}

	// ジオメトリシェーダーのコンパイル
	{
		std::wstring fullFilepath = currentPath + filePath + L"_GS" + format;
		auto hr = D3DCompileFromFile(fullFilepath.c_str(), nullptr, include, "main",
			"gs_5_0", flag, 0, &m_pGSBlob, &pErrorBlob);

		// ジオメトリシェーダーはなくてもいい
	}

	// ピクセルシェーダーのコンパイル
	{
		std::wstring fullFilepath = currentPath + filePath + L"_PS" + format;
		auto hr = D3DCompileFromFile(fullFilepath.c_str(), nullptr, include, "main",
			"ps_5_0", flag, 0, &m_pPSBlob, &pErrorBlob);

		if (FAILED(hr))
		{
			assert(0 && "ピクセルシェーダーのコンパイルに失敗しました");
			return;
		}
	}
}

void Shader::SetMaterial(const Material& material)
{
	material.spBaseColorTex->Set(m_cbvCount);
	//material.spNormalTex->Set(m_cbvCount + 1);
	//material.spMetallicRoughnessTex->Set(m_cbvCount + 2);
	//material.spEmissiveTex->Set(m_cbvCount + 3);
}