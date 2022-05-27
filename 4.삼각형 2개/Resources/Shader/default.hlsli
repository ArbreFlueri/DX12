
cbuffer TEST_B0 : register(b0)  //constant Buffer�� ����ϴµ� b0���ִ� �������͸� 
{                               //����Ҳ��� �긦 offset0�̶� �θ�����
    float4 offset0;             // offset�� b0 register�� ����ҰŶ�� ��
};

cbuffer TEST_B1 : register(b1)  //constant Buffer�� ����ϴµ� b1���ִ� �������͸� 
{                               //����Ҳ��� �긦 offset1�̶� �θ�����
    float4 offset1;
};

struct VS_IN
{
    float3 pos : POSITION;
    float4 color : COLOR;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float4 color : COLOR;
};

VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

    output.pos = float4(input.pos, 1.f);
    output.pos += offset0;
    output.color = input.color;
    output.color += offset1;

    return output;
}

float4 PS_Main(VS_OUT input) : SV_Target
{
    return input.color;
}