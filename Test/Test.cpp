// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

BOOL
	InitMod(
	__in BOOL bService,
	__in BOOL bCreateMassageLoop,
	__in BOOL bCreateMassageLoopThread
	)
{
	BOOL			bRet			= FALSE;

	TCHAR			tchPdbDir[MAX_PATH] = {0};
	LPTSTR			lpPosition			= NULL;

	CPrintfEx		PrintfEx;
	CVolumeDetector	VolumeDetector;


	__try
	{
		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "begin");

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

		if (!VolumeDetector.Init(NULL, bService ? CService::ms_SvcStatusHandle : NULL, bService, bCreateMassageLoop, bCreateMassageLoopThread))
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "VolumeDetector.Init failed");
			__leave;
		}

		bRet = TRUE;
	}
	__finally
	{
		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "end");
	}

	return bRet;
}

BOOL
	UnloadMod()
{
	BOOL			bRet			= FALSE;

	CPrintfEx		PrintfEx;
	CVolumeDetector	VolumeDetector;


	__try
	{
		if (!VolumeDetector.Unload())
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "VolumeDetector.Unload failed");
			__leave;
		}

		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "按任意键退出");
		_getch();
		PrintfEx.Unload();

		bRet = TRUE;
	}
	__finally
	{
		;
	}

	return bRet;
}

BOOL
	Test()
{
	BOOL			bRet			= FALSE;

	CVolumeDetector	VolumeDetector;


	__try
	{
		if (!VolumeDetector.Init(NULL, NULL, FALSE, TRUE, FALSE))
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "VolumeDetector.Init failed");
			__leave;
		}

		if (!VolumeDetector.MessageLoop(TRUE))
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "VolumeDetector.MessageLoop failed");
			__leave;
		}

		if (!VolumeDetector.Unload())
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "VolumeDetector.Unload failed");
			__leave;
		}

		bRet = TRUE;
	}
	__finally
	{
		;
	}

	return bRet;
}

int _tmain(int argc, _TCHAR* argv[])
{
	CService Service;


	__try
	{
		Sleep(10000);

		if (!Service.Register(_T("test"), InitMod, UnloadMod))
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "Service.Register failed");
			__leave;
		}
	}
	__finally
	{
		;
	}

	return 0;


	/*
	TCHAR			tchPdbDir[MAX_PATH] = {0};
	LPTSTR			lpPosition			= NULL;

	CPrintfEx		PrintfEx;


	__try
	{
		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "begin");

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

		Test();




	}
	__finally
	{
		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "按任意键退出");
		_getch();
		PrintfEx.Unload();

		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "end");
	}

	return 0;
	*/
}
