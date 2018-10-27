#define RANGE  255
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

      for (i = 0; i < n-1; i++)
    {
               min_idx = i;
        for (j = i+1; j < n; j++)
          if (arr[j] < arr[min_idx])
            min_idx = j;

               swap(&arr[min_idx], &arr[i]);
    }
}

// A function to implement bubble sort
void bubbleSort(int arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)

             for (j = 0; j < n-i-1; j++)
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}

void insertionSort(int arr[], int n)
{
   int i, key, j;
   for (i = 1; i < n; i++)
   {
       key = arr[i];
j = i-1;

     
       while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;

       int L[n1], R[n2];

       for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

      i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
   while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
       
        int m = l+(r-l)/2;

               mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);

        merge(arr, l, m, r);
    }
}

int partition (int arr[], int low, int high){
    int pivot = arr[high];    // pivot

   int j,i = (low - 1);  // Index of smaller element

    for (j = low; j <= high- 1; j++)
    {
               if (arr[j] <= pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
              int pi = partition(arr, low, high);

               quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void countSort(char arr[])
{
       char output[strlen(arr)];

       int count[RANGE + 1], i;
    memset(count, 0, sizeof(count));

       for(i = 0; arr[i]; ++i)
        ++count[arr[i]];

      for (i = 1; i <= RANGE; ++i)
        count[i] += count[i-1];

       for (i = 0; arr[i]; ++i)
    {
        output[count[arr[i]]-1] = arr[i];
        --count[arr[i]];
    }

   
    for (i = 0; arr[i]; ++i)
        arr[i] = output[i];
}


int sort_main()
{
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr)/sizeof(arr[0]);
int arr_size = sizeof(arr)/sizeof(arr[0]);

selectionSort(arr, n);
    printf("Sorted array using selection sort: \n");
    printArray(arr, n);


bubbleSort(arr, n);
    printf("Sorted array using bubble sort: \n");
    printArray(arr, n);

    insertionSort(arr, n);
    printf("Sorted array using insertion sort: \n");
    printArray(arr, n);

mergeSort(arr, 0, arr_size - 1);

    printf("\nSorted array using merge sort is: \n");
    printArray(arr, arr_size);

 quickSort(arr, 0, n-1);
    printf("Sorted array using quick sort: \n");
    printArray(arr, n);
    

return 0;
}
