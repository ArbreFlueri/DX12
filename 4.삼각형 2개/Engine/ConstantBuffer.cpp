#include "pch.h"
#include "ConstantBuffer.h"
#include "Engine.h"

ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer()
{
	if (_cbvBuffer)
	{
		if (_cbvBuffer != nullptr)
			_cbvBuffer->Unmap(0, nullptr);

		_cbvBuffer = nullptr;
	}
}

void ConstantBuffer::Init(uint32 size, uint32 count)
{
	// 상수 버퍼는 256 바이트 배수로 만들어야 한다
	// 0 256 (298)-> 512 768
	//255를 더하는 이유 :오른쪽의 값을 가지려고 298은 256이 가깝지만 올림처리처럼 512로 가게하려구
	_elementSize = (size + 255) & ~255; 
	_elementCount = count;

	CreateBuffer();
}

void ConstantBuffer::CreateBuffer()
{
	uint32 bufferSize = _elementSize * _elementCount;
	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	DEVICE->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_cbvBuffer));

	_cbvBuffer->Map(0, nullptr, reinterpret_cast<void**>(&_mappedBuffer));
	// We do not need to unmap until we are done with the resource.  However, we must not write to
	// the resource while it is in use by the GPU (so we must use synchronization techniques).
	//fence 사용해 무식하게 잘 기다리고있음 싱크 걱정 ㄴ
}

void ConstantBuffer::Clear() //매 프레임 0 되야지 지옥가야지~
{
	_currentIndex = 0;
}

void ConstantBuffer::PushData(int32 rootParamIndex, void* buffer, uint32 size)
{
	assert(_currentIndex < _elementSize); //만족안하면 crash내는 디버깅 코드

	::memcpy(&_mappedBuffer[_currentIndex * _elementSize], buffer, size); 
	//해당 인덱스(_currentIndex) 위치에다가 요청해준 buffer를 복사 해주고있음

	D3D12_GPU_VIRTUAL_ADDRESS address = GetGpuVirtualAddress(_currentIndex);
	CMD_LIST->SetGraphicsRootConstantBufferView(rootParamIndex, address); //나중에 레지스터한테 요 주소를 참고해주세요
	_currentIndex++;
}

D3D12_GPU_VIRTUAL_ADDRESS ConstantBuffer::GetGpuVirtualAddress(uint32 index)	//버퍼의 어디에 있는지 알아내버리기
{
	D3D12_GPU_VIRTUAL_ADDRESS objCBAddress = _cbvBuffer->GetGPUVirtualAddress();
	objCBAddress += index * _elementSize;
	return objCBAddress;
}


