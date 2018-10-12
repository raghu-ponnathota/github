//insertion sort
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
}

main() {

        int a[] = { 20, 4, 10, 4, 6, 18, 9, 1};
        int n = 8, i, j, item;

        printf(" Array before sorting: \n ");
        for (i=0; i<n; i++)
                printf("%d  ", a[i]);

        for (i=0 ;i<n; i++) {
                item = a[i];
                j = i-1;

                while (j>=0 && a[j] > item) {
                        a[j+1] = a[j];
                        j--;
                }
                a[j+1] = item;
        }


        printf(" Array after sorting: \n ");
        for (i=0; i<n; i++)
                printf("%d  ", a[i]);

}
