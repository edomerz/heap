#include <stdlib.h>
#include <string.h>

#include "dyn_vec.h"

typedef struct dyn_vec_adt
{
	size_t elem_size;
	size_t size;		/* current number of elements */
	size_t capacity;	/* total availablity of elemets */
	void* arr;
}dyn_vec_adt;

/* creates a dynamic vector for num_elements, each of size element_size */
dyn_vec_t* DynVecCreate(size_t element_size, size_t num_elements)
{
	dyn_vec_t * vec = (dyn_vec_t *)malloc(sizeof(dyn_vec_t));
	if(!vec)
	{
		return(NULL);
	}
	
	vec->capacity = num_elements;
	vec->elem_size = element_size;
	vec->size = 0;
	vec->arr = NULL;
	
	if(DynVecReserve(vec, num_elements)) 
	{
		fprintf(stderr, "%s %s %d\n", __FILE__, __func__, __LINE__);
		return(NULL);
	}
	
	return(vec);
}

/* destroy the dynamic vector created by DynVecDestroy */
void DynVecDestroy(dyn_vec_t* vec)
{
	free(vec->arr);
	free(vec);
}

/* increase/decrease capacity of dynamic vector */
int DynVecReserve(dyn_vec_t* vec, size_t num_elements)
{
	dyn_vec_t* tmp = vec;
	if(! (tmp->arr = realloc(tmp->arr, num_elements * vec->elem_size)) )
	{
		fprintf(stderr, "realloc failure %s %s %d\n",__FILE__, __func__, __LINE__);
		free(vec);
		return(-1);
	}	
	else
	{
		vec = tmp;	
	}
	
	vec->capacity = num_elements;
	if(vec->size > num_elements)
	{
		vec->size = num_elements;
	}
	
	return(0);
}

/* get the number of elements in dynamic vector */	
size_t DynVecSize(dyn_vec_t* vec)
{
	/*printf("vec->size: %lu\n", vec->size);   			 DEBUG!!!!!!!!!!!!!!!!!!!!! */
	
	return(vec->size);
}

/*returns elements size*/
size_t DynVecElementSize(dyn_vec_t *vec)
{
	return(vec->elem_size);
}

/* get the capacity of elements in dynamic vector */
size_t DynVecCapacity(dyn_vec_t* vec)
{
/*	printf("vec->capacity: %lu\n", vec->capacity);		 DEBUG!!!!!!!!!!!!!!!!!!!!! */

	return(vec->capacity);
}

/* get element by index */
void* DynVecGetItemAddress(dyn_vec_t* vec, size_t index)
{
    void* ret = (void*)&((char*)vec->arr)[vec->elem_size * index];
	
	/*printf("GetItemAddress - index req: %lu:\n", index);*/
	/*printf("arr address:%p, index address:%p\n", vec->arr, ret);*/
	return(ret);
}

/*  add element to the end of dynamic vector */
void DynVecPushBack(dyn_vec_t* vec, void* element)
{
	void* adr_tmp = NULL;
	size_t size_tmp = vec->size;
	
	if(size_tmp == vec->capacity)
	{
		DynVecReserve(vec, size_tmp * 2);
	}
	
	adr_tmp = DynVecGetItemAddress(vec, size_tmp);
	/*printf("before memmove - &vec->arr[vec->elem_size * size_tmp]: %p\n", adr_tmp);  DEBUG!!!!!!!!!!!! */
	
	memmove(adr_tmp, element, vec->elem_size);
	size_tmp = ++(vec->size);
	
	adr_tmp = DynVecGetItemAddress(vec, size_tmp);					/* DEBUG!!!!!!!!!!!! */
	/*printf("after memmove - &vec->arr[vec->elem_size * size_tmp]: %p\n", adr_tmp);	 DEBUG!!!!!!!!!!!! */
}

/* removes the last element from dynamic vector */
void DynVecPopBack(dyn_vec_t* vec)
{
	size_t size_tmp = vec->size;
	printf("before pop size: %lu\n",size_tmp);				/* DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	if(!size_tmp)
	{
		return;
	}
	
	size_tmp = --(vec->size);
	if(size_tmp <= (vec->capacity) / 4)
	{
		DynVecReserve(vec, (vec->capacity) / 4);
	}
	printf("after pop size: %lu\n",vec->size);			/* DEBUG!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	
	return;
}

void DynVecPrint(dyn_vec_t* vec)
{
	int i = 0;
	size_t size_tmp = vec->size;
	size_t e_size = vec->elem_size;
	for( ; i < size_tmp; ++i)
	{
		switch (e_size)
		{
		case 8:
			printf("%lu ", ((size_t*)vec->arr)[i]);
			break;
		case 4:
			printf("%d ", ((int *)vec->arr)[i]);
			break;
		case 2:
			printf("%d ", ((short *)vec->arr)[i]);
			break;
		case 1:
			printf("%c ", ((char *)vec->arr)[i]);
			break;
		default:
			printf("unknown element size\n");
			return;
		}
	}
	printf("\n");
}
