#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FindMaximumSubArray(int Array[], int length)
{
	int Max = 0;
	int sum = 0;
	int i, left, right, sumleft;
	for(i = 0, left = 0, right = 0, sumleft = 0; i < length; i ++){
		sum += Array[i];
		if(Max < sum){
			Max = sum;
			right = i;
			left = sumleft;
		}
		if(sum < 0){
			sumleft = i+1;
			sum = 0;
		}
	}
	for(i = left; i <= right; i++){
		printf("%d ", Array[i]);
	}
	printf("\n%d, %d, %d", left, right, Max);
}

int main()
{
	int a[] = {3, -2, 2, 3, -5, 4};
	FindMaximumSubArray(a, 6);
}
