#include <stdio.h> 
#include <stdlib.h>		/*use rand() to get random value of the array elements*/
#include <time.h>		/*use time to be a seed for rand()*/
#define LENGTH 16  		/*define the length of the array to be sorted*/ 
#define MAXIMUM 1000 	/*define the range of the element value in the array */
#define TYPE 0			/*define the sort type: increase 0, or decrease 1*/ 
#define METHOD 0		/*define which kind of sort method to use: 0-insert; 1-select; 2-merge*/

void Sort(unsigned Array[], unsigned length, unsigned type, unsigned method);
void InsertSortIncrease(unsigned Array[], unsigned length);
void InsertSortDecrease(unsigned Array[], unsigned length);
void SelectSortIncrease(unsigned Array[], unsigned length);
void SelectSortDecrease(unsigned Array[], unsigned length);
void MergeSortIncrease(unsigned Array[], unsigned length);
void MergeSortIncrease0(unsigned Array[], unsigned start, unsigned end);
void MergeIncrease(unsigned Array[], unsigned start, unsigned middle, unsigned end);
void MergeSortDecrease(unsigned Array[], unsigned length);
void MergeSortDecrease0(unsigned Array[], unsigned start, unsigned end);
void MergeDecrease(unsigned Array[], unsigned start, unsigned middle, unsigned end);

int main()
{
	/*initialize the origin array to be sorted*/
	unsigned a[LENGTH];
	int i,j,k;
	/*使用当前时间生成随机数产生的种子*/ 
	srand((unsigned)time(NULL));
	for(i = 0;i < LENGTH;i++){
		a[i] = (unsigned)rand()%MAXIMUM;
		printf("%u ", a[i]);
	}
	printf("\n\n");
	Sort(a,(unsigned)LENGTH,(unsigned)TYPE,(unsigned)METHOD);
	for(i = 0; i < LENGTH; i++){
		printf("%u ", a[i]);
	}
	printf("\n");
	return 0;
}

/*根据函数参数来判断是升序还是降序*/ 
void Sort(unsigned Array[], unsigned length, unsigned type, unsigned method)
{
	if(method == 0){
		if(type == 0)
			InsertSortIncrease(Array,length);
		else
			InsertSortDecrease(Array,length);
	}
	else if(method == 1){
		if(type == 0)
			SelectSortIncrease(Array,length);
		else
			SelectSortDecrease(Array,length);
	}
	else if(method == 2){
		if(type == 0)
			MergeSortIncrease(Array,length);
		else
			MergeSortDecrease(Array,length);
	}

}

/*按照升序方式进行插入排序*/ 
void InsertSortIncrease(unsigned Array[], unsigned length)
{
	int i,j,k;
	unsigned key;
	for(i = 1; i < length; i++){
		/*此处选择了依次向前判断，也可以选择依次向后判断，复杂度相同。只需改变三个表达式：j = 0; j < i-1; j++*/ 
		key = Array[i];
		j = i-1;
		while(j>=0 && Array[j] > key){
			Array[j+1] = Array[j];
			j --;
		}
		Array[j+1] = key;
		for(k = 0;k < length;k++){
			printf("%u ", Array[k]);
		}
		printf("\n");
	}
}

/*按照降序方式进行插入排序*/ 
void InsertSortDecrease(unsigned Array[], unsigned length)
{
	int i,j,k;
	unsigned key;
	for(i = 1; i < length; i++){
		/*此处选择了依次向前判断，也可以选择依次向后判断，复杂度相同。只需改变三个表达式：j = 0; j < i-1; j++*/ 
		key = Array[i];
		j = i-1;	
		while(j>=0 && Array[j] < key){
			Array[j+1] = Array[j];
			j --;
		}
		Array[j+1] = key;
		for(k = 0;k < length;k++){
			printf("%u ", Array[k]);
		}
		printf("\n");
	}
}

