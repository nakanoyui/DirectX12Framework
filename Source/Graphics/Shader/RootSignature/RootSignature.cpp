#include "RootSignature.h"

void RootSignature::Create(GraphicsDevice* pGraphicsDevice, const std::vector<RangeType>& rangeTypes)
{
	m_pDevice = pGraphicsDevice;

	D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc = {};
	int rangeCount = (int)rangeTypes.size();

	// レンジ数分だけルートパラメータ、レンジを生成
	std::vector<D3D12_ROOT_PARAMETER> rootParams(rangeCount);
	std::vector<D3D12_DESCRIPTOR_RANGE> ranges(rangeCount);

	// SRVの数だけSamplerDescを生成
	int samplerCount = 0;

	for (int i = 0; i < (int)rangeTypes.size(); ++i)
	{
		if (rangeTypes[i] == RangeType::SRV)
		{
			++samplerCount;
		}
	}

	// 指定された順に設定
	samplerCount = 0;
	bool bSampler = false;
	int cbvCount = 0;
	int uavCount = 0;

	for (int i = 0; i < rangeCount; ++i)
	{
		switch (rangeTypes[i])
		{
		case RangeType::CBV:
			CreateRange(ranges[i], RangeType::CBV, cbvCount);
			rootParams[i].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParams[i].DescriptorTable.pDescriptorRanges = &ranges[i];
			rootParams[i].DescriptorTable.NumDescriptorRanges = 1;
			rootParams[i].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			++cbvCount;
			break;
		case RangeType::SRV:
			CreateRange(ranges[i], RangeType::SRV, samplerCount);
			rootParams[i].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParams[i].DescriptorTable.pDescriptorRanges = &ranges[i];
			rootParams[i].DescriptorTable.NumDescriptorRanges = 1;
			rootParams[i].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			++samplerCount;
			bSampler = true;
			break;
		case RangeType::UAV:
			CreateRange(ranges[i], RangeType::UAV, uavCount);
			rootParams[i].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
			rootParams[i].DescriptorTable.pDescriptorRanges = &ranges[i];
			rootParams[i].DescriptorTable.NumDescriptorRanges = 1;
			rootParams[i].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
			++uavCount;
			break;
		default:
			break;
		}
	}

	std::array<D3D12_STATIC_SAMPLER_DESC, 4> pStaticSamplerDescs = {};

	if (bSampler)
	{
		CreateStaticSampler(pStaticSamplerDescs[0], TextureAddressMode::Wrap, D3D12Filter::Point, 0);
		CreateStaticSampler(pStaticSamplerDescs[1], TextureAddressMode::Clamp, D3D12Filter::Point, 1);
		CreateStaticSampler(pStaticSamplerDescs[2], TextureAddressMode::Wrap, D3D12Filter::Linear, 2);
		CreateStaticSampler(pStaticSamplerDescs[3], TextureAddressMode::Clamp, D3D12Filter::Linear, 3);
	}

	rootSignatureDesc.pStaticSamplers = bSampler ? pStaticSamplerDescs.data() : nullptr;
	rootSignatureDesc.NumStaticSamplers = bSampler ? 4 : 0;
	rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	rootSignatureDesc.pParameters = rootParams.data();
	rootSignatureDesc.NumParameters = (int)rangeTypes.size();

	ID3DBlob* pErrorBlob = nullptr;
	auto hr = D3D12SerializeRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &m_pRootBlob, &pErrorBlob);

	if (FAILED(hr))
	{
		assert(0 && "ルートシグネチャ初期化失敗");
	}

	hr = m_pDevice->GetDevice()->CreateRootSignature(0, m_pRootBlob->GetBufferPointer(), m_pRootBlob->GetBufferSize(), IID_PPV_ARGS(&m_pRootSignature));

	if (FAILED(hr))
	{
		assert(0 && "ルートシグネチャ作成失敗");
	}
}

void RootSignature::CreateRange(D3D12_DESCRIPTOR_RANGE& range, RangeType type, int count)
{
	switch (type)
	{
	case RangeType::CBV:
		range = {};
		range.NumDescriptors = 1;
		range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		range.BaseShaderRegister = count;
		range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
		break;
	case RangeType::SRV:
		range = {};
		range.NumDescriptors = 1;
		range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
		range.BaseShaderRegister = count;
		range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
		break;
	case RangeType::UAV:
		range = {};
		range.NumDescriptors = 1;
		range.RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
		range.BaseShaderRegister = count;
		range.OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
		break;
	default:
		break;
	}
}

void RootSignature::CreateStaticSampler(D3D12_STATIC_SAMPLER_DESC& samplerDesc, TextureAddressMode mode, 
	D3D12Filter filter, int count)
{
	D3D12_TEXTURE_ADDRESS_MODE addressMode = mode == TextureAddressMode::Wrap ? 
		D3D12_TEXTURE_ADDRESS_MODE_WRAP : D3D12_TEXTURE_ADDRESS_MODE_CLAMP;

	D3D12_FILTER samplingFilter = filter == D3D12Filter::Point ? 
		D3D12_FILTER_MIN_MAG_MIP_POINT : D3D12_FILTER_MIN_MAG_MIP_LINEAR;

	samplerDesc = {};
	samplerDesc.AddressU = addressMode;
	samplerDesc.AddressV = addressMode;
	samplerDesc.AddressW = addressMode;
	samplerDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
	samplerDesc.Filter = samplingFilter;
	samplerDesc.MaxLOD = D3D12_FLOAT32_MAX;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.ComparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
	samplerDesc.ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ShaderRegister = count;
}