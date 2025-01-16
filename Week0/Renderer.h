// D3D 사용에 필요한 라이브러리들을 링크합니다.
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

// D3D 사용에 필요한 헤더파일들을 포함합니다.
#include <d3d11.h>
#include <d3dcompiler.h>

namespace RendererData
{
    // 1. Define the triangle vertices
    struct alignas(16) FVertexSimple
    {
        float x, y, z;    // Position
        float r, g, b, a; // Color
    };
}

class URenderer
{
public:
    // Direct3D 11 장치(Device)와 장치 컨텍스트(Device Context) 및 스왑 체인(Swap Chain)을 관리하기 위한 포인터들
    ID3D11Device* Device = nullptr; // GPU와 통신하기 위한 Direct3D 장치
    ID3D11DeviceContext* DeviceContext = nullptr; // GPU 명령 실행을 담당하는 컨텍스트
    IDXGISwapChain* SwapChain = nullptr; // 프레임 버퍼를 교체하는 데 사용되는 스왑 체인

    // 렌더링에 필요한 리소스 및 상태를 관리하기 위한 변수들
    ID3D11Texture2D* FrameBuffer = nullptr; // 화면 출력용 텍스처
    ID3D11RenderTargetView* FrameBufferRTV = nullptr; // 텍스처를 렌더 타겟으로 사용하는 뷰
    ID3D11RasterizerState* RasterizerState = nullptr; // 래스터라이저 상태(컬링, 채우기 모드 등 정의)
    ID3D11Buffer* ConstantBuffer = nullptr; // 쉐이더에 데이터를 전달하기 위한 상수 버퍼

    FLOAT ClearColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f }; // 화면을 초기화(clear)할 때 사용할 색상 (RGBA)
    D3D11_VIEWPORT ViewportInfo; // 렌더링 영역을 정의하는 뷰포트 정보

public:
    // 렌더러 초기화 함수
    void Create(HWND hWindow);

    // Direct3D 장치 및 스왑 체인을 생성하는 래핑 함수
    void CreateDeviceAndSwapChain(HWND hWindow);

    // Direct3D 장치 및 스왑 체인을 해제하는 함수
    void ReleaseDeviceAndSwapChain();

    // 프레임 버퍼를 생성하는 함수
    void CreateFrameBuffer();

    // 프레임 버퍼를 해제하는 함수
    void ReleaseFrameBuffer();

    // 래스터라이저 상태를 생성하는 함수
    void CreateRasterizerState();

    // 래스터라이저 상태를 해제하는 함수
    void ReleaseRasterizerState();

    // 렌더러에 사용된 모든 리소스를 해제하는 함수
    void Release();

    // 스왑 체인의 백 버퍼와 프론트 버퍼를 교체하여 화면에 출력
    void SwapBuffer();

public:
    // SimpleVertexShader: GPU에서 실행되는 정점(Vertex) 처리 쉐이더 객체를 나타냅니다.
    // 이 쉐이더는 주로 정점 변환(모델 공간 → 화면 공간), 조명 계산 등을 담당합니다.
    ID3D11VertexShader* SimpleVertexShader;

    // SimplePixelShader: GPU에서 실행되는 픽셀(Pixel) 처리 쉐이더 객체를 나타냅니다.
    // 이 쉐이더는 화면에 그려질 픽셀의 색상 및 최종 렌더링 출력을 결정합니다.
    ID3D11PixelShader* SimplePixelShader;

    // SimpleInputLayout: GPU가 정점 데이터를 올바르게 해석하기 위해 사용하는 입력 레이아웃(Input Layout)입니다.
    // 정점 데이터의 구성(예: 위치, 색상, 텍스처 좌표 등)을 정의하며, 정점 쉐이더와 연결됩니다.
    ID3D11InputLayout* SimpleInputLayout;

    // Stride: 정점 데이터에서 한 정점(Vertex)의 바이트 단위를 나타냅니다.
    // 예를 들어, 정점이 (x, y, z, r, g, b, a)의 데이터를 가진다면, Stride는 sizeof(float) * 7 = 28 바이트가 됩니다.
    unsigned int Stride;

	// Shader 생성 함수
    void CreateShader();

	// Shader 해제 함수
    void ReleaseShader();

public:
    // D3D11 렌더링에 필요한 준비 작업을 위한 Prepare 함수
	void Prepare();

    //Simple Shader 사용을 위한 PrepareShader 함수
    void PrepareShader();

    //실질적인 Rendering 요청을 할 RenderPrimitive 함수
    void RenderPrimitive(ID3D11Buffer* pBuffer, UINT numVertices);
};


