
cbuffer TEST_B0 : register(b0)  //constant Buffer를 사용하는데 b0에있는 레지스터를 
{                               //사용할꺼고 얘를 offset0이라 부를꺼야
    float4 offset0;             // offset가 b0 register를 사용할거라는 뜻
};

cbuffer TEST_B1 : register(b1)  //constant Buffer를 사용하는데 b1에있는 레지스터를 
{                               //사용할꺼고 얘를 offset1이라 부를꺼야
    float4 offset1;
};

Texture2D tex_0 : register(t0);

SamplerState sam_0 : register(s0); //정책을 골라주는? 

struct VS_IN
{
    float3 pos : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

struct VS_OUT
{
    float4 pos : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT)0;

    output.pos = float4(input.pos, 1.f);
    output.color = input.color;
    output.uv = input.uv;
    

    return output;
}

float4 PS_Main(VS_OUT input) : SV_Target
{
    float4 color = tex_0.Sample(sam_0, input.uv);
    //이거뭐야 ㅅㅂ
    return color;
}