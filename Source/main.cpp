#include"Initializer.h"

int main()
{
	Initializer *init = new Initializer();

	init->IsOnlyInstance(TEXT("CoconutEngine-x64-Release"));
	init->CheckStorage(300 * MB);
	init->CheckMemory(0, 0);
	init->ReadCpuSpeed();
	init->ReadCpuArchitecture();
	system("pause");
	return 0;
}