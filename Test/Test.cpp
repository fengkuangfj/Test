// Test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CPrintfEx	PrintfEx;
	CService	Service;


	PrintfEx.Init("G:\\GitHub\\Test\\Debug");

	printf("按任意键安装 \n");
	_getch();
	Service.Install(
		_T("diskperf"),
		SERVICE_KERNEL_DRIVER,
		// SERVICE_BOOT_START,
		SERVICE_AUTO_START,
		SERVICE_ERROR_NORMAL,
		/*_T("C:\\Windows\\System32\\drivers\\diskperf.sys"),*/
		_T("C:\\Users\\Administrator\\Desktop\\diskperf.sys"),
		_T("PnP Filter"),
		NULL
		);

	printf("按任意键启动 \n");
	_getch();
	Service.Start(_T("diskperf"));

	printf("按任意键停止 \n");
	_getch();
	Service.Stop(_T("diskperf"));

	printf("按任意键删除 \n");
	_getch();
	Service.Delete(_T("diskperf"));

	_getch();

	PrintfEx.Unload();

	return 0;
}
