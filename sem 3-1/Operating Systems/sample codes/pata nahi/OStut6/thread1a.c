#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<stdio.h>

int fact=0;

int factorial(int n)
{
	if (n == 0)
		return 1;
	else
		return(n * factorial(n-1));
}

void * func(void * ptr)
{
	int val=*(int *)ptr;
	int result=factorial(val);
	fact=result;
	pthread_exit((void *)(&fact));
}

int main()
{
	int res;
	pthread_t a_thread;
	void *thread_result;

	int num;
	scanf("%d",&num);

	int inputNumber=num;
	int * param=&inputNumber;

	res = pthread_create(&a_thread, NULL,func, (void *)param);

	if (res != 0) 
	{
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}

//	printf("Waiting for thread to finish...\n");
	res = pthread_join(a_thread, &thread_result);

	if (res != 0) 
	{
		perror("Thread join failed");
		exit(EXIT_FAILURE);
	}

	printf("Result %d = ",fact);
//	printf("Thread joined, it returned %d\n", *(int *)thread_result);
//	printf("Result %d = \n", *(int *)thread_result);

	exit(EXIT_SUCCESS);

	return 0;
}

