#include "InjectionMethod.h"
#include <string>
using namespace std;

int main(int argc, TCHAR *argv[])
{
	bool done = false;
	char szProc[MAX_PATH], szDll[MAX_PATH];
	char* szDllPath1 = (char*)malloc(MAX_PATH);
	char* szExePath1 = (char*)malloc(MAX_PATH);
	char* szProc1 = "BFHeroes.exe";
	char* szDll1 = "Hook.dll";
	char* szEXE1 = "BFHeroes.exe";
	szDllPath1 = GetCurrentDir();
	strcat_s(szDllPath1, MAX_PATH, "\\");
	strcat_s(szDllPath1, MAX_PATH, szDll1);

	szExePath1 = GetCurrentDir();
	strcat_s(szExePath1, MAX_PATH, "\\");
	strcat_s(szExePath1, MAX_PATH, szEXE1);


	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;

	if (CreateProcess(argv[0], argv[1], NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo)) {
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}

	if (InjectDll(processInfo.dwProcessId, szDllPath1))
	{
		done = true;
	}

	if (!done) {
		std::cout << " > Injection failed!" << std::endl;
	}
	system("pause");
	return 0;
}