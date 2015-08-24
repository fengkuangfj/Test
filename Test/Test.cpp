// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

BOOL
	TestShellExecuteEx()
{
	BOOL				bRet				= FALSE;

	SHELLEXECUTEINFO	ShellExecuteInfo	= {0};


	__try
	{
		ShellExecuteInfo.cbSize = sizeof(ShellExecuteInfo);
		// ShellExecuteInfo.fMask = SEE_MASK_FLAG_DDEWAIT | SEE_MASK_FLAG_NO_UI;
		ShellExecuteInfo.lpVerb = _T("runas");
		ShellExecuteInfo.lpFile = _T("test1.exe");
		ShellExecuteInfo.nShow = SW_SHOWNORMAL;

		if (!ShellExecuteEx(&ShellExecuteInfo))
		{
			printfEx(NULL, PRINTF_LEVEL_ERROR, "ShellExecuteEx failed. (%d)", GetLastError());
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

BOOL
	TestCreateFile()
{
	BOOL	bRet	= FALSE;

	HANDLE	hFile	= INVALID_HANDLE_VALUE;


	__try
	{
		hFile = CreateFile(
			_T("C:\\1.txt"),
			FILE_GENERIC_READ | FILE_GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			NULL
			);
		if (INVALID_HANDLE_VALUE == hFile)
		{
			printfEx(NULL, PRINTF_LEVEL_ERROR, "CreateFile failed. (%d)", GetLastError());
			__leave;
		}

		bRet = TRUE;
	}
	__finally
	{
		if (INVALID_HANDLE_VALUE != hFile)
		{
			CloseHandle(hFile);
			hFile = INVALID_HANDLE_VALUE;
		}
	}

	return bRet;
}

int _tmain(int argc, _TCHAR* argv[])
{
	CPrintfEx	PrintfEx;
	CService	Service;


	PrintfEx.Init("G:\\GitHub\\Test\\Debug");


	_getch();


	TestShellExecuteEx();

// 	printf("按任意键安装 \n");
// 	_getch();
// 	Service.Install(
// 		_T("diskperf"),
// 		SERVICE_KERNEL_DRIVER,
// 		// SERVICE_BOOT_START,
// 		SERVICE_AUTO_START,
// 		SERVICE_ERROR_NORMAL,
// 		/*_T("C:\\Windows\\System32\\drivers\\diskperf.sys"),*/
// 		_T("C:\\Users\\Administrator\\Desktop\\diskperf.sys"),
// 		_T("PnP Filter"),
// 		NULL
// 		);
// 
// 	printf("按任意键启动 \n");
// 	_getch();
// 	Service.Start(_T("diskperf"));
// 
// 	printf("按任意键停止 \n");
// 	_getch();
// 	Service.Stop(_T("diskperf"));
// 
// 	printf("按任意键删除 \n");
// 	_getch();
// 	Service.Delete(_T("diskperf"));

	_getch();

	CProcessPrivilege::Adjust(TRUE, 0, SE_CREATE_TOKEN_NAME          );
	CProcessPrivilege::Adjust(TRUE, 0, SE_ASSIGNPRIMARYTOKEN_NAME    );
	CProcessPrivilege::Adjust(TRUE, 0, SE_LOCK_MEMORY_NAME           );
	CProcessPrivilege::Adjust(TRUE, 0, SE_INCREASE_QUOTA_NAME        );
	CProcessPrivilege::Adjust(TRUE, 0, SE_UNSOLICITED_INPUT_NAME     );
	CProcessPrivilege::Adjust(TRUE, 0, SE_MACHINE_ACCOUNT_NAME       );
	CProcessPrivilege::Adjust(TRUE, 0, SE_TCB_NAME                   );
	CProcessPrivilege::Adjust(TRUE, 0, SE_SECURITY_NAME              );
	CProcessPrivilege::Adjust(TRUE, 0, SE_TAKE_OWNERSHIP_NAME        );
	CProcessPrivilege::Adjust(TRUE, 0, SE_LOAD_DRIVER_NAME           );
	CProcessPrivilege::Adjust(TRUE, 0, SE_SYSTEM_PROFILE_NAME        );
	CProcessPrivilege::Adjust(TRUE, 0, SE_SYSTEMTIME_NAME            );
	CProcessPrivilege::Adjust(TRUE, 0, SE_PROF_SINGLE_PROCESS_NAME   );
	CProcessPrivilege::Adjust(TRUE, 0, SE_INC_BASE_PRIORITY_NAME     );
	CProcessPrivilege::Adjust(TRUE, 0, SE_CREATE_PAGEFILE_NAME       );
	CProcessPrivilege::Adjust(TRUE, 0, SE_CREATE_PERMANENT_NAME      );
	CProcessPrivilege::Adjust(TRUE, 0, SE_BACKUP_NAME                );
	CProcessPrivilege::Adjust(TRUE, 0, SE_RESTORE_NAME               );
	CProcessPrivilege::Adjust(TRUE, 0, SE_SHUTDOWN_NAME              );
	CProcessPrivilege::Adjust(TRUE, 0, SE_DEBUG_NAME                 );
	CProcessPrivilege::Adjust(TRUE, 0, SE_AUDIT_NAME                 );
	CProcessPrivilege::Adjust(TRUE, 0, SE_SYSTEM_ENVIRONMENT_NAME    );
	CProcessPrivilege::Adjust(TRUE, 0, SE_CHANGE_NOTIFY_NAME         );
	CProcessPrivilege::Adjust(TRUE, 0, SE_REMOTE_SHUTDOWN_NAME       );
	CProcessPrivilege::Adjust(TRUE, 0, SE_UNDOCK_NAME                );
	CProcessPrivilege::Adjust(TRUE, 0, SE_SYNC_AGENT_NAME            );
	CProcessPrivilege::Adjust(TRUE, 0, SE_ENABLE_DELEGATION_NAME     );
	CProcessPrivilege::Adjust(TRUE, 0, SE_MANAGE_VOLUME_NAME         );
	CProcessPrivilege::Adjust(TRUE, 0, SE_IMPERSONATE_NAME           );
	CProcessPrivilege::Adjust(TRUE, 0, SE_CREATE_GLOBAL_NAME         );
	CProcessPrivilege::Adjust(TRUE, 0, SE_TRUSTED_CREDMAN_ACCESS_NAME);
	CProcessPrivilege::Adjust(TRUE, 0, SE_RELABEL_NAME               );
	CProcessPrivilege::Adjust(TRUE, 0, SE_INC_WORKING_SET_NAME       );
	CProcessPrivilege::Adjust(TRUE, 0, SE_TIME_ZONE_NAME             );
	CProcessPrivilege::Adjust(TRUE, 0, SE_CREATE_SYMBOLIC_LINK_NAME  );

	TestCreateFile();

	_getch();

	PrintfEx.Unload();

	return 0;
}

