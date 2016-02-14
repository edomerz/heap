/*
	heap
*/
	
#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdio.h>

#include "dyn_vec.h"

typedef int (*heap_is_before_t)(const void *data1, const void *data2, const void *args);
typedef int (*heap_is_match_t) (const void *data, const void *param);

typedef struct heap_adt heap_t;

/*create a heap and returns a pointer to it, else NULL*/
heap_t *HeapCreate(heap_is_before_t compare, size_t element_size, size_t num_elements);

/*destroys 'heap'*/
void HeapDestroy(heap_t *heap);

/*returns number of elements in heap*/
size_t HeapSize(const heap_t *heap);

/*returns 1 if 'heap' is empty, else 0*/
int HeapIsEmpty(const heap_t *heap);

/*Inserts a new element to 'heap' in a prioritized manner,
  and initialize it with 'data'.
  Returns 0 for success, else 1 */
int HeapPush(heap_t *heap, void *data);

/* Removes the first-prioritized element from 'heap'
 * Returns 0 for success, else 1 */
int HeapPop(heap_t *heap);

/*returns the first-prioritized element*/
/*undefined behavior if 'peek' on empty 'heap'*/
void *HeapPeek(const heap_t *heap);

/* Removes element from 'heap' matching the criteria in 'is_match'
 *  return it's data if found, else NULL */
void *HeapRemove(heap_t *heap, heap_is_match_t is_match, void *param);

/* prints the array */
void HeapPrint(heap_t* heap);

#endif /* ifndef __HEAP_H__*/
