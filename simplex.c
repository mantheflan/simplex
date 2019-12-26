#include <stdio.h>
//#include <errno.h>
//#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

//extern int errno;

int argmin(double arr[], int size, double lowerBound) {
    // Returns index of smallest (leftmost) element of arr which is bigger than lowerBound
    double m;
    int j = 0;
    int i;

    for ( i = 0; i < size; i++ ) {

        if ( arr[i] < lowerBound ) { j++; continue; }
        else { m = arr[i]; break; }

        fprintf(stderr, "Couldn't find a minimum with this lowerbound!\n");
        exit(EXIT_FAILURE);
    }

    for ( i = j+1; i < size; i++ ) {
        if ( arr[i] < m ) {
            m = arr[i];
            j = i;
        }
    }

    return j;
}

void printMat(int sizeL, int sizeC, double arr[sizeL][sizeC]) {
    int i, j;

    for ( i = 0; i < sizeL; i++ ) {
        for ( j = 0; j < sizeC; j++ ) {
            if ( arr[i][j] >= 0 ) { printf(" "); }
            printf("%f   ", arr[i][j]);
        }
        printf("\n");
    }
}

void gaussElim(int sizeL, int sizeC, double mat[sizeL][sizeC], int indL, int indC){
    double *q;
    int i;
    int j;
    double w;

    if (!( 0 <= indL < sizeL )) {
        fprintf(stderr, "Line number not in range!\n");
        exit(EXIT_FAILURE);
    }
    if ( indC < 0 || indC >= sizeC ) {
        fprintf(stderr, "Column number not in range!\n");
        exit(EXIT_FAILURE);
    }

    double pivot = mat[indL][indC];
    if ( pivot == 0 ) {
        fprintf(stderr, "Pivot is 0!\n");
        exit(EXIT_FAILURE);
    }

    for ( j = 0; j < sizeC; j++ ){
        mat[indL][j] = mat[indL][j] / pivot;
    }

    for ( i = 0; i < sizeL; i++ ){
        if ( mat[i][indC] == 0 || i == indL ) { continue; }

        w = mat[i][indC];

        for ( j = 0; j < sizeC; j++ ){
            mat[i][j] = mat[i][j] - w * mat[indL][j];
        }
    }
}

int main() {
    int n = 3;
    int p = 5;
    int i;
    int j;

    // to remove
    int k=1;
    double A[n][p];
    for ( i = 0; i < n; i++ ) {
        for ( j = 0; j < p; j++ ) {
            A[i][j] = k;
            k++;
        }
    }
    A[2][0] = -11;
    A[2][1] = -12;
    A[2][2] = 0;
    A[2][3] = 0;
    A[2][4] = 0;

    printf("Initial tableau:\n");
    printMat(n, p, A);

    double z[p];
    for ( j = 0; j < p; j++ ) {
        z[j] = A[n-1][j];
    }

    printf("test: %d\n", 0 >= 0.0);
    printf("test: %d\n", argmin(z, p, -1));

    double theta[n-1];
    int exiting;
    int entering;
    int iteration = 0;

    while ( true ) { // Hopefully it always terminates!
        iteration++;

        printf("\niteration no. %d\n", iteration);

        printf("z-row: ");
        for ( j = 0; j < p; j++ ) {
            z[j] = A[n-1][j];
            printf("%f  ", z[j]);
        }
        printf("\n");

        entering = argmin(z, p, -INFINITY);

        if ( z[entering] >= 0 || iteration == 10) { printf("finished!"); break; }

        printf("entering variable is x%d\n", entering+1);
        //printf("-3 is bigger than -INF: %d\n", (-3 > -INFINITY));



        printf("theta: ");
        for ( i = 0; i < n-1; i++ ) { // Does i finish at the right time here?
            theta[i] = A[i][p-1] / A[i][entering];
            printf("%f  ", theta[i]);
        }
        printf("\n");
        
        exiting = argmin(theta, n-1, 0);
        printf("exiting variable is x%d\n", exiting+1);
         
        gaussElim(n, p, A, exiting, entering);

        printMat(n, p, A);


    }

    return 0;
}
