#pragma once

enum class CONSTANT_BUFFER_TYPE : uint8
{
	TRANSFORM,
	MATERIAL,
	END,
};

enum
{
	CONSTANT_BUFFER_COUNT = static_cast<uint8>(CONSTANT_BUFFER_TYPE::END)
};

class ConstantBuffer
{

public :
	ConstantBuffer();
	~ConstantBuffer();

	void Init(CBV_REGISTER reg, uint32 size, uint32 count);

	void Clear();
	void PushData(void* buffer, uint32 size);

	D3D12_GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress(uint32 index);
	D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle(uint32 index);
private:
	void CreateBuffer();
	void CreateView();
private:
	ComPtr<ID3D12Resource>	_cbvBuffer;
	BYTE*					_mappedBuffer = nullptr;
	uint32					_elementSize = 0;//요소의 크기
	uint32					_elementCount = 0;//요소의 갯수

	ComPtr<ID3D12DescriptorHeap>		_cbvHeap;
	D3D12_CPU_DESCRIPTOR_HANDLE			_cpuHandleBegin = {};//시작핸들주소
	uint32								_handleIncrementSize = 0;//각핸들 사이의 크기

	uint32					_currentIndex = 0;
	//어디까지 사용했는지 추적 한프레임을 다 그리면 다시 0이되서 다음 프레임 그릴준비

	CBV_REGISTER			_reg = {};
};

