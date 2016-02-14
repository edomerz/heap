#include <stdio.h>

#include "heap.h"

#define START(X) (printf("\n[%s %s %d]%s\n", __FILE__, __func__, __LINE__, (X)))

int IsBefore(const void *data1, const void *data2, const void *args);
int IsMatch(const void *data, const void *param);

int main(int argc, char* argv[], char** envp)
{
	heap_t *heap = NULL;
	size_t num_elements = 4;
	size_t in1 = 2;
	size_t in2 = 7;
	size_t in3 = 26;
	size_t in4 = 25;

	size_t param1 = 2;
	size_t param2 = 19;

	size_t tmp1 = 0;
	void *tmp2 = NULL;

	/*____HeapCreate_______*/
	START("HeapCreate");

	heap = HeapCreate(&IsBefore, sizeof(size_t), num_elements);

	printf("heap: %p", (void*)heap);
	/*____HeapCreate END_______*/
	
	/*____HeapSize_______*/
	START("HeapSize");

	printf("HeapSize(heap): %lu\n", HeapSize(heap));
	/*____HeapSize END_______*/

	/*____HeapIsEmpty_______*/
	START("HeapIsEmpty");
	printf("HeapIsEmpty(heap): %d\n", HeapIsEmpty(heap));
	/*~~~~HeapIsEmpty END~~~*/

	/*____HeapPush 1_______*/
	START("HeapPush 1");
	HeapPush(heap, &in1);

	printf("HeapIsEmpty(heap): %d\n", HeapIsEmpty(heap));

	printf("HeapSize(heap): %lu\n", HeapSize(heap));

	HeapPrint(heap);

	/*~~~~HeapPush END~~~*/

	/*____HeapPush 2_______*/
	START("HeapPush 2");
	HeapPush(heap, &in2);

	printf("HeapIsEmpty(heap): %d\n", HeapIsEmpty(heap));

	printf("HeapSize(heap): %lu\n", HeapSize(heap));

	HeapPrint(heap);
	/*~~~~HeapPush END~~~*/

	/*____HeapPush 3_______*/
	START("HeapPush 3");
	HeapPush(heap, &in3);

	printf("HeapIsEmpty(heap): %d\n", HeapIsEmpty(heap));

	printf("HeapSize(heap): %lu\n", HeapSize(heap));

	HeapPrint(heap);
	/*~~~~HeapPush END~~~*/

	/*____HeapPop 1_______*/
	START("HeapPop 1");
	HeapPop(heap);

	printf("HeapIsEmpty(heap): %d\n", HeapIsEmpty(heap));

	printf("HeapSize(heap): %lu\n", HeapSize(heap));

	HeapPrint(heap);
	/*~~~~HeapPop END~~~*/

	/*____HeapPop 1_______*/
	START("HeapPop 1");
	HeapPop(heap);

	printf("HeapIsEmpty(heap): %d\n", HeapIsEmpty(heap));

	printf("HeapSize(heap): %lu\n", HeapSize(heap));

	HeapPrint(heap);
	/*~~~~HeapPop END~~~*/

	/*____HeapPush 4_______*/
	START("HeapPush 4");
	HeapPush(heap, &in4);

	printf("HeapIsEmpty(heap): %d\n", HeapIsEmpty(heap));

	printf("HeapSize(heap): %lu\n", HeapSize(heap));

	HeapPrint(heap);
	/*~~~~HeapPush END~~~*/

	/*____HeapRemove 1_______*/
	START("HeapRemove 1");
	tmp1 = *(size_t*)HeapRemove(heap, &IsMatch , &param1);
	printf("tmp1:%lu\n", tmp1);

	printf("HeapIsEmpty(heap): %d\n", HeapIsEmpty(heap));

	printf("HeapSize(heap): %lu\n", HeapSize(heap));

	HeapPrint(heap);

	/*____HeapRemove 2_______*/
	START("HeapRemove 2");
	tmp2 = HeapRemove(heap, &IsMatch , &param2);
	printf("tmp2:%p\n", tmp2);

	printf("HeapIsEmpty(heap): %d\n", HeapIsEmpty(heap));

	printf("HeapSize(heap): %lu\n", HeapSize(heap));

	HeapPrint(heap);
	/*~~~~HeapRemove END~~~*/

	/*____HeapDestroy_______*/
	START("HeapDestroy");

	HeapDestroy(heap);
	/*____HeapDestroy END_______*/

	return(0);
}

int IsBefore(const void *data1, const void *data2, const void *args)
{
	return(*(size_t*)data1 < *(size_t*)data2 ? 1 : 0);
}

int IsMatch(const void *data, const void *param)
{
	return(*(size_t*)data == *(size_t*)param);
}
