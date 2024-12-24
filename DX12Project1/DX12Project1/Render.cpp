#include "Windows.h"
#include "tchar.h"
#include "Device.h"
#include "Render.h"
#include "Shader.h"

TCHAR* g_WindowName = _T("DX12Project1");

//���� ������

//���� ����ü
struct Vertex
{
	float x, y, z;
	float r, g, b, a;
};

//���� ����
ID3D12Resource* g_pVB = nullptr;
D3D12_VERTEX_BUFFER_VIEW* g_pVBView = nullptr;

//�Է� ���̾ƿ�
D3D12_INPUT_LAYOUT_DESC* g_pVBLayout = nullptr; //DX12


//=============================================================================
//���� �����͵�

COLOR g_ClearColor = { 0.0f, 0.125f, 0.3f, 1 }; //����
//COLOR g_ClearColor(0.7f, 0.7f, 0.7f, 1);

//���� ������ �� ������ �ڿ��� �ҷ��´�
int DataLoading()
{
	//������ �ε�/���� �ڵ�
	//todo:...

	return TRUE;
}

//���� ������ �� ������ �ڿ��� �����Ѵ�
void DataRelease()
{
	//todo:...
}

//���� ���
void ShowInfo()
{
	PutFPS(0, 0);

	static bool bShow = true;

	if (IsKeyUp(VK_F1)) bShow ^= true;

	if (!bShow)
	{
		//ynTextDraw(1,20, COLOR(1, 1, 0, 1), _T("[Help] F1"));
		return;
	}

	//topic
	{
		int x = 300, y = 50;
		COLOR col(1, 1, 1, 1);
		COLOR col2(1, 1, 0, 1);
		ynTextDraw(x, y, col, _T("�� %s"), g_WindowName);

		y += 24;
		WCHAR* msg = _T(
			"1.�⺻�����ӿ�ũ ����.\n"
			"2.HW ������ ����̽�(D3D Device) �� ����.\n"
			"3.Idle �ð� ������.\n"
			"4.����ü�� Swap(Flipping) chain �� ���� \n"
		);
		ynTextDraw(x, y, col2, msg);
	}

	//�ý��� ����
	{
		int x = 1, y = 14;
		COLOR col(0, 1, 0, 1);
		SystemInfo(x, y, col);
	}

	int x = 300, y = 300;
	static int cnt = 0;
	COLOR col(1, 1, 0, 1);
	ynTextDraw(x, y, col, _T("Hello, Device!!    cnt=%08d"), ++cnt);

	y += 24;
	ynTextDraw(x, y, col, _T("* HW Rendering Device (%s) ���� *"), g_strFeatLv);

}

//���� ��� ������
void SceneRender()
{
	//===============================================================
	//���� / �ý��� ����

	//������ ����, ����, ī�޶� �� ����

	//��� ����

	//===============================================================
	//��� �׸���
	//����Ÿ�� �����
	ClearBackBuffer(g_ClearColor);

	//��� ������

	//���� ���
	ShowInfo();

	//===============================================================
	//��� �׸��� ����
	Flip();
}
