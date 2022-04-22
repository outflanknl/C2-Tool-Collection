#pragma once

#include <windows.h>

//MSVCRT
WINBASEAPI void __cdecl MSVCRT$memset(void *dest, int c, size_t count);
WINBASEAPI size_t __cdecl MSVCRT$wcslen(const wchar_t *_Str);
WINBASEAPI int __cdecl MSVCRT$_vsnwprintf_s(wchar_t *buffer, size_t sizeOfBuffer, size_t count, const wchar_t *format, va_list argptr);

//KERNEL32
DECLSPEC_IMPORT HLOCAL WINAPI KERNEL32$LocalFree(HLOCAL hMem);
WINBASEAPI LPVOID WINAPI KERNEL32$HeapAlloc(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes);
WINBASEAPI HANDLE WINAPI KERNEL32$GetProcessHeap();
WINBASEAPI BOOL WINAPI KERNEL32$HeapFree(HANDLE, DWORD, PVOID);

//OLE32
DECLSPEC_IMPORT HRESULT WINAPI OLE32$CoCreateGuid(GUID *pguid);
DECLSPEC_IMPORT HRESULT WINAPI OLE32$StringFromCLSID(REFCLSID rclsid, LPOLESTR *lplpsz);
DECLSPEC_IMPORT VOID WINAPI OLE32$CoTaskMemFree(LPVOID pv);
DECLSPEC_IMPORT HRESULT WINAPI OLE32$CreateStreamOnHGlobal(HGLOBAL hGlobal, BOOL fDeleteOnRelease, LPSTREAM *ppstm);
DECLSPEC_IMPORT HRESULT WINAPI OLE32$IIDFromString(LPCOLESTR lpsz, LPIID lpiid);

//NETAPI32
DECLSPEC_IMPORT DWORD WINAPI NETAPI32$DsGetDcNameW(LPCWSTR ComputerName, LPCWSTR DomainName, GUID *DomainGuid, LPCWSTR SiteName, ULONG Flags, PDOMAIN_CONTROLLER_INFOW *DomainControllerInfo);
DECLSPEC_IMPORT DWORD WINAPI NETAPI32$DsGetDcNextW(HANDLE GetDcContextHandle, PULONG SockAddressCount, LPSOCKET_ADDRESS *SockAddresses, LPWSTR *DnsHostName);
DECLSPEC_IMPORT DWORD WINAPI NETAPI32$DsGetDcCloseW(HANDLE GetDcContextHandle);
DECLSPEC_IMPORT DWORD WINAPI NETAPI32$NetUserModalsGet(LPCWSTR servername, DWORD level, LPBYTE  *bufptr);
DECLSPEC_IMPORT DWORD WINAPI NETAPI32$DsGetDcOpenW(LPCWSTR DnsName, ULONG OptionFlags, LPCWSTR SiteName, GUID *DomainGuid, LPCWSTR DnsForestName, ULONG DcFlags, PHANDLE RetGetDcContext);
DECLSPEC_IMPORT DWORD WINAPI NETAPI32$NetApiBufferFree(LPVOID Buffer);
