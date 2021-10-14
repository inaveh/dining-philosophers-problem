#include <iostream>
#include <Windows.h>
#include <time.h>

#define NUM_OF_THREADS 5
#define MAX 1000000

using namespace std;

BOOL inc(PINT param);
DWORD WINAPI eat_counter(LPVOID param);

CRITICAL_SECTION cs[5];
INT val[5] = { 0 };

int main()
{	
	cout << "Critical Section " << endl;
	clock_t time;
	time = clock();

	for (int i = 0; i < NUM_OF_THREADS; i++)
		InitializeCriticalSection(&cs[i]);
	INT id[5] = { 0,1,2,3,4 };
	LPVOID thread_id[5] = { &id[0],&id[1],&id[2],&id[3],&id[4] };

	HANDLE hThread[NUM_OF_THREADS];

	for (int i = 0; i < NUM_OF_THREADS; i++)
	{
		hThread[i] = CreateThread(
			NULL,
			0,
			eat_counter,
			thread_id[i],
			0,
			NULL
		);
	}
	WaitForMultipleObjects(NUM_OF_THREADS, hThread,TRUE,INFINITE);

	for (int i = 0; i < NUM_OF_THREADS; i++)
		DeleteCriticalSection(&cs[i]);
	for (int i = 0; i < NUM_OF_THREADS; cout << "Philhosof "<<i<< " was eaten " << val[i] << " times.\n", i++);
	time = clock() - time;
	cout << "The total time of running: " << time << " millisecond" << endl;

	return 1;
	system("pause");
}

BOOL inc(PINT param) {
	EnterCriticalSection(&cs[*(PINT)param]);
	BOOL success = 0;
	int help = 0;
	if (*(PINT)param != (INT)4) {
		help = *(PINT)param + 1;
		success = TryEnterCriticalSection(&cs[*(PINT)param + 1]);
	}
	else
		success = TryEnterCriticalSection(&cs[0]);

	if (success) {
		val[*(PINT)param] += 1;
		LeaveCriticalSection(&cs[help]);
		LeaveCriticalSection(&cs[*(PINT)param]);
		return 1;
	}
	else
	{
		LeaveCriticalSection(&cs[*(PINT)param]);
		return 0;
	}
}

DWORD WINAPI eat_counter(LPVOID param) {
	for (int i = 0; i < MAX; i++)
	{
		if (!inc((PINT)param))
			i--;
		if (i + 1 == MAX)
			cout << *(PINT)param << '\n';
	}
	return 1;
}