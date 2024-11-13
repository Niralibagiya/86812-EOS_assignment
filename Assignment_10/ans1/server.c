#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
	int result,fd,num1,num2;
	
	//read from file
	fd = open("/tmp/input",O_RDONLY);
	if(fd<0)
	{
		perror("open() failed");
		_exit(1);
	}

	//read or take num1 num2 value from client
	printf("Receive two number from client: ");
	read(fd,&num1,sizeof(int));
	read(fd,&num2,sizeof(int));
	printf("num1=%d  num2=%d\n",num1,num2);
	close(fd);

	//calculate
	result = num1+num2;

	//open file for write
	fd = open("/tmp/input",O_WRONLY);
	if(fd<0)
	{
		perror("open() failed");
		_exit(1);
	}
	
	//write result into result file
	write(fd,&result,sizeof(int));
	close(fd);
return 0;
}
