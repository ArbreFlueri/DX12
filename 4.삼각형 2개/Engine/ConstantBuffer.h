#pragma once
class ConstantBuffer
{

public :
	ConstantBuffer();
	~ConstantBuffer();

	void Init(uint32 size, uint32 count);

	void Clear();
	void PushData(int32 rootParamIndex, void* buffer, uint32 size);

	D3D12_GPU_VIRTUAL_ADDRESS GetGpuVirtualAddress(uint32 index);

private:
	void CreateBuffer();
private:
	ComPtr<ID3D12Resource>	_cbvBuffer;
	BYTE*					_mappedBuffer = nullptr;
	uint32					_elementSize = 0;//요소의 크기
	uint32					_elementCount = 0;//요소의 갯수

	uint32					_currentIndex = 0;
	//어디까지 사용했는지 추적 한프레임을 다 그리면 다시 0이되서 다음 프레임 그릴준비

};

