#include "pch.h"
#include "Mesh.h"
#include "Engine.h"

void Mesh::Init(vector<Vertex>& vec)
{
	_vertexCount = static_cast<uint32>(vec.size());
	uint32 bufferSize = _vertexCount * sizeof(Vertex);

	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD); //실시간으로 변경 UPLOAD 나무처럼 가만히 NOMAL
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);
	//뭔가 지금 바로 이뤄지고있어
	DEVICE->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&_vertexBuffer));

	// Copy the triangle data to the vertex buffer.
	void* vertexDataBuffer = nullptr;
	CD3DX12_RANGE readRange(0, 0); // We do not intend to read from this resource on the CPU.
	_vertexBuffer->Map(0, &readRange, &vertexDataBuffer); //맵을 통해 때려넣기
	::memcpy(vertexDataBuffer, &vec[0], bufferSize);	//memcpy로 바로바로 복사
	_vertexBuffer->Unmap(0, nullptr);	//연동끊기	//디바이스를 통해 작업이 이뤄지므로 지금 당장 이뤄진다고 생각하면됨

	// Initialize the vertex buffer view.
	_vertexBufferView.BufferLocation = _vertexBuffer->GetGPUVirtualAddress();
	_vertexBufferView.StrideInBytes = sizeof(Vertex); // 정점 1개 크기
	_vertexBufferView.SizeInBytes = bufferSize; // 버퍼의 크기	
}

void Mesh::Render()
{
	CMD_LIST->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	CMD_LIST->IASetVertexBuffers(0, 1, &_vertexBufferView); // Slot: (0~15)

	//TODO
	// 1) Buffer에다가 데이터 세팅
	// 2) Buffer의 주소를 register에 전송
	GEngine->GetCB()->PushData(0, &_transform, sizeof(_transform));
	GEngine->GetCB()->PushData(1, &_transform, sizeof(_transform));
	//CMD_LIST->SetGraphicsRootConstantBufferView(0,?);

	CMD_LIST->DrawInstanced(_vertexCount, 1, 0, 0);
}