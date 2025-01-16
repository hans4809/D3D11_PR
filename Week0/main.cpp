#include <windows.h>
#include "Renderer.h"

// ���� �޽����� ó���� �Լ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		// Signal that the app should quit
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

// �ﰢ���� �ϵ� �ڵ�
RendererData::FVertexSimple triangle_vertices[] =
{
	{  0.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f }, // Top vertex (red)
	{  1.0f, -1.0f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f }, // Bottom-right vertex (green)
	{ -1.0f, -1.0f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f }  // Bottom-left vertex (blue)
};

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// ������ Ŭ���� �̸�
	WCHAR WindowClass[] = L"JungleWindowClass";

	// ������ Ÿ��Ʋ�ٿ� ǥ�õ� �̸�
	WCHAR Title[] = L"Game Tech Lab";

	// ���� �޽����� ó���� �Լ��� WndProc�� �Լ� �����͸� WindowClass ����ü�� �ִ´�.
	WNDCLASSW wndclass = { 
		/*UINT style*/0, 
		/*WNDPROC lpfnWndProc*/WndProc, 
		/*int cbClsExtra*/0, 
		/*int cbWndExtra*/0, 
		/*HINSTANCE hInstance*/0, 
		/*HICON hIcon*/0, 
		/*HCURSOR hCursor*/0, 
		/*HBRUSH hbrBackground*/0, 
		/*LPCWSTR lpszMenuName*/0, 
		/*LPCWSTR lpszClassName*/WindowClass
	};

	// ������ Ŭ���� ���
	RegisterClassW(&wndclass);

	// 1024 x 1024 ũ�⿡ ������ ����
	HWND hWnd = CreateWindowExW(0, WindowClass, Title, WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 1024, 1024,
		nullptr, nullptr, hInstance, nullptr);

	// ���� �����ϴ� �ڵ带 ���⿡ �߰��մϴ�.

	// Renderer Class�� �����մϴ�.
	URenderer renderer;

	// D3D11 �����ϴ� �Լ��� ȣ���մϴ�.
	renderer.Create(hWnd);

	// ������ ���� ���Ŀ� ���̴��� �����ϴ� �Լ��� ȣ���մϴ�.
	renderer.CreateShader();

	// Renderer�� Shader ���� ���Ŀ� ���ؽ� ���۸� �����մϴ�.
	RendererData::FVertexSimple* vertices = triangle_vertices;
	UINT ByteWidth = sizeof(triangle_vertices);
	UINT numVertices = sizeof(triangle_vertices) / sizeof(RendererData::FVertexSimple);

	// ����
	D3D11_BUFFER_DESC vertexbufferdesc = {};
	vertexbufferdesc.ByteWidth = ByteWidth;
	vertexbufferdesc.Usage = D3D11_USAGE_IMMUTABLE;
	vertexbufferdesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA vertexbufferSRD = { vertices };

	ID3D11Buffer* vertexBuffer;

	renderer.Device->CreateBuffer(&vertexbufferdesc, &vertexbufferSRD, &vertexBuffer);

	bool bIsExit = false;

	// Main Loop (Quit Message�� ������ ������ �Ʒ� Loop�� ������ �����ϰ� ��)
	while (bIsExit == false)
	{
		MSG msg;

		// ó���� �޽����� �� �̻� ������ ���� ����
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			// Ű �Է� �޽����� ����
			TranslateMessage(&msg);

			// �޽����� ������ ������ ���ν����� ����, �޽����� ������ ����� WndProc ���� ���޵�
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT)
			{
				bIsExit = true;
				break;
			}
		}

		////////////////////////////////////////////
		// �Ź� ����Ǵ� �ڵ带 ���⿡ �߰��մϴ�.

		// �غ� �۾�
		renderer.Prepare();
		renderer.PrepareShader();

		// ������ ���ؽ� ���۸� �Ѱ� �������� ������ ��û
		renderer.RenderPrimitive(vertexBuffer, numVertices);

		// ���� ȭ�鿡 �������� ���ۿ� �׸��� �۾��� ���� ���۸� ���� ��ȯ�մϴ�.
		renderer.SwapBuffer();
		////////////////////////////////////////////
	}


	// �Ҹ��ϴ� �ڵ带 ���⿡ �߰��մϴ�.
	// 
	// ���ؽ� ���� �Ҹ��� Renderer �Ҹ����� ó���մϴ�.
	vertexBuffer->Release();
	// ������ �Ҹ� ������ ���̴��� �Ҹ� ��Ű�� �Լ��� ȣ���մϴ�.
	renderer.ReleaseShader();
	renderer.Release();

	return 0;
}