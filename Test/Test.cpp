// Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CPrintfEx	PrintfEx;
	CService	Service;


	PrintfEx.Init("G:\\GitHub\\Test\\Debug");

	Service.Stop(_T("WSearch"));
	Service.Disable(_T("WSearch"));


	_getch();

	PrintfEx.Unload();

	return 0;
}
