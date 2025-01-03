//Default Shader

//VS 출력 구조체
struct VSOutput
{
    float4 pos : SV_POSITION;
    float4 col : COLOR0;
};

//셰이더 상수 구조체
struct CONSTS
{
    float trans;
    float scale;
    float rot;
};

ConstantBuffer<CONSTS> g_Consts : register(b0);


//2. color blanding
struct COLANI
{
    float4 color;
    
    float per;
    uint frm;
    float use;
};

ConstantBuffer<COLANI> g_ColAni : register(b1);

//3.flags
struct Flags
{
    bool blandflag;
};

ConstantBuffer<Flags> g_Flags : register(b2);

//셰이더 상수
static float4 g_RGB[] =
{
    { 1, 0, 0, 1 },
    { 0, 1, 0, 1 },
    { 0, 0, 1, 1 },
    { 1, 0, 0, 1 }
};

//색상 선형보간 함수
float4 RGBGen(float4 col, float a, uint frm);

//정점 셰이더
VSOutput VSMain(
    float4 pos : POSITION, 
    float4 col : COLOR0
)
{
        
    //scale
    pos.x *= g_Consts.scale;
    pos.y *= g_Consts.scale;
    
    //rotation
    #define r g_Consts.rot
    float4 v = pos;
    pos.x = v.x * cos(r) - v.y * sin(r);
    pos.y = v.x * sin(r) + v.y * cos(r);
    //translation
    pos.x += g_Consts.trans;
    
    
    
    float4 defaultcol = col;
    
    if (g_ColAni.use > 0)
    {
        
        col = g_ColAni.color;
    }
    
    if (g_Flags.blandflag)
    {
        col = col + defaultcol;
        col = RGBGen(col, g_ColAni.per, g_ColAni.frm);
    }
        
    
    VSOutput
    output = (VSOutput) 0;
    output.pos = pos;
    output.col = col;
    
    return output;
}

//색상 선형보간 함수 정의
float4 RGBGen(float4 col, float a, uint frm)
{
    float4 c0 = g_RGB[frm];
    float4 c1 = g_RGB[frm + 1];
    float4 c = lerp(c0, c1, a);
    
    return col + c;
}

//픽셀 셰이더
float4 PSMain(
    float4 pos : SV_POSITION,
    float4 col : COLOR0
) : SV_TARGET
{
    float4 color = col;
    
    return color;
}