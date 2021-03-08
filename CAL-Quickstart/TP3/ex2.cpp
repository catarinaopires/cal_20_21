#include "exercises.h"

int sumSubArray(int a[], int start, int finish) {
    int sum = 0;

    for (int i = start; i <= finish; i++) {
        sum += a[i];
    }
    return sum;
}

int maxCross(int A[], int l, int r, int &i, int &j) {
    int middle = (l+r)/2;

    int maxLeft = INT_MIN, leftSum = 0;
    for (int k = middle; k >= 0; k--){
        leftSum += A[k];

        if (leftSum > maxLeft) {
            maxLeft = leftSum;
            i = k;
        }
    }

    int maxRight = -INT_MIN, rightSum = 0;
    for (int k = middle + 1; k <= r; k++){
        rightSum += A[k];

        if (rightSum > maxRight) {
            maxRight = rightSum;
            j = k;
        }
    }

    return maxLeft + maxRight;
}

int maxSubsequenceDC_REC(int A[], unsigned int n, int l, int r, int &i, int &j) {

    if (l == r) {
        return A[l];
    }

    int middle = (l+r)/2;
    int left = maxSubsequenceDC_REC(A, n, l, middle, i, j);
    int right = maxSubsequenceDC_REC(A, n, middle + 1, r, i, j);

    int cI, cJ;
    int cross = maxCross(A, l, r, cI, cJ);

    if (left > right) {
        if (left > cross) {
            if (sumSubArray(A, i, j) < left) {
                i = l;
                j = middle;
                return left;
            }
            else{
                return sumSubArray(A, i, j);
            }
        }
        else {
            if (sumSubArray(A, i, j) < cross) {
                i = cI;
                j = cJ;
                return cross;
            }
            else{
                return sumSubArray(A, i, j);
            }
        }
    }
    else {
        if (right > cross) {
            if (sumSubArray(A, i, j) < right) {
                i = middle + 1;
                j = r;
                return right;
            }
            else{
                return sumSubArray(A, i, j);
            }
        }
        else {
            if (sumSubArray(A, i, j) < cross) {
                i = cI;
                j = cJ;
                return cross;
            }
            else{
                return sumSubArray(A, i, j);
            }
        }
    }
}

int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j) {
    return maxSubsequenceDC_REC(A, n, 0, n-1, i, j);
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP3_Ex2, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    int i, j;
    EXPECT_EQ(maxSubsequenceDC(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDC(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDC(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDC(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}