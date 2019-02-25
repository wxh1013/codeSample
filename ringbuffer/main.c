#include "ringbuffer.h"
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <errno.h>

static CircularBuffer *buffer;
void* write_data(void *arg)
{
	char data[20];
	int count = 0;
	memset(data,0x00,20);
	FILE *fp = NULL;
	fp = fopen("data_gps.bin","rb+");
	if(fp == NULL)
	{
		printf(" fopen data_gps.bin is failed!!\n");
	}
	else
	{
		printf(" fopen data_gps.bin fp:%x!!\n",fp);
		while (!feof(fp)){
        	count = fread(data, sizeof (char), 20, fp);
			CircularBufferWrite(buffer, data, count);
        	int n = feof (fp);
        	printf ("\n%d,%d\n", count, n);
        	printf ("\n%s\n",strerror (errno));
			usleep(1000);//50ms
    	}
		
	}
	
	return NULL;
}

void* read_data(void *arg)
{
	char data[20];
	int size = 0;
	int i = 0;
	while(1)
	{
		size = CircularBufferRead(buffer, data, 20);
		if(size != 0)
		{
			printf("read data:\n");
             for( i =0 ;i < size; i++)
             {
             	printf("0x%x ",data[i]);

				if(((i+1)%10) == 0) printf("\n");
             }


			 printf("\n");
			
		}
		usleep(50*1000);//50ms
	}	
	return NULL;
}


void myCreateThread(void *fun, const char *name)
{
	pthread_attr_t attr;
	pthread_t mThreadId;

	pthread_attr_init(&attr);

	int stackSize = 0;
	int error = -1;
	
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

	error = pthread_create(&mThreadId, &attr, fun, NULL);

	if(error != 0x00)
	{
		printf("create thread error !!!");
	}


	error = pthread_attr_setstacksize(&attr,64*1024*8);//512 size
	{
		if(0 != error)
		{
			printf("set stack error!");
		}
		else
		{
			error = pthread_attr_getstacksize(&attr,&stackSize);
			if(error == 0)
			{
				printf("stack is %d\n",stackSize);
			}
		}
	}


	pthread_setname_np(mThreadId, name);

}
int main()
{
	//CircularBuffer *buffer;
	CircularBufferCreate(1024,&buffer);

	myCreateThread(write_data, "write_data");
	myCreateThread(read_data, "read_data");

	pause();

	
}