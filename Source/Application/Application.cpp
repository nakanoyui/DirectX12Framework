#include "Application.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// ���������[�N��m�点��

	CoInitializeEx(nullptr, COINIT_MULTITHREADED);	// COM������

	Application::Instance().Excute();

	CoUninitialize();	// COM���

	return 0;
}

void Application::Excute()
{
	SetDirectoryAndLoadDll();

	static const int width = 1280;
	static const int height = 720;

	if (!m_window.Create(width, height, L"FrameworkDX12", L"Window"))
	{
		assert(0 && "�E�B���h�E�쐬���s�B");
		return;
	}

	if (!GraphicsDevice::Instance().Init(m_window.GetWndHandle(), width, height))
	{
		assert(0 && "�O���t�B�b�N�X�f�o�C�X���������s�B");
		return;
	}

	ModelData modelData;
	modelData.Load("Asset/Model/Cube/Cube.gltf");

	Math::Matrix mWorld;

	RenderingSetting renderingSetting = {};
	renderingSetting.InputLayouts = 
		{ InputLayout::POSITION,InputLayout::TEXCOORD,InputLayout::COLOR,InputLayout::NORMAL,InputLayout::TANGENT };
	renderingSetting.Formats = { DXGI_FORMAT_R8G8B8A8_UNORM };
	renderingSetting.IsDepth = false;
	renderingSetting.IsDepthMask = false;

	Shader shader;
	shader.Create(&GraphicsDevice::Instance(), L"SimpleShader", 
		renderingSetting, { RangeType::CBV,RangeType::CBV, RangeType::SRV,RangeType::SRV,RangeType::SRV,RangeType::SRV });

	Math::Matrix mView = Math::Matrix::CreateTranslation(0, 0, 3);

	Math::Matrix mProj =
		DirectX::XMMatrixPerspectiveFovLH(DirectX::XMConvertToRadians(60.0f), 1280.0f / 720.0f, 0.01f, 1000.0f);

	CBufferData::Camera cbCamera;
	cbCamera.mView = mView;
	cbCamera.mProj = mProj;

	while (true)
	{
		if (!m_window.ProcessMessage())
		{
			break;
		}

		GraphicsDevice::Instance().Prepare();

		GraphicsDevice::Instance().GetCBVSRVUAVHeap()->SetHeap();

		GraphicsDevice::Instance().GetCBufferAllocater()->ResetCurrentUseNumber();

		shader.Begin(width, height);

		GraphicsDevice::Instance().GetCBufferAllocater()->BindAndAttachData(0, cbCamera);

		mWorld *= Math::Matrix::CreateRotationY(0.01f);

		GraphicsDevice::Instance().GetCBufferAllocater()->BindAndAttachData(1, mWorld);

		shader.DrawModel(modelData);

		GraphicsDevice::Instance().ScreenFlip();
	}
}

void Application::SetDirectoryAndLoadDll()
{
#ifdef _DEBUG
	SetDllDirectoryA("Library/assimp/build/lib/Debug");
	LoadLibraryExA("assimp-vc143-mtd.dll", NULL, NULL);
#else
	SetDllDirectoryA("Library/assimp/build/lib/Release");
	LoadLibraryExA("assimp-vc143-mt.dll", NULL, NULL);
#endif
}