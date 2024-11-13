#include<stdio.h>
#include<unistd.h>
#include <fcntl.h> 

int main()
{
	int fd,num1,num2,result;

	//input file open
	fd = open("/tmp/input",O_WRONLY);
	if(fd < 0)
	{
		perror("open() failed");
		_exit(1);
	}
	
	//take a input from client
	printf("Enter two number \n");
	printf("Enter 1st number: ");
	scanf("%d",&num1);
	printf("Enter 2nd number: ");
	scanf("%d",&num2);

	//write into file
	write(fd,&num1,sizeof(int));
	write(fd,&num2,sizeof(int));
	close(fd);

	//result file open 
	fd = open("/tmp/input",O_RDONLY);
	if(fd<0)
	{
		perror("open() failed");
		_exit(1);
	}

	//read result 
	read(fd,&result,sizeof(int));
	close(fd);
	
	printf("Result=%d\n",result);
return 0;
}
