#pragma once

#define MOD_MAIN _T("��ģ��")

#include <Windows.h>
#include <conio.h>

BOOL
	InitMod(
	__in_opt LPINIT_MOD_ARGUMENTS lpInitModArguments
	);

BOOL
	UnloadMod();

BOOL
	Test();
