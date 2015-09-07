// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define MOD_MAIN _T("主模块")

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR			tchPdbDir[MAX_PATH] = {0};
	LPTSTR			lpPosition			= NULL;

	CPrintfEx		PrintfEx;

	CDeviceMonitor	DeviceMonitor;


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

		if (!DeviceMonitor.Init())
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "Init failed");
			__leave;
		}

		if (!DeviceMonitor.MessageLoop())
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "MessageLoop failed");
			__leave;
		}






	}
	__finally
	{
		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "按任意键退出");
		_getch();
		PrintfEx.Unload();
	}

	return 0;
}
