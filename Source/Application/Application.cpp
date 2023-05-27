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

	Mesh mesh;
	mesh.Create(&GraphicsDevice::Instance());

	RenderingSetting renderingSetting = {};
	renderingSetting.InputLayouts = { InputLayout::POSITION };
	renderingSetting.Formats = { DXGI_FORMAT_R8G8B8A8_UNORM };
	renderingSetting.IsDepth = false;
	renderingSetting.IsDepthMask = false;

	Shader shader;
	shader.Create(&GraphicsDevice::Instance(), L"SimpleShader", renderingSetting, {});

	while (true)
	{
		if (!m_window.ProcessMessage())
		{
			break;
		}

		GraphicsDevice::Instance().Prepare();

		shader.Begin(width, height);

		shader.DrawMesh(mesh);

		GraphicsDevice::Instance().ScreenFlip();
	}
}