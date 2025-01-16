// D3D ��뿡 �ʿ��� ���̺귯������ ��ũ�մϴ�.
#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

// D3D ��뿡 �ʿ��� ������ϵ��� �����մϴ�.
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
    // Direct3D 11 ��ġ(Device)�� ��ġ ���ؽ�Ʈ(Device Context) �� ���� ü��(Swap Chain)�� �����ϱ� ���� �����͵�
    ID3D11Device* Device = nullptr; // GPU�� ����ϱ� ���� Direct3D ��ġ
    ID3D11DeviceContext* DeviceContext = nullptr; // GPU ��� ������ ����ϴ� ���ؽ�Ʈ
    IDXGISwapChain* SwapChain = nullptr; // ������ ���۸� ��ü�ϴ� �� ���Ǵ� ���� ü��

    // �������� �ʿ��� ���ҽ� �� ���¸� �����ϱ� ���� ������
    ID3D11Texture2D* FrameBuffer = nullptr; // ȭ�� ��¿� �ؽ�ó
    ID3D11RenderTargetView* FrameBufferRTV = nullptr; // �ؽ�ó�� ���� Ÿ������ ����ϴ� ��
    ID3D11RasterizerState* RasterizerState = nullptr; // �����Ͷ����� ����(�ø�, ä��� ��� �� ����)
    ID3D11Buffer* ConstantBuffer = nullptr; // ���̴��� �����͸� �����ϱ� ���� ��� ����

    FLOAT ClearColor[4] = { 0.025f, 0.025f, 0.025f, 1.0f }; // ȭ���� �ʱ�ȭ(clear)�� �� ����� ���� (RGBA)
    D3D11_VIEWPORT ViewportInfo; // ������ ������ �����ϴ� ����Ʈ ����

public:
    // ������ �ʱ�ȭ �Լ�
    void Create(HWND hWindow);

    // Direct3D ��ġ �� ���� ü���� �����ϴ� ���� �Լ�
    void CreateDeviceAndSwapChain(HWND hWindow);

    // Direct3D ��ġ �� ���� ü���� �����ϴ� �Լ�
    void ReleaseDeviceAndSwapChain();

    // ������ ���۸� �����ϴ� �Լ�
    void CreateFrameBuffer();

    // ������ ���۸� �����ϴ� �Լ�
    void ReleaseFrameBuffer();

    // �����Ͷ����� ���¸� �����ϴ� �Լ�
    void CreateRasterizerState();

    // �����Ͷ����� ���¸� �����ϴ� �Լ�
    void ReleaseRasterizerState();

    // �������� ���� ��� ���ҽ��� �����ϴ� �Լ�
    void Release();

    // ���� ü���� �� ���ۿ� ����Ʈ ���۸� ��ü�Ͽ� ȭ�鿡 ���
    void SwapBuffer();

public:
    // SimpleVertexShader: GPU���� ����Ǵ� ����(Vertex) ó�� ���̴� ��ü�� ��Ÿ���ϴ�.
    // �� ���̴��� �ַ� ���� ��ȯ(�� ���� �� ȭ�� ����), ���� ��� ���� ����մϴ�.
    ID3D11VertexShader* SimpleVertexShader;

    // SimplePixelShader: GPU���� ����Ǵ� �ȼ�(Pixel) ó�� ���̴� ��ü�� ��Ÿ���ϴ�.
    // �� ���̴��� ȭ�鿡 �׷��� �ȼ��� ���� �� ���� ������ ����� �����մϴ�.
    ID3D11PixelShader* SimplePixelShader;

    // SimpleInputLayout: GPU�� ���� �����͸� �ùٸ��� �ؼ��ϱ� ���� ����ϴ� �Է� ���̾ƿ�(Input Layout)�Դϴ�.
    // ���� �������� ����(��: ��ġ, ����, �ؽ�ó ��ǥ ��)�� �����ϸ�, ���� ���̴��� ����˴ϴ�.
    ID3D11InputLayout* SimpleInputLayout;

    // Stride: ���� �����Ϳ��� �� ����(Vertex)�� ����Ʈ ������ ��Ÿ���ϴ�.
    // ���� ���, ������ (x, y, z, r, g, b, a)�� �����͸� �����ٸ�, Stride�� sizeof(float) * 7 = 28 ����Ʈ�� �˴ϴ�.
    unsigned int Stride;

	// Shader ���� �Լ�
    void CreateShader();

	// Shader ���� �Լ�
    void ReleaseShader();

public:
    // D3D11 �������� �ʿ��� �غ� �۾��� ���� Prepare �Լ�
	void Prepare();

    //Simple Shader ����� ���� PrepareShader �Լ�
    void PrepareShader();

    //�������� Rendering ��û�� �� RenderPrimitive �Լ�
    void RenderPrimitive(ID3D11Buffer* pBuffer, UINT numVertices);
};


