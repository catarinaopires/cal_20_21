#include "exercises.h"

int maxSubsequenceDP(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int sum = 0, best = 0;
    int tempI, tempJ;

    for (int num = 0; num < n; num++) {
        if (sum + A[num] > A[num]) {
            tempJ = num;
            sum = sum + A[num];
        }
        else {
            sum = A[num];
            tempI = num;
            tempJ = num;
        }

        if (sum > best) {
            best = sum;
            i = tempI;
            j = tempJ;
        }
    }

    return best;

}

// BRUTE FORCE SOLUTION - TP1 EX2
int maxSubsequenceBF(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int maxSum = INT_MIN;

    for (int l = 0; l < n; l++){
        int tempSum = 0;

        for (int r = l; r < n; r++){
            tempSum += A[r];

            if (tempSum > maxSum) {
                maxSum = tempSum;
                i = l;
                j = r;
            }
        }

    }
    return maxSum;
}


// DIVIDE AND CONQUER SOLUTION - TP3 EX2
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

void testPerformanceMaxSubsequence() {
	// TODO
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex6, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequenceDP(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDP(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDP(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDP(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);

    testPerformanceMaxSubsequence();
}