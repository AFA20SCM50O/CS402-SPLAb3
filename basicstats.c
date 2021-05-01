/* For this lab, you will implement a program that reads data from a file and
computes some basic statistical analysis measures for the data.
The program should work without any changes for data sets of any size, i.e. it 
would work for 10 data values or for 10 million without re-compilation.


Alexis D Ortega
4/28/2021
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


// read file into Database
float * writeIntoDB(char* datafile, int* xp, int* yp);

// print Database        
void printDB (float arr[], int size, int total_size);

// helper method for sort
void swapHelper(float* xp, float* yp);
  
// sort
void sort(float arr[], int n);

// find findMedian
float findMedian(float arr[], int size);

// find findMean
double findMean(float arr[], int size);

//find Standard Deviation
double findStandardDeviation(float arr[], int size);

int main(int argc, char *argv[])
{
    if ( argc != 2 ) 
    {
        
        printf( "usage: %s filename\n", argv[0] );
    }
    else
    {   
        int count = 0;
        int size = 20;
        float* set;

        set = writeIntoDB(argv[1], &count, &size); 
        sort(set, count); 
        printDB(set, count, size);      
    }
}

// make DB from file
float * writeIntoDB(char* datafile, int* count, int* size)
{
    int n = 20;
      
    float* set = (float*)malloc(n * sizeof(float)); 
    
    //check if mem allocated correctly 
    if (set == NULL) { 
        printf("Memory not allocated.\n"); 
        exit(0); 
    } 
    
    //read from file
    int counter = 0;
    float data = 0;
    FILE *file;
    file = fopen(datafile, "r"); //read opened file

    char maxSize[100];   //set size
    while (fgets(maxSize, sizeof(maxSize), file))  
    {
        data = strtof(maxSize, NULL);
        set[counter] = data;
        counter++; 
        

        if (counter == n)
        {
            
            n = n*2;
            float* temp = (float*)malloc(n * sizeof(float)); 

            //check if mem allocated correctly
            if (temp == NULL) { 
                printf("Memory not allocated.\n"); 
                exit(0); 
            }


            memcpy(temp, set, n * sizeof(float));
            free(set);
            set = (float*)malloc(n * sizeof(float)); 
            memcpy(set, temp, n * sizeof(float));
            free(temp);
        }
    }
    if (feof(file)) // End Of File
    {
        fclose(file);
    } 
    *size = n;
    *count = counter;
    return set;
}

// print DB        
void printDB (float arr[], int n, int total_size)
{
    printf("\nResults:\n");
    printf("-----------\n");
    printf("Num Values:\t\t%d\n", n);
    printf("mean\t\t\t%lf\n", findMean(arr, n));
    printf("median:\t\t\t%f\n", findMedian(arr, n));
    printf("stddev:\t\t\t%lf\n", findStandardDeviation(arr, n));
    printf("Unused array capacity:\t%d\n\n", (total_size-n));
}

// swap helper for sort
void swapHelper(float* xp, float* yp) 
{ 
    float temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
  
// sort DB
void sort(float arr[], int n) 
{ 
    int i, j, min; 
         
    for (i = 0; i < n - 1; i++) { 
        min = i; 
        for (j = i + 1; j < n; j++) 
            if (arr[j] < arr[min]) 
                min = j; 
                swapHelper(&arr[min], &arr[i]); 
    } 
} 

//find median
float findMedian(float arr[], int size)
{
    float findMedian = 0;
    if(size % 2 == 0)
    {
        findMedian = (arr[(size-1)/2] + arr[size/2])/2.0;
    }
    else
    {
        findMedian = arr[size/2];
    }
    return findMedian;
}
//find mean
double findMean(float arr[], int size)
{
    int counter;
    float sum;
    double average;

    sum = average = 0;
   
    for(counter = 0; counter < size; counter++) 
    {
      sum = sum + arr[counter];
    }
   
    average = (double)sum / size;
    return average;
}

//find Standard Deviation
double findStandardDeviation(float arr[], int size)
{
    int counter;
    float sum;
    double average, findStandardDeviation;

    average = findMean(arr, size); 
   
    for(counter = 0; counter < size; counter++) 
    {
      sum = sum + ((arr[counter] - average) * (arr[counter] - average));
    }
   
    findStandardDeviation = (double) sqrt(sum / size);
    return findStandardDeviation;

}
