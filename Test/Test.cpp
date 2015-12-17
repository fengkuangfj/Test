// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

BOOL
	InitMod(
	__in_opt LPINIT_MOD_ARGUMENTS lpInitModArguments
	)
{
	BOOL							bRet						= FALSE;

	TCHAR							tchPdbDir[MAX_PATH]			= {0};
	LPTSTR							lpPosition					= NULL;
	VOLUME_DETECTOR_INIT_ARGUMENTS	VolumeDetectorInitArguments = {0};

	CPrintfEx						PrintfEx;
	CVolumeDetector					VolumeDetector;

	printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "begin");

	__try
	{
		if (!PrintfEx.Init())
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "PrintfEx.Init failed");

		if (GetModuleFileName(NULL, tchPdbDir, _countof(tchPdbDir)))
		{
			lpPosition = _tcsrchr(tchPdbDir, _T('\\'));
			if (lpPosition)
			{
				*(lpPosition) = _T('\0');
				// 
			}
		}

		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "日志模块初始化完毕，按任意键继续");
		_getch();

		if (lpInitModArguments)
		{
			_tcscat_s(VolumeDetectorInitArguments.tchModuleName, _countof(VolumeDetectorInitArguments.tchModuleName), lpInitModArguments->tchModuleName);
			VolumeDetectorInitArguments.hWindow = lpInitModArguments->hWindow;
			VolumeDetectorInitArguments.lpfnWndProc = lpInitModArguments->lpfnWndProc;
			VolumeDetectorInitArguments.bCreateMassageLoop = lpInitModArguments->bCreateMassageLoop;
		}

		if (!VolumeDetector.Init(&VolumeDetectorInitArguments))
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "VolumeDetector.Init failed");
			__leave;
		}

		bRet = TRUE;
	}
	__finally
	{
		;
	}

	printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "end");

	return bRet;
}

BOOL
	UnloadMod()
{
	BOOL			bRet			= TRUE;

	CVolumeDetector	VolumeDetector;


	__try
	{
		if (!VolumeDetector.Unload())
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "VolumeDetector.Unload failed");
			bRet = FALSE;
		}

		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "按任意键退出");
		_getch();
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
	BOOL				bRet				= TRUE;

	INIT_MOD_ARGUMENTS	InitModArguments	= {0};


	__try
	{
		InitModArguments.bCreateMassageLoop = TRUE;
		if (!InitMod(&InitModArguments))
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "InitMod failed");
			bRet = FALSE;
		}

		_getch();

		if (!UnloadMod())
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "UnloadMod failed");
			bRet = FALSE;
		}
	}
	__finally
	{
		;
	}

	return bRet;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// 服务
	CService			Service;

	INIT_MOD_ARGUMENTS	InitModArguments = {0};


	__try
	{
		InitModArguments.bCreateMassageLoop = TRUE;
		if (!Service.Register(_T("test"), InitMod, &InitModArguments, UnloadMod))
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
	// 非服务
	Test();
	return 0;
	*/

	/*
	// 模板
	TCHAR			tchPdbDir[MAX_PATH] = {0};
	LPTSTR			lpPosition			= NULL;

	CPrintfEx		PrintfEx;

	printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "begin");

	__try
	{
		if (GetModuleFileName(NULL, tchPdbDir, _countof(tchPdbDir)))
		{
			lpPosition = _tcsrchr(tchPdbDir, _T('\\'));
			if (lpPosition)
			{
				*(lpPosition) = _T('\0');

				if (!PrintfEx.Init(tchPdbDir, TRUE))
					printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "PrintfEx.Init failed");
			}
		}

		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "日志模块初始化完毕，按任意键继续");
		_getch();






	}
	__finally
	{
		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "按任意键退出");
		_getch();
		if (!PrintfEx.Unload())
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "PrintfEx.Unload failed");
	}

	printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "end");

	return 0;
	*/
}
