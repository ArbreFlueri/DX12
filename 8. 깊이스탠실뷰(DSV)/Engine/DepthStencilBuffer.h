#pragma once
class DepthStencilBuffer
{
public:
	void Init(const WindowInfo& window, DXGI_FORMAT dsvFormat = DXGI_FORMAT_D32_FLOAT); 
	//Depth 용도로만 32bit의 float을 활용할꺼에용 오로지 깊이만 사용 스텐실 x

	D3D12_CPU_DESCRIPTOR_HANDLE	GetDSVCpuHandle() { return _dsvHandle; }
	DXGI_FORMAT GetDSVFormat() { return _dsvFormat; }

private:
	// Depth Stencil View
	ComPtr<ID3D12Resource>				_dsvBuffer;
	ComPtr<ID3D12DescriptorHeap>		_dsvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE			_dsvHandle = {};
	DXGI_FORMAT							_dsvFormat = {};
};

