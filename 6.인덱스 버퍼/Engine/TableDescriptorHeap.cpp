#include "pch.h"
#include "TableDescriptorHeap.h"
#include"Engine.h"

void TableDescriptorHeap::Init(uint32 count)
{
	_groupCount = count;

	D3D12_DESCRIPTOR_HEAP_DESC desc = {};
	desc.NumDescriptors = count * REGISTER_COUNT;
	desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE; //visible로 만들어야만 register로 올려보낼수가 있음
	desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;

	DEVICE->CreateDescriptorHeap(&desc, IID_PPV_ARGS(&_descHeap));//descHeap에다가 다넣어줌

	_handleSize = DEVICE->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);//핸들사이즈저장
	_groupSize = _handleSize * REGISTER_COUNT;//그룹사이즈 얻음 둘중 하나만 있어도 충분
}

void TableDescriptorHeap::Clear()
{
	_currentGroupIndex = 0;
}
//프레임마다 밀어주기위해서 있는 함수

void TableDescriptorHeap::SetCBV(D3D12_CPU_DESCRIPTOR_HANDLE srcHandle, CBV_REGISTER reg)
{
	D3D12_CPU_DESCRIPTOR_HANDLE destHandle = GetCPUHandle(reg);

	uint32 destRange = 1;
	uint32 srcRange = 1;
	DEVICE->CopyDescriptors(1, &destHandle, &destRange, 1, &srcHandle, &srcRange, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}//cpu핸들 2개를 받아서 원래 위치 목적지 위치를 입력한거임


void TableDescriptorHeap::CommitTable() //현재 내 그룹인덱스에 해당되는 칸을 register에 올려줌
{
	D3D12_GPU_DESCRIPTOR_HANDLE handle = _descHeap->GetGPUDescriptorHandleForHeapStart();
	handle.ptr += _currentGroupIndex * _groupSize;
	CMD_LIST->SetGraphicsRootDescriptorTable(0, handle);

	_currentGroupIndex++;
}

D3D12_CPU_DESCRIPTOR_HANDLE TableDescriptorHeap::GetCPUHandle(CBV_REGISTER reg)
{
	return GetCPUHandle(static_cast<uint32>(reg));
}

D3D12_CPU_DESCRIPTOR_HANDLE TableDescriptorHeap::GetCPUHandle(uint32 reg)
{
	D3D12_CPU_DESCRIPTOR_HANDLE handle = _descHeap->GetCPUDescriptorHandleForHeapStart();
	handle.ptr += _currentGroupIndex * _groupSize;//그룹사이즈만큼이동
	handle.ptr += reg * _handleSize;//내가 원하는 reg만큼 이동
	return handle; //몇동몇호같은느낌
}