#include "InjectionMethod.h"
#include <string>
using namespace std;

int main(int argc, TCHAR *argv[])
{
	bool done = false;

	STARTUPINFO info = { sizeof(info) };
	PROCESS_INFORMATION processInfo;


	wchar_t param1[300];
	mbstowcs(param1, (char*)argv[1], 299);
	LPWSTR param1lpwstr = param1;

	/*wchar_t param2[150];
	mbstowcs(param2, (char*)argv[2], 149);
	LPWSTR param2lpwstr = param2;*/

	if (CreateProcess(NULL, param1lpwstr, NULL, NULL, TRUE, 0, NULL, NULL, &info, &processInfo)) {
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
	}

	if (InjectDll(processInfo.dwProcessId, (char *)argv[2]))
	{
		done = true;
	}

	if (!done) { std::cout << " > Injection failed!" << std::endl; }
	system("pause");
	return 0;
}