// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define MOD_MAIN _T("主模块")

VOID
	Test()
{
	HANDLE				hVolume					= INVALID_HANDLE_VALUE;
	ENDISK_QUERYVOLUME	EnDiskQueryVolumeIn		= {0};
	ENDISK_QUERYVOLUME	EnDiskQueryVolumeOut	= {0};
	DWORD				dwRet					= 0;
	HANDLE				hFile					= INVALID_HANDLE_VALUE;

	CService			Service;


	__try
	{
		Service.Stop(_T("EnDisk"));
		Service.Delete(_T("EnDisk"));

		if (!Service.Install(
			_T("EnDisk"),
			SERVICE_KERNEL_DRIVER,
			SERVICE_BOOT_START,
			SERVICE_ERROR_NORMAL,
			_T("C:\\Documents and Settings\\Administrator\\桌面\\test\\EnDisk.sys"),
			_T("Pnp Filter"),
			NULL			
			))
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "Install failed");
			__leave;
		}

		if (!Service.Start(_T("EnDisk")))
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "Start failed");
			__leave;
		}

		hVolume = CreateFile(
			_T("\\\\.\\EnDiskDevice"),
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			NULL,
			NULL
			);
		if (INVALID_HANDLE_VALUE == hVolume)
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "CreateFile failed. (%d)", GetLastError());
			__leave;
		}

		EnDiskQueryVolumeIn.TypeSize = sizeof(EnDiskQueryVolumeIn);
		EnDiskQueryVolumeOut.TypeSize = sizeof(EnDiskQueryVolumeOut);
		if (!DeviceIoControl(
			hVolume,
			IOCTL_ENDISK_QUERYVOLUME,
			&EnDiskQueryVolumeIn,
			sizeof(EnDiskQueryVolumeIn),
			&EnDiskQueryVolumeOut,
			sizeof(EnDiskQueryVolumeOut),
			&dwRet,
			NULL
			))
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "DeviceIoControl failed. (%d)", GetLastError());
			__leave;
		}

		hFile = CreateFile(
			_T("F:\\1.txt"),
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "CreateFile failed. (%d)", GetLastError());
			__leave;
		}
	}
	__finally
	{
		if (INVALID_HANDLE_VALUE != hVolume)
		{
			CloseHandle(hVolume);
			hVolume = INVALID_HANDLE_VALUE;
		}

		if (INVALID_HANDLE_VALUE != hFile)
		{
			CloseHandle(hFile);
			hFile = INVALID_HANDLE_VALUE;
		}
	}

	return ;
}

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR		tchPdbDir[MAX_PATH] = {0};
	LPTSTR		lpPosition			= NULL;

	CPrintfEx	PrintfEx;


	__try
	{
		if (GetModuleFileName(NULL, tchPdbDir, _countof(tchPdbDir)))
		{
			lpPosition = _tcsrchr(tchPdbDir, _T('\\'));
			if (lpPosition)
			{
				*(lpPosition) = _T('\0');

				PrintfEx.Init(tchPdbDir);
			}
		}

		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "日志模块初始化完毕，按任意键继续\n");
		_getch();

		Test();






	}
	__finally
	{
		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "按任意键退出");
		_getch();
		PrintfEx.Unload();
	}

	return 0;
}
