#include "pch.h"
#include "RootSignature.h"

void RootSignature::Init(ComPtr<ID3D12Device> device)
{
	CD3DX12_ROOT_PARAMETER param[2];	//파라미터 2개 만든다음.
	param[0].InitAsConstantBufferView(0); // 0번 -> b0 -> CBV 
	param[1].InitAsConstantBufferView(1); // 1번 -> b1 -> CBV 
	//인자중 visibility all은 모든 파이프라인에 꽂아준다는 뜻


	D3D12_ROOT_SIGNATURE_DESC sigDesc = CD3DX12_ROOT_SIGNATURE_DESC(2,param);	//파라미터 param[2] 넣어줌
	sigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT; // 입력 조립기 단계

	ComPtr<ID3DBlob> blobSignature;
	ComPtr<ID3DBlob> blobError;
	::D3D12SerializeRootSignature(&sigDesc, D3D_ROOT_SIGNATURE_VERSION_1, &blobSignature, &blobError);
	device->CreateRootSignature(0, blobSignature->GetBufferPointer(), blobSignature->GetBufferSize(), IID_PPV_ARGS(&_signature));
}