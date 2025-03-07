#include <stdio.h>

void mergeArrays(int arr1[], int arr2[], int arr3[], int size1, int size2) 
{
    int i=0;
    int j=0;
    int k=0;
    for (int i = 0; i < size1; i++)
    {
        arr3[k] = arr1[i];
        k++;
    }
    for (int j = 0; j < size2; j++)
    {
        arr3[k] = arr2[j];
        k++;
    }   
}

void main()
{
    int arr1[]={1, 2, 8, 20, 30, 80};
    int arr2[]={3, 5, 6, 9, 12};

    int size1=sizeof(arr1)/sizeof(arr1[0]);
    int size2=sizeof(arr2)/sizeof(arr2[0]);

    int arr3[size1+size2];
    mergeArrays(arr1,arr2,arr3,size1,size2);

    for(int i=0;i<size1+size2;i++)
    {
        printf("%d ",arr3[i]);
    }
}