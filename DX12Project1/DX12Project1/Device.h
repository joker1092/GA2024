#pragma once
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>

#include <memory>
#include <chrono>

using namespace std::chrono;

#define TIME_MAX 9223372056854775807 //std::chrono::millseconds::max()

#include <d3d12.h>
#pragma comment(lib,"d3d12")

#include <DirectXMath.h>
using namespace DirectX;

#include <dxgi1_4.h>
#include <dxgi1_6.h>
#pragma comment(lib,"dxgi")

//DXŸ�԰� ��� ������ ==> ������ ȣȯ�� ����
//��ġ����
typedef ID3D12Device*	LPDEVICE;

//math Ÿ��
typedef XMMATRIX	MATRIXA;
typedef XMFLOAT4X4	MATRIX;
typedef XMVECTOR	VECTOR;
typedef XMFLOAT4	VECTOR4;
typedef XMFLOAT3	VECTOR3;
typedef XMFLOAT2	VECTOR2;

//����
typedef XMFLOAT4	COLOR;

//DX �� ��ġ ���� �Լ� �� ������

int DXSetup(HWND hwnd);
void DXRelease();