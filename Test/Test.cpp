// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Test.h"

BOOL
	InitMod(
	__in_opt LPINIT_MOD_ARGUMENTS lpInitModArguments
	)
{
	BOOL				bRet					= FALSE;

	CRUSH_HANDLER_INFO	CrushHandlerInfo;
	TCHAR				tchLogPath[MAX_PATH]	= {0};
	LPTSTR				lpPosition				= NULL;


	__try
	{
		ZeroMemory(&CrushHandlerInfo, sizeof(CrushHandlerInfo));

		if (!CPrintfEx::GetInstance()->Init())
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "PrintfEx.Init failed");

		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "按任意键继续");
		_getch();

		CrushHandlerInfo.EhType = EH_TYPE_S;
		CrushHandlerInfo.bFirstHandler = TRUE;
		CrushHandlerInfo.MiniDumpType = MiniDumpWithFullMemory;

		CSimpleDump::GetInstance()->RegisterCrushHandler(&CrushHandlerInfo);

		if (GetModuleFileName(NULL, tchLogPath, _countof(tchLogPath)))
		{
			lpPosition = _tcsrchr(tchLogPath, _T('.'));
			if (lpPosition)
			{
				*(lpPosition + 1) = _T('\0');
				_tcscat_s(tchLogPath, _countof(tchLogPath), _T("log"));

				if (!CSimpleLog::GetInstance()->Init(tchLogPath))
					printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "SimpleLog.Init failed");
			}
		}

		bRet = TRUE;
	}
	__finally
	{
		;
	}

	return bRet;
}

BOOL
	UnloadMod()
{
	BOOL bRet = TRUE;


	__try
	{
		CSimpleLog::GetInstance()->Unload();
		CSimpleLog::ReleaseInstance();

		CSimpleDump::ReleaseInstance();

		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "按任意键退出");
		CPrintfEx::ReleaseInstance();
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
	BOOL bRet = TRUE;


	__try
	{
		if (!InitMod(NULL))
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
	/*
	// 服务
	CPrintfEx	PrintfEx;
	CService	Service;


	__try
	{
		if (!PrintfEx.Init())
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "PrintfEx.Init failed");

		if (!Service.Register(_T("test"), InitMod, NULL, UnloadMod))
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
	*/

	// 非服务
	Test();
	return 0;

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
