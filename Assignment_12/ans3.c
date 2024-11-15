#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t m;
pthread_cond_t c;
int sun_flag = 0; 

void* sunbeam(void* param)
{
    while (1)
	{
		char *str = "SUNBEAM\n";
        pthread_mutex_lock(&m);
        while (sun_flag != 0)
		{ 
            pthread_cond_wait(&c, &m);
        }
	   for(int i=0;str[i]!='\0';i++)
	   {
			write(1,&str[i],1);
			sleep(1);
	   }
        sun_flag = 1; 
        pthread_cond_signal(&c);
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

void* infotech(void* param) 
{
    while (1) 
	{
		char *str = "INFOTECH\n";
        pthread_mutex_lock(&m);
        while (sun_flag != 1) 
		{
            pthread_cond_wait(&c, &m);
        }
		for(int i=0;str[i]!='\0';i++)
		{
			write(1,&str[i],1);
			sleep(1);
		}
        sun_flag = 0;
        pthread_cond_signal(&c); 
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

int main() 
{
    pthread_t th1, th2;

    pthread_mutex_init(&m, NULL);
    pthread_cond_init(&c, NULL);

    
    pthread_create(&th1, NULL, sunbeam, NULL);
    pthread_create(&th2, NULL, infotech, NULL);

    
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    
    pthread_mutex_destroy(&m);
    pthread_cond_destroy(&c);

    return 0;
}

