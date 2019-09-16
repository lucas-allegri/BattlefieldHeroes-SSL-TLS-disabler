#include "InjectionMethod.h"
#include <string>
using namespace std;

int main(int argc, TCHAR *argv[])
{
	bool done = false;
	char szProc[MAX_PATH], szDll[MAX_PATH];
	char* szDllPath1 = (char*)malloc(MAX_PATH);
	char* szDll1 = "Hook.dll";
	szDllPath1 = GetCurrentDir();
	strcat_s(szDllPath1, MAX_PATH, "\\");
	strcat_s(szDllPath1, MAX_PATH, szDll1);

	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;


	wchar_t param1[50];
	mbstowcs(param1, (char*)argv[1], 49);
	LPWSTR param1lpwstr = param1;

	wchar_t param2[50];
	mbstowcs(param2, (char*)argv[2], 49);
	LPWSTR param2lpwstr = param2;

	if (CreateProcess(param1lpwstr, param2lpwstr, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo)) {
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}

	if (InjectDll(processInfo.dwProcessId, szDllPath1)) { done = true; }
	if (!done) { std::cout << "Something really weird just happened, oops!" << std::endl; }
	return 0;
}