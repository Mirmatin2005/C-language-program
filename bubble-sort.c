#include <stdio.h>

int main()
{
    int array[] = {18, 23, 17, 98};
    int size = sizeof(array) / sizeof(array[0]);
    for (int i = size; i > 0; i--)
    {
        for(int j = 0; j < size - 1; j++)
        {
            if(array[j] < array[j+1])
            {
                int z = array[j]; //z : zakhire
                array[j] = array[j+1];
                array[j+1] = z;
            }
        }
    }
    for(int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
}