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

		CrushHandlerInfo.EhType = EH_TYPE_S;
		CrushHandlerInfo.MiniDumpType = MiniDumpWithFullMemory;

		CSimpleDump::GetInstance()->RegisterCrushHandler(&CrushHandlerInfo);

		if (GetModuleFileName(NULL, tchLogPath, _countof(tchLogPath)))
		{
			lpPosition = _tcsrchr(tchLogPath, _T('.'));
			if (lpPosition)
			{
				*(lpPosition + 1) = _T('\0');
				_tcscat_s(tchLogPath, _countof(tchLogPath), _T("log"));

				if (!CSimpleLog::GetInstance(tchLogPath))
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
		CSimpleLog::ReleaseInstance();
		CSimpleDump::ReleaseInstance();
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

		if (!UnloadMod())
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "UnloadMod failed");
			bRet = FALSE;
		}
	}
	__finally
	{
		CPrintfEx::ReleaseInstance();
	}

	return bRet;
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*
	// 服务
	__try
	{
		if (!CService::GetInstance()->Register(_T("test"), InitMod, NULL, UnloadMod))
		{
			printfEx(MOD_MAIN, PRINTF_LEVEL_ERROR, "Service.Register failed");
			__leave;
		}
	}
	__finally
	{
		CService::ReleaseInstance();
	}
	*/

	// 非服务
	Test();

	return 0;
}
