#ifndef __DYN_VEC_H__
#define __DYN_VEC_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct dyn_vec_adt dyn_vec_t;

/* creates a dynamic vector for num_elements, each of size element_size */
dyn_vec_t* DynVecCreate(size_t element_size, size_t num_elements);
/* destroy the dynamic vector created by DynVecDestroy */
void DynVecDestroy(dyn_vec_t* dynamic_vector);

/* increase/decrease capacity of dynamic vector */
int DynVecReserve(dyn_vec_t* dynamic_vector, size_t num_elements);

/* get the number of elements in dynamic vector */	
size_t DynVecSize(dyn_vec_t* dynamic_vector);

/*returns elements size*/
size_t DynVecElementSize(dyn_vec_t *dynamic_vector);

/* get the capacity of elements in dynamic vector */
size_t DynVecCapacity(dyn_vec_t* dynamic_vector);

/* get element by index */
void* DynVecGetItemAddress(dyn_vec_t* dynamic_vector, size_t index); 

/*  add element to the end of dynamic vector */
void DynVecPushBack(dyn_vec_t* dynamic_vector, void* element);

/* removes the last element from dynamic vector */
void DynVecPopBack(dyn_vec_t* dynamic_vector);

/* prints the array */
void DynVecPrint(dyn_vec_t* dynamic_vector);


#endif /* ifndef __DYN_VEC_H__*/
