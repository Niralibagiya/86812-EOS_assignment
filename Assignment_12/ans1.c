#include <stdio.h>
#include <pthread.h>

#define SIZE 10

void selection_sort(int arr[], int size) 
{
    for (int i = 0; i < size - 1; i++) 
	{
        int min_index = i;
        for (int j = i + 1; j < size; j++) 
		{
            if (arr[j] < arr[min_index]) 
			{
                min_index = j;
            }
        }
        int temp = arr[min_index];
        arr[min_index] = arr[i];
        arr[i] = temp;
    }
}

typedef struct {
    int* arr;
    int size;
} ThreadData;

void* sort_array(void* arg) 
{
    ThreadData* data = (ThreadData*)arg;
    selection_sort(data->arr, data->size);

	return NULL;
}

int main() 
{
    int arr[SIZE] = {64, 25, 12, 22, 11, 90, 45, 33, 78, 10};
    
    printf("Original array: ");
    for (int i = 0; i < SIZE; i++) 
	{
        printf("%d ", arr[i]);
    }
    printf("\n");

    pthread_t sort_thread;
    ThreadData data = {arr, SIZE};

    pthread_create(&sort_thread, NULL, sort_array, (void*)&data);
    pthread_join(sort_thread, NULL);

    printf("Sorted array: ");
    for (int i = 0; i < SIZE; i++) 
	{
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
