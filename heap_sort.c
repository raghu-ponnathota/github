//heap-sort implementation.

#include <stdio.h>
#include <stdlib.h>




void swap(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
}


void heapify(int a[], int n, int index) {

        int i, li, ri; //root index, left index, right index.
        i = index;

        li = 2*i +1;
        ri = 2*i+2;
        printf ("\n -- index %d left %d right %d", index, li, ri);
        printf("\n -- a[index] %d a[left] %d a[right] %d", a[i], a[li], a[ri]);
        if(li < n && a[li] > a[i])
                i = li;
        if(ri<n && a[ri] > a[i])
                i = ri;
        printf(" \n i = %d index = %d ", i, index);
        if (i != index) {
                printf("\n SWAPPING a[%d] %d and a[%d]=%d", index, a[index], i, a[i]);
                swap(&a[index], &a[i]);
                printf("\nafter SWAPPING a[%d] %d and a[%d]=%d", index, a[index], i, a[i]);
                heapify(a, n, i);
        }
}


void heap_sort(int a[], int n) {
        int i;

        for (i=(n/2-1); i>=0; i--)
                heapify(a,n,i);
        printf("\n after heapify");
        for (i=0; i<n; i++)
                printf("%d ",a[i]);
        for (i=n-1; i > 0; i--) {
                swap(&a[0], &a[i]);
                heapify(a,i, 0); // make sure i is passed here.
        }
}

int main() {
        int a[10] = { 26,6,13,45, 97,12,36,99,2,19};
        int n = 10;//array size
        int i =0;

        //print array
        printf("Array before sorting \n");
        for (i=0; i<n; i++)
                printf("%d ",a[i]);

        heap_sort(a,n);

        printf("\nArray after sorting \n");
        for (i=0; i<n; i++)
                printf("%d ",a[i]);

}
