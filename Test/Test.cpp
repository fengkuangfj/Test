// Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#define MOD_MAIN _T("��ģ��")

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

		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "��־ģ���ʼ����ϣ������������\n");
		_getch();






	}
	__finally
	{
		printfEx(MOD_MAIN, PRINTF_LEVEL_INFORMATION, "��������˳�");
		_getch();
		PrintfEx.Unload();
	}

	return 0;
}
