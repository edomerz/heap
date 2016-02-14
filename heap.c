#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>

#include "dyn_vec.h"
#include "heap.h"

/* HeapCmp(void *d1, void *d2, void *args);
 * struct CompAux
 * {
 *
 */

struct heap_adt
{
	dyn_vec_t *dyn_vec;
	heap_is_before_t compare;
}heap_adt;

/*create a heap and returns a pointer to it, else NULL*/
heap_t *HeapCreate(heap_is_before_t compare,
				   size_t element_size,
				   size_t num_elements)
{
	heap_t *heap = (assert(compare), (heap_t*)malloc(sizeof(heap_t)));
	if(!heap)
	{
		return(NULL);
	}

	heap->dyn_vec = DynVecCreate(element_size, num_elements);
	if(!heap->dyn_vec)
	{
		return(NULL);
	}

	heap->compare = compare;

	return(heap);
}

/*destroys 'heap' */
void HeapDestroy(heap_t *heap)
{
	assert(heap);
	DynVecDestroy(heap->dyn_vec);

	free(heap);
}

/* returns number of elements in heap */
size_t HeapSize(const heap_t *heap)
{
	return(DynVecSize(heap->dyn_vec));
}

/* returns 1 if 'heap' is empty, else 0 */
int HeapIsEmpty(const heap_t *heap)
{
	return(!HeapSize(heap));
}


/* returns the first-prioritized element
undefined behavior if 'peek' on empty 'heap' */
void *HeapPeek(const heap_t *heap)
{
	assert(heap);

	return(DynVecGetItemAddress(heap->dyn_vec, 0));
}

static void Swap(void *address1, void *address2, void *tmp, size_t element_size)
{
	memmove(tmp, address1 , element_size);
	memmove(address1, address2, element_size);
	memmove(address2, tmp, element_size);
}

/*HEAPFIY the heap after insertion, checking if the inserted element violates
  the heap properties */
static int Swim(heap_t *heap, size_t index)
{
	/*size_t tmp_index = DynVecSize(heap->dyn_vec) - 1;*/
	size_t element_size = DynVecElementSize(heap->dyn_vec);
	void *tmp = malloc(element_size);
	if(!tmp)
	{
		return(1);
	}

	while((index > 0)  &&
		  (heap->compare(DynVecGetItemAddress(heap->dyn_vec, index / 2),
				         DynVecGetItemAddress(heap->dyn_vec, index),
						 NULL)) )
	{
		Swap(DynVecGetItemAddress(heap->dyn_vec, index / 2),
			 DynVecGetItemAddress(heap->dyn_vec, index),
			 tmp,
			 element_size);

		index /= 2;
	}
	free(tmp);

	return(0);
}

/* Inserts a new element to 'heap' in a prioritized manner,
  and initialize it with 'data'.
  Returns 0 for success, else 1 */
int HeapPush(heap_t *heap, void *data)
{
	assert(heap);
	assert(data);

	DynVecPushBack(heap->dyn_vec, data);

	return(Swim(heap, DynVecSize(heap->dyn_vec) - 1));
}

/* prints the array */
void HeapPrint(heap_t* heap)
{
	assert(heap);
	DynVecPrint(heap->dyn_vec);
}

static int Sink(heap_t *heap, size_t index, void *tmp)
{
	/*size_t tmp_index = 0;*/
	size_t element_size = DynVecElementSize(heap->dyn_vec);
	size_t array_size = DynVecSize(heap->dyn_vec) - 1;



	while((((index + 1) * 2) - 1 <= array_size)) /* left child is in range of array */
	{
		size_t j = ((index + 1) * 2) - 1; /* left child */

		/* if the right child is greater the the left, choose the left */
		if((j < array_size) &&
		   (heap->compare(DynVecGetItemAddress(heap->dyn_vec, j),
				   	      DynVecGetItemAddress(heap->dyn_vec, j + 1),
						  NULL)) )
		{
			++j;
		}
		/* the parent, tmp_index, is >= than its biggest child , j, ->do nothing */
		if(!(heap->compare(DynVecGetItemAddress(heap->dyn_vec, index),
						  DynVecGetItemAddress(heap->dyn_vec, j),
						  NULL)) )
		{
			break;
		}

		Swap(DynVecGetItemAddress(heap->dyn_vec, index),
			 DynVecGetItemAddress(heap->dyn_vec, j),
		 tmp,
		 element_size);
	}

	return(0);
}

/* Removes the first-prioritized element from 'heap'
 Returns 0 for success, else 1 */
int HeapPop(heap_t *heap)
{
	int ret = 1;
	size_t element_size = DynVecElementSize(heap->dyn_vec);
	void *tmp = malloc(element_size);
	if(!tmp)
	{
		return(1);
	}
	assert(heap);

	Swap(DynVecGetItemAddress(heap->dyn_vec, 0),
		 DynVecGetItemAddress(heap->dyn_vec, DynVecSize(heap->dyn_vec) - 1),
		 tmp,
		 element_size);

	DynVecPopBack(heap->dyn_vec);

	ret = Sink(heap, 0, tmp);

	free(tmp);

	return(ret);
}
/* Removes element from 'heap' matching the criteria in 'is_match'
 *  return it's data if found, else NULL */
void *HeapRemove(heap_t *heap, heap_is_match_t is_match, void *param)
{
	size_t i = (assert(heap), assert(is_match), 0);
	size_t array_size = DynVecSize(heap->dyn_vec);
	void *ret = NULL;
	void *tmp = NULL;

	while(i < array_size)
	{
		if(is_match(DynVecGetItemAddress(heap->dyn_vec, i), param))
		{
			ret = DynVecGetItemAddress(heap->dyn_vec, i);
			tmp = malloc(DynVecElementSize(heap->dyn_vec));

			break;
		}
		++i;
	}

	if(!ret)
	{
		return(ret);
	}

	Swap(DynVecGetItemAddress(heap->dyn_vec, i),
		 DynVecGetItemAddress(heap->dyn_vec, array_size - 1),
		 tmp,
		 DynVecElementSize(heap->dyn_vec));

	DynVecPopBack(heap->dyn_vec);

	if(heap->compare(DynVecGetItemAddress(heap->dyn_vec, i / 2),
					 DynVecGetItemAddress(heap->dyn_vec, i),
					 NULL))
	{
		Swim(heap, i);
	}
	else
	{
		Sink(heap, i, tmp);
	}
	free(tmp);

	return(ret);
}
/*
typedef int (*heap_is_match_t) (const void *data, const void *param);

typedef struct heap_adt heap_t;


*/
