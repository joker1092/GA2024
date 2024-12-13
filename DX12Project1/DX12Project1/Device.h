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

//DX타입과 상수 재정의 ==> 버전별 호환성 목적
//장치관련
typedef ID3D12Device*	LPDEVICE;

//math 타입
typedef XMMATRIX	MATRIXA;
typedef XMFLOAT4X4	MATRIX;
typedef XMVECTOR	VECTOR;
typedef XMFLOAT4	VECTOR4;
typedef XMFLOAT3	VECTOR3;
typedef XMFLOAT2	VECTOR2;

//색상
typedef XMFLOAT4	COLOR;

//DX 및 장치 관련 함수 및 데이터

int DXSetup(HWND hwnd);
void DXRelease();