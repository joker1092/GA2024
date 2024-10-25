// VirtuaAlloc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <Windows.h>
#include <stdio.h>
#include <conio.h>


int main()
{
	// alloc and reserve 1MB
	DWORD* pReservedMemory = (DWORD*)VirtualAlloc(NULL, 1 * 1024 * 1024, MEM_RESERVE, PAGE_READWRITE);
	if (!pReservedMemory)
	{
		__debugbreak();
	}
	//pReservedMemory[0] = 100;	// Access violation, 'pReservedMemory' is not committed yet.

	// commit 512KB of 1MB
	DWORD* pCommittedMemory = (DWORD*)VirtualAlloc(pReservedMemory, 512 * 1024, MEM_COMMIT, PAGE_READWRITE);
	if (!pCommittedMemory)
	{
		__debugbreak();
	}
	pCommittedMemory[0] = 100;	// Access violation, 'pReservedMemory' is not committed yet.
	wprintf(L"address: %p[0] : %u\n", pCommittedMemory, pCommittedMemory[0]);
	// free memory
	if (!VirtualFree(pCommittedMemory, 0, MEM_RELEASE))
	{
		__debugbreak();
	}
	wprintf_s(L"Press any key.\n");
	_getch();
	return 0;
}

