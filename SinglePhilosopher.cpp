#include <Windows.h>
#include <iostream>

using namespace std;

#define MAX 1000000
int val[5] = { 0 };

int main(int argc, char* argv[])
{
	if (argc != 2) {
		printf("Incorrect number of arguments\n");
		return 0;
	}

	int max = MAX;
	int id = atoi(argv[1]);

	string left = "stick" + string(argv[1]);
	string right = "stick" + id + 1;

	if (id == 4)
		right = "stick" + 0;

	HANDLE hMutex1 = CreateMutexA(NULL, FALSE, left.c_str());
	HANDLE hMutex2 = CreateMutexA(NULL, FALSE, right.c_str());

	while (true) {
		WaitForSingleObject(hMutex1, INFINITE);
		DWORD waitResult = WaitForSingleObject(hMutex2, 0);
		if (waitResult == WAIT_OBJECT_0)
		{
			if (max == 0) {
				break;
			}
			max--;
			val[id] ++;
			ReleaseMutex(hMutex1);
			ReleaseMutex(hMutex2);
		}
		else
			ReleaseMutex(hMutex1);
	}
	CloseHandle(hMutex1);
	CloseHandle(hMutex2);

	for (int i = 0; i < 5; i++) {
		if (val[i] != 0)
			cout << "Philhosof " << i << " was eaten " << val[i] << endl;
	}

	return 0;
}
