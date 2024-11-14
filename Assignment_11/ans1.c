#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>

struct input {
	int start;
	int end;
	int sum;
};

void* cal_sum(void *param)
{
	struct input* ip = (struct input *)param;
	
	int sum = 0;

	for(int i=ip->start;i<=ip->end;i++)
	{
		sum += i;
	}

	ip->sum = sum;
	pthread_exit(NULL);

}

int main()
{
	int start,end,num_threads;

	printf("enter start: ");
	scanf("%d",&start);
	printf("enter end: ");
	scanf("%d",&end);

	num_threads=2;

	pthread_t th1[num_threads];
	struct input th2[num_threads];

	int range_per_thread = (end-start+1)/num_threads;

	for(int i=0;i<num_threads;i++)
	{
		th2[i].start = start+i*range_per_thread;
		th2[i].end = (i == num_threads -1)?end:(start+(i+1)*range_per_thread-1);

		pthread_create(&th1[i],NULL,cal_sum,&th2[i]);
	}

	int total_sum=0;

	for(int i=0;i<num_threads;i++)
	{
		pthread_join(th1[i],NULL);
		total_sum += th2[i].sum;
	}

	printf("final sum = %d\n",total_sum);

	return 0;
}
