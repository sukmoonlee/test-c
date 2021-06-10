#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

char *GlobalString="abcde";
char *GlobalP;

void *test()
{
	char buffer2[32];
	char *localString2="1234567890";
	pthread_t pid = pthread_self();

	printf("(%x) %015p buffer2        Stack        %s() %s:%d\n", pid, buffer2, __FUNCTION__, __FILE__, __LINE__);
	printf("(%x) %015p localString2   Literals     %s() %s:%d (%s)\n", pid, localString2, __FUNCTION__, __FILE__, __LINE__, localString2);
	printf("(%x) %015p &localString2  Stack        %s() %s:%d\n", pid, &localString2, __FUNCTION__, __FILE__, __LINE__);
	printf("(%x) %015p GlobalP        Heap         %s() %s:%d\n", pid, GlobalP, __FUNCTION__, __FILE__, __LINE__);
	printf("(%x) %015p &GlobalP       StaticData   %s() %s:%d\n", pid, &GlobalP, __FUNCTION__, __FILE__, __LINE__);
}

int main(void) {
	char buffer1[32];
	char *localString1="1234567890";
	char *newbuffer;
	int status;
	pthread_t p_thread[2];

	printf("%015p GlobalString   Literals     %s() %s:%d (%s)\n", GlobalString, __FUNCTION__, __FILE__, __LINE__, GlobalString);
	printf("%015p &GlobalString  StaticData   %s() %s:%d\n", &GlobalString, __FUNCTION__, __FILE__, __LINE__);
	printf("%015p buffer1        Stack        %s() %s:%d\n", buffer1, __FUNCTION__, __FILE__, __LINE__);
	printf("%015p localString1   Literals     %s() %s:%d (%s)\n", localString1, __FUNCTION__, __FILE__, __LINE__, localString1);

	newbuffer=malloc(1024);
	printf("%015p newbuffer      Heap         %s() %s:%d\n", newbuffer, __FUNCTION__, __FILE__, __LINE__);
	GlobalP=malloc(1024);
	printf("%015p GlobalP        Heap         %s() %s:%d\n", GlobalP, __FUNCTION__, __FILE__, __LINE__);
	printf("%015p &GlobalP       StaticData   %s() %s:%d\n", &GlobalP, __FUNCTION__, __FILE__, __LINE__);

	pthread_create(&p_thread[0], NULL, test, NULL);
	pthread_create(&p_thread[1], NULL, test, NULL);

	pthread_join(p_thread[0], (void **)&status);
	pthread_join(p_thread[1], (void **)&status);

	return 0;
}
