#pragma once

class Buffer
{
public:
	Buffer() {}
	virtual ~Buffer() {}

protected:
	GraphicsDevice* m_pGraphicsDevice = nullptr;
	ComPtr<ID3D12Resource> m_pBuffer = nullptr;
};