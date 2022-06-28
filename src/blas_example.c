#include "/home/alexanders/Documents/repos/C-FlappIO/include/cblas.h"
#include <stdio.h>

void main()
{
    blasint m = 4; // Rows for Matrix A and C
    blasint n = 1; // Columns for Matrix B and C
    blasint k = 3; // Columns for Matrix A and Rows for Matrix B
    const float alpha = 1; // ??
    const float beta = 0;  // ??
    blasint lda = m;
    blasint ldb = k;
    blasint ldc = k;

    float A[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    float B[] = {1,2,3};
    float C[3];
    cblas_sgemm(CblasColMajor, CblasNoTrans, CblasNoTrans, m, n, k, alpha, A, lda, B, ldb, beta, C, ldc);

    blasint m_1 = 3;
    blasint n_1 = 3;
    const float alpha_1 = 1;
    const float beta_1 = 0;
    blasint lda_1 = m_1;
    blasint incx_1 = 1;
    blasint incy_1 = 1;



    float A_1[] = {0.6, 0.4, 0.1, 0.5, 0.3, 0.1, 0.2, 0.9, 0.7};
    float X_1[] = {0.2, 0.1, 0.3};
    float Y_1[] = {0, 0, 0};
    cblas_sgemv(CblasRowMajor, CblasNoTrans, m_1, n_1, alpha_1, A_1, lda_1, X_1, incx_1, beta_1, Y_1, incy_1);
    

    printf("Matrix X Matrix\n");
    for (int i = 0; i < n*k; i++) {
        if (i%m == 0)
            printf("\n");
        
        printf(" %f", C[i]);
    }

    printf("\n");
    printf("\n--------------\n");
    printf("\n");

    printf("Matrix X Vector\n");
    for (int i = 0; i < m_1; i++) {
        printf("%f ", Y_1[i]);
    }
}