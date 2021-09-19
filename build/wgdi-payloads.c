
HDC hdc;        // initializing some common variables
int scrx, scry;

DWORD WINAPI WhiteGlitch() {
	// this is a gdi payload that makes screen glitch.
	scrx = GetSystemMetrics(SM_CXSCREEN);
	scry = GetSystemMetrics(SM_CYSCREEN);
	hdc = GetDC(0);
	for (;;){
		StretchBlt(hdc, 0, 0, scrx-50, scry-50, hdc, 0, 0, scrx, scry, SRCPAINT);
		Sleep(3000);
		StretchBlt(hdc, 50, 50, scrx, scry, hdc, 0, 0, scrx, scry, SRCPAINT);
		Sleep(3000);
		StretchBlt(hdc, 50, scry-50, 0, scry, hdc, 0, 0, scrx, scry, SRCPAINT);
		Sleep(3000);
		StretchBlt(hdc, scrx-50, 50, scrx, 0, hdc, 0, 0, scrx, scry, SRCPAINT);
		Sleep(3000);
	}
}


DWORD WINAPI InvTimeTime() {
	// Invalidating screen to clean it from glitches every three seconds. 
	scrx = GetSystemMetrics(SM_CXSCREEN);
	scry = GetSystemMetrics(SM_CYSCREEN);
	for(;;){
		RECT rect={0, 0, scrx, scry};
		InvalidateRect(0, &rect, TRUE);
		Sleep(3000);
	}
}


DWORD WINAPI TunnelCorrupted() {
	// this one was a bad try to make new tunnel effect. 
	HDC hdc = GetDC(0);
	scrx = GetSystemMetrics(SM_CXSCREEN);
	scry = GetSystemMetrics(SM_CYSCREEN);
	for(;;) {
		StretchBlt(hdc, 50, 0, scrx-100, scry-50, hdc, 0, 0, scrx, scry, SRCCOPY);
		Sleep(3000);
		StretchBlt(hdc, 0, 50, scrx-50, scry-100, hdc, 0, 0, scrx, scry, SRCCOPY);
		Sleep(3000);
	}
}