// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#define MOD_MAIN _T("主模块")

int _tmain(int argc, _TCHAR* argv[])
{
	TCHAR			tchPdbDir[MAX_PATH] = {0};
	LPTSTR			lpPosition			= NULL;

	CPrintfEx		PrintfEx;
	CVolumeDetector	VolumeDetector;
	CService		Service;


	__try
	{
		if (GetModuleFileName(NULL, tchPdbDir, _countof(tchPdbDir)))
		{
			lpPosition = _tcsrchr(tchPdbDir, _T('\\'));
			if (lpPosition)
			{
				*(lpPosition) = _T('\0');

				PrintfEx.Init(tchPdbDir, TRUE);
			}
		}

		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "日志模块初始化完毕，按任意键继续\n");
		_getch();

		if (!Service.Register(_T("test")))
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "Service.Register failed");
			__leave;
		}

		if (!VolumeDetector.Init(NULL, NULL, FALSE))
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "VolumeDetector.Init failed");
			__leave;
		}

		if (!VolumeDetector.MessageLoop())
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "VolumeDetector.MessageLoop failed");
			__leave;
		}
		
		if (!VolumeDetector.Unload())
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "VolumeDetector.Unload failed");
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
