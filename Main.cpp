#include <windows.h>

INT WINAPI WinMain(
HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPSTR pszCmdLine,
INT nCmdShow)
{
	HWND hNotepadWnd, hEditWnd;
	CHAR sz[1024];
	ShellExecute(NULL, NULL, "notepad.exe", NULL, NULL, SW_SHOWNORMAL);
	Sleep(1000);
	hNotepadWnd = FindWindow("Notepad", NULL);
	hEditWnd = FindWindowEx(hNotepadWnd, NULL, "EDIT", NULL);
	lstrcpy(sz, "テストです。");
	SendMessage(hEditWnd, WM_SETTEXT, 0, (LPARAM)sz);
	Sleep(1000);
	lstrcat(sz, "\r\n\r\nテスト２です。");
	SendMessage(hEditWnd, WM_SETTEXT, 0, (LPARAM)sz);
	return 0;
}
