#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct array {
    int *arr;
    int size;
};


void bubble_sort(int arr[], int size) 
{
    for (int i = 0; i < size - 1; i++) 
	{
        for (int j = 0; j < size - i - 1; j++) 
		{
            if (arr[j] > arr[j + 1]) 
			{
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void* sort_array(void* arg) 
{
    struct array* data = (struct array*)arg;
    bubble_sort(data->arr, data->size);

	return NULL;
}

int main() 
{
    int n;
    printf("Enter the number of integers: ");
    scanf("%d", &n);


    int *arr = (int*)malloc(n * sizeof(int));

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++) 
	{
        scanf("%d", &arr[i]);
    }

    printf("Original array: ");
    for (int i = 0; i < n; i++) 
	{
        printf("%d ", arr[i]);
    }
    printf("\n");

    
    pthread_t sort_thread;
    struct array data = {arr, n};

  
    pthread_create(&sort_thread, NULL, sort_array, (void*)&data);
    

    pthread_join(sort_thread, NULL);


    printf("Sorted array: ");
    for (int i = 0; i < n; i++) 
	{
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);

    return 0;
}
