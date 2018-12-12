#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <cmath>

using namespace std;

// prototype for insertion sort
void insertion_sort(int);

// prototypes for heap sort
void heap_sort(int);
void maxheapify(int[], int, int, int&);
int buildmax_heap(int[], int, int&);
int left(int i);
int right(int i);

// prototypes for quick sort
void call_quicksort(int);
void randquicksort(int [], int, int, int&);
int randpart(int [], int, int, int&);
int partition(int [], int, int, int&);


// prototypes for merge sort
void merge_sort(int);
void merge_srt(int [], int , int, int &);
void merge(int [], int, int, int, int &);

int main (void)
{
    int input_sizes[100];

    // seed random number generator with time
    srand(time(NULL));

    //generate 100 random input sizes from 32 to 10000[exclusive] 
    for (int i = 0; i < 100; i++)
        input_sizes[i] = rand() % 10000 + 30;
    
    // call the algorithms for each of 100 random input sizes generated
    for (int i = 0; i < 100; i++)
    {
        //insertion_sort(input_sizes[i]);
        //merge_sort(input_sizes[i]);
        //heap_sort(input_sizes[i]);
        call_quicksort(input_sizes[i]);
    }

    return 0;
}

/*****************************************************************/
/*                       Insertion Sort                          */
/*****************************************************************/

// function to implement insertion sort
void insertion_sort(int n)
{
    srand(time(NULL));
    
    int input[n];
    int comparisons = 0;
    
    // generate n random numbers and use them as input
    for (int i = 0; i < n; i++)
        input[i] = rand() % 10000 + 30;
    
    for(int i = 1; i < n; i++)
    {
        int sen = input[i];
        int j = i - 1;
        while (j >= 0 && input[j] > sen)
        {
            comparisons++;
            input[j + 1] = input[j];
            j--;
        }
        input[j + 1] = sen;
    }

    // write csv
    ofstream file;
    file.open("insertion_sort.csv", fstream::app);
    file << n << "," << comparisons << "\n";
    file.close();
}

/*****************************************************************/
/*                         Merge Sort                            */
/*****************************************************************/

void merge_sort(int n)
{
    srand(time(NULL));
    
    int input[n];
    int comparisons = 0;
    
    // generate n random numbers and use them as input
    for (int i = 0; i < n; i++)
        input[i] = rand() % 10000 + 30;
    
    // call merge sort
    merge_srt(input, 0, n - 1, comparisons);

    // debugging stuff
    // for (int i = 0; i < n; i++)
    //     cout << input[i] << " ";

    // write csv
    ofstream file;
    file.open("merge_sort.csv", fstream::app);
    file << n << "," << comparisons << "\n";
    file.close();
}

void merge_srt(int ar[], int start, int end, int &comparisons)
{
    if (start < end)
    {
        comparisons++;
        int mid = (start + end) / 2;
        merge_srt(ar, start, mid, comparisons);
        merge_srt(ar, mid + 1, end, comparisons);
        merge(ar, start, mid, end, comparisons);
    }
}

void merge(int ar[], int start, int mid, int end, int &comparisons)
{
    int n1 = mid - start + 1;
    int n2 = end - mid;

    int a1[n1], a2[n2];

    for (int i = 0; i < n1; i++)
        a1[i] = ar[start + i];
    
    for (int j = 0; j < n2; j++)
        a2[j] = ar[mid + j + 1];

    int i = 0; 
    int j = 0; 
    int k = start;

    while (i < n1 && j < n2)
    {
        comparisons = comparisons + 2;
        if (a1[i] <= a2[j])
        {
            comparisons++;
            ar[k] = a1[i];
            i++;
        }
        else
        {
            comparisons++;
            ar[k] = a2[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        comparisons++;
        ar[k] = a1[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        comparisons++;
        ar[k] = a2[j];
        j++;
        k++;
    }
}

/**********************************************************/
/*                  HEAP SORT                             */
/**********************************************************/
int left(int i)
{
    return 2 * i;
}

int right(int i)
{
    return (2 * i) + 1;
}

void maxheapify(int ar[], int i, int heap_size, int &comparison)
{
    int largest = i;

    int l = left(i);
    int r = right(i);

    if (l < heap_size && ar[l] > ar[i])
    {
        comparison = comparison + 2;
        largest = l;
    }
    else
    {
        comparison = comparison + 2;
        largest = i;
    }
    
    if (r < heap_size && ar[r] > ar[largest])
    {
        comparison = comparison + 2;
        largest = r;
    }

    if (largest != i)
    {
        swap(ar[i], ar[largest]);
        maxheapify(ar, largest, heap_size, comparison);
    }
}

int buildmax_heap(int ar[], int n, int &comparison)
{
    int heap_size = n;
    for (int i = (n / 2) - 1; i >= 0; i--)
        maxheapify(ar, i, n, comparison);
    
    return heap_size;
}

void heap_sort(int n)
{
    srand(time(NULL));
    int arr[n];
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 10000 + 30;

    int comparison = 0;
    int heap_size = buildmax_heap(arr, n, comparison);
    
    for(int i = n - 1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        heap_size--;
        maxheapify(arr, 0, i, comparison);
    }

    // write csv
    ofstream file;
    file.open("heap_sort.csv", fstream::app);
    file << n << "," << comparison << "\n";
    file.close();
}

/**********************************************************/
/*                  Quick SORT                            */
/**********************************************************/

void call_quicksort(int n)
{
    int arr[n];
    int comparisons = 0;
    for(int i = 0; i < n; i++)
        arr[i] = rand() % 10000 + 30;

    //int arr[] = {5, 4, 2, 3, 1, 2, 4, 3, 4, 5};

    randquicksort(arr, 0, n - 1, comparisons);

    //debugging stuff
    // for (int i = 0; i < n; i++)
    //     cout << arr[i] << " ";
    
    // write csv
    ofstream file;
    file.open("quick_sort.csv", fstream::app);
    file << n << "," << comparisons << "\n";
    file.close();
}

void randquicksort(int arr[], int start, int end, int &comparison)
{
    if (start < end)
    {
        comparison++;
        int q  = randpart(arr, start, end, comparison);
        randquicksort(arr, start, q - 1, comparison);
        randquicksort(arr, q + 1, end, comparison);
    }
}

int randpart(int arr[], int start, int end, int &comparison)
{
    int i = (rand() % (end - start + 1)) + start;
    swap(arr[i], arr[end]);
    return partition(arr, start, end, comparison);
}

int partition(int arr[], int start, int end, int &comparison)
{
    int pivot = arr[end];
    int i = start - 1;
    for (int j = start; j < end; j++)
    {
        if(arr[j] <= pivot)
        {
            comparison++;
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[end]);

    return i + 1;
}