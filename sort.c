#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implements heap sort
// extraMemoryAllocated counts bytes of memory allocated
void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void heapify(int arr[], int n, int i)
{
    
    int largest = i;
    int l= 2 * i + 1;
    int r= 2 * i + 2;

    if (l< n && arr[l] > arr[largest]) {
		largest = l;
	}
       

    if (r< n && arr[r] > arr[largest]) {
		largest = r;
	}  

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void merge(int pData[], int l, int m, int r) {

	int l1 = m - l + 1;
	int leftarray[l1];

	int r1 = r - m;
	int rightarray[r1];

	for (int i = 0; i < l1; i++) {
		leftarray[i] = pData[l+i];
	}

	for (int i = 0; i < r1; i++) {
		rightarray[i] = pData[m + 1 + i];
	}

	int i = 0, j = 0, k = l;

	while (i < l1 && j < r1) {
		if (leftarray[i] <= rightarray[i]) {
			pData[k] = leftarray[i];
			i++;
		} else {
			pData[k] = rightarray[j];
			j++;
		}

		k++;
	}

	while (i < l1) {
        pData[k] = leftarray[i];
        i++;
        k++;
    }
 
    while (j < r1) {
        pData[k] = rightarray[j];
        j++;
        k++;
    }



}

void mergeSort(int pData[], int l, int r)
{

	if (l < r) {
		int m = l + (r - l) / 2;
		mergeSort(pData, l, m);
		mergeSort(pData, m + 1, r);
		
		merge(pData, l, m, r);
	}

}

// parses input file to an integer array
int parseData(char *inputFilename, int **ppData)
{
	FILE* inFile = fopen(inputFilename,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* filenames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(filenames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}