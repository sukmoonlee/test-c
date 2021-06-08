#include <stdio.h>
#include <stdlib.h>

char *GlobalString="abcde";

int test(void)
{
	char buffer2[32];
	char *localString2="1234567890";

	printf("%015p buffer2        Stack        %s() %s:%d\n", buffer2, __FUNCTION__, __FILE__, __LINE__);
	printf("%015p localString2   Literals     %s() %s:%d (%s)\n", localString2, __FUNCTION__, __FILE__, __LINE__, localString2);
	printf("%015p &localString2  Stack        %s() %s:%d\n", &localString2, __FUNCTION__, __FILE__, __LINE__);
}

int main(void) {
	char buffer1[32];
	char *localString1="1234567890";
	int (*FuncPtr)();
	char *newbuffer;

	printf("%015p GlobalString   Literals     %s() %s:%d (%s)\n", GlobalString, __FUNCTION__, __FILE__, __LINE__, GlobalString);
	printf("%015p &GlobalString  StaticData   %s() %s:%d\n", &GlobalString, __FUNCTION__, __FILE__, __LINE__);
	printf("%015p buffer1        Stack        %s() %s:%d\n", buffer1, __FUNCTION__, __FILE__, __LINE__);
	printf("%015p localString1   Literals     %s() %s:%d (%s)\n", localString1, __FUNCTION__, __FILE__, __LINE__, localString1);

	FuncPtr=main;
	printf("%015p main()         Instructions %s() %s:%d\n", FuncPtr, __FUNCTION__, __FILE__, __LINE__);
	FuncPtr=test;
	printf("%015p test()         Instructions %s() %s:%d\n", FuncPtr, __FUNCTION__, __FILE__, __LINE__);

	newbuffer=malloc(1024);
	printf("%015p newbuffer      Heap         %s() %s:%d\n", newbuffer, __FUNCTION__, __FILE__, __LINE__);

	FuncPtr();
	return 0;
}
