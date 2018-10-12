//bubble sort
#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
}

main() {

        int a[] = { 20, 4, 10, 4, 6, 18, 9, 1};
        int n = 8, i, j, is_swap;

        printf(" Array before sorting: \n ");
        for (i=0; i<n; i++)
                printf("%d  ", a[i]);
        for ( i = 0; i < n ; i++) {
                for (j=0; j<n-i-1; j++) {
                is_swap = 0;
                        if (a[j] > a[j+1]) {
                                swap(&a[j], &a[j+1]);
                                is_swap = 1;
                        }
                }
                if (!is_swap) {
                        printf("Already sort. No swap is required. exit");
                        break;
                }
        }

        printf(" Array after sorting: \n ");
        for (i=0; i<n; i++)
                printf("%d  ", a[i]);

}
