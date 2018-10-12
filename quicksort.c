//This is quicksort implementation
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int*b) {
        int temp = *a;
        *a = *b;
        *b = temp;
}

int partition(int a[], int low, int high) {

        int i, j, pivot;

        pivot = a[low];
        i = low +1;
        j = high;

        while (i < j) {
                while (pivot > a[i])
                        i++;
                while (pivot < a[j])
                        j--;
                if (i<j)
                        swap(&a[i], &a[j]);
        }
        swap(&a[low],&a[j]);
        return j;
}

int quicksort(int a[], int low, int high) {
        int j =0 ;

        if (low < high) {
                j = partition(a, low, high);
                quicksort(a, low, j-1);
                quicksort(a, j+1, high);
        }
}

main() {

        int a[] = {10, 2, 45, 32, 6, 99, 8, 34, 99, 67, 25, 77};
        int n = 12, i ;
        printf(" ARRAY BEFORE SORTING : \n");

        for (i =0; i<n; i++)
                printf("%d ", a[i]);
        quicksort(a, 0, n-1);
        printf("\n ARRAY AFTER SORTING : \n");
        for (i =0; i<n; i++)
                printf("%d ", a[i]);
}