/*按照升序方式进行选择排序*/
void SelectSortIncrease(unsigned Array[], unsigned length)
{
	int i, j, k, key;
	unsigned temp;
	for(i = 0; i < length -1; i++){
		j = i + 1;
		key = i;
		while(j < length){
			if(Array[key] > Array[j]){
				key = j;
			}
			j ++;
		}
		if (key != i){
			temp = Array[i];
			Array[i] = Array[key];
			Array[key] = temp;
		}
		for(k = 0; k < length; k++){
			printf("%u ", Array[k]);
		}
		printf("\n");
	}
}

/*按照降序方式进行选择排序*/
void SelectSortDecrease(unsigned Array[], unsigned length)
{
	int i, j, k, key;
	unsigned temp;
	for(i = 0; i < length -1; i++){
		j = i + 1;
		key = i;
		while(j < length){
			if(Array[key] < Array[j]){
				key = j;
			}
			j ++;
		}
		if (key != i){
			temp = Array[i];
			Array[i] = Array[key];
			Array[key] = temp;
		}
		for(k = 0; k < length; k++){
			printf("%u ", Array[k]);
		}
		printf("\n");
	}
}

/*按照升序方式进行归并排序*/
void MergeSortIncrease(unsigned Array[], unsigned length)
{
	MergeSortIncrease0(Array,0,length-1);
}

void MergeSortIncrease0(unsigned Array[], unsigned start, unsigned end)
{
	if(start < end){
		unsigned middle = (start+end)/2;
		MergeSortIncrease0(Array, start, middle);
		MergeSortIncrease0(Array, middle+1, end);
		MergeIncrease(Array, start, middle, end);
		int i;
		for(i = 0; i < LENGTH; i++){
			printf("%u ", Array[i]);
		}
		printf("\n");
	}
	
}

void MergeIncrease(unsigned Array[], unsigned start, unsigned middle, unsigned end)
{
	int n1 = middle - start + 1;
	int n2 = end - middle;
	unsigned array1[n1], array2[n2];
	int i,j,k;
	for(i=0;i<n1;i++){
		array1[i] = Array[start+i];
	}
	for(i=0;i<n2;i++){
		array2[i] = Array[middle+1+i];
	}
	for(i=0, j=0, k=start;k<=end;k++){
		if(array1[i] <= array2[j] && i!=n1 || j==n2){   /*这里的判断语句是最难的地方，错了好多次才搞对。*/ 
			Array[k] = array1[i];
			i ++;
		}
		else if(array1[i] > array2[j] && j!=n2 || i==n1){
			Array[k] = array2[j];
			j ++;
		}
	}
}

/*按照降序方式进行归并排序*/
void MergeSortDecrease(unsigned Array[], unsigned length)
{
	MergeSortDecrease0(Array,0,length-1);
}

void MergeSortDecrease0(unsigned Array[], unsigned start, unsigned end)
{
	if(start < end){
		unsigned middle = (start+end)/2;
		MergeSortDecrease0(Array, start, middle);
		MergeSortDecrease0(Array, middle+1, end);
		MergeDecrease(Array, start, middle, end);
		int i;
		for(i = 0; i < LENGTH; i++){
			printf("%u ", Array[i]);
		}
		printf("\n");
	}
	
}

void MergeDecrease(unsigned Array[], unsigned start, unsigned middle, unsigned end)
{
	int n1 = middle - start + 1;
	int n2 = end - middle;
	unsigned array1[n1], array2[n2];
	int i,j,k;
	for(i=0;i<n1;i++){
		array1[i] = Array[start+i];
	}
	for(i=0;i<n2;i++){
		array2[i] = Array[middle+1+i];
	}
	for(i=0, j=0, k=start;k<=end;k++){
		if(array1[i] >= array2[j] && i!=n1 || j==n2){   /*这里的判断语句是最难的地方，错了好多次才搞对。*/ 
			Array[k] = array1[i];
			i ++;
		}
		else if(array1[i] < array2[j] && j!=n2 || i==n1){
			Array[k] = array2[j];
			j ++;
		}
	}
}
