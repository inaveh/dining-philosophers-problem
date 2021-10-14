#include <iostream>
#include <Windows.h>
#include<time.h>

using namespace std;

#define NUM_PROCESSES 5
#define MAX 1000000
#define EXE_FILENAME "D:\\cyber\\bootcamp\\os\\processesAndThreads\\philosopher\\mutex\\SinglePhilosopher\\SinglePhilosopher\\Debug\\SinglePhilosopher.exe"

int main()
{
	cout << "Mutex " << endl;

	//save the start time
	clock_t time;
	time = clock();

	INT size = strlen(EXE_FILENAME) + 3;
	PCHAR param = (PCHAR)malloc(size * sizeof(CHAR));
	STARTUPINFOA si;
	PROCESS_INFORMATION pi[NUM_PROCESSES];
	for (int i = 0; i < NUM_PROCESSES; i++) {
		sprintf_s(param, size, "%s %d", EXE_FILENAME, i);
		cout << i << endl;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi[i], sizeof(pi[i]));
		CreateProcessA(
			NULL,
			param,
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&si,
			&pi[i]);
	}

	for (int i = 0; i < NUM_PROCESSES; i++) {
		WaitForSingleObject(pi[i].hProcess, INFINITE);
	}
	for (int i = 0; i < NUM_PROCESSES; i++)
	{
		CloseHandle(pi[i].hProcess);
		CloseHandle(pi[i].hThread);
	}
	time = clock() - time;
	cout << "The total time of running: " << time << " millisecond" << endl;
	return 0;
}
