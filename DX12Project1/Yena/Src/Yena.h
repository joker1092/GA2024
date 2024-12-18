// 
//! \file   Yena.h
//! \brief  ���� / ���� / ��� �����ӿ�ũ ���.
//! 
//! \author	���ȫ / Kihong Kim / onlysonim@gmail.com
//! \date	2020.08.22. Updated. (DX12.x Windows 10 SDK 10.0.x)
//
#pragma once
#pragma warning(disable:4996)

/////////////////////////////////////////////////////////////////////////////
//
// �⺻ �ʼ� ��� ����
//
/////////////////////////////////////////////////////////////////////////////
#include "windows.h"		//Windows �⺻ ���.
#include "tchar.h"

#include "ynError.h"		//����\����ó�� �����ӿ�ũ. 
#include "ynWindow.h"		//����\���� �����ӿ�ũ.
#include "ynGraphics.h"		//����\DX ǥ�� ��� �� ���� Ŭ����.
//#include "ynTimer.h"		//����\Ÿ�̸� Ŭ����.

 


///////////////////////////////////////////////////////////////////////////////
//
// ���� �����ӿ�ũ ����
//
///////////////////////////////////////////////////////////////////////////////
//! \defgroup	Yena ���� �����ӿ�ũ
//!	\brief		���� ��� �����ӿ�ũ�� Ȯ�� ���̺귯��. \n
//!	\details	3D ���ø����̼� ���ۿ� ���� ��� �����ӿ�ũ�� Ȯ�� ���̺귯���� �����մϴ�.
//! \n \copydetails YENA
//! \n\n \copydetails Yena
//! \par		�ҽ� ����
//! \ref		Yena.h, Yena.cpp, ynWindow.h, ynDXAfx.h, ynError.h, ynTimer.h 
//
//! \namespace	YENA
//! \brief		���� / ���� / �ֻ��� ���ӽ����̽�
//! \details	���ӽ����̽� YENA ���� ���� �� ���� ��ü���� ���� ���� ������, ���, ��ũ��, �Լ�, ���� Ŭ���� ���� �����մϴ�.
//! \note		D3D �������̽����� �������� ǥ��, ȣȯ�� ��� �� �Ϲ�ȭ�� ���� �������Ͽ����ϴ�. 
//! 
//!	2020.08.22 ���ȫ Kihong.Kim / onlysonim@gmail.com 
//! \ingroup	Yena 
namespace YENA
{

	// ����(����) ������, �Լ� �� �������̽��� �߰��� ���⿡...
	//...

	//GLOBALCONST TCHAR* yn_strProjVer	= _T("v.0.9");
	//GLOBALCONST TCHAR* yn_strEngVer	= _T("v.1.0.0@1");
	//GLOBALCONST TCHAR* yn_strBuildVer	= _T("Build.20.0822");

}


using namespace YENA;




/****************** The end of file "Yena.h" ***********************************/