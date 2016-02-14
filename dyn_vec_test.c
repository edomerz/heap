#include "dyn_vec.h"
	
int main(int argc, char* argv[], char** envp)
{
	unsigned int element_size = 0, num_elements = 0;
	dyn_vec_t* tmp = NULL;
	int ch = 65;
	/*size_t i = 0; */
	/*size_t cap = 0; */
		
	if(argc != 3)
	{
		printf("Usage:./dyn_vec (unsigned int)element_size (unsigned int)num_elements\n");
		return(-1);
	}
	element_size = atol(argv[1]);
	num_elements = atol(argv[2]);
	printf("elemet_size: %d\n", element_size);
	printf("num_elemets: %d\n", num_elements);
	printf("###############################################\n");
	
	/* create */	
	tmp = DynVecCreate(element_size, num_elements);
	
	/* get size */
	printf("vec size: %lu\n", DynVecSize(tmp));
	printf("###############################################\n");
	
	/* get capacity */
	printf("vec capacity: %lu\n", DynVecCapacity(tmp));
	printf("###############################################\n");
	
	/* Change capacity with RESEREVE */
	DynVecReserve(tmp, 8);
	
	/* get new SIZE */
	printf("vec size after reserve of 8: %lu\n", DynVecSize(tmp));	
	printf("###############################################\n");
	
	/* get new CAPACITY*/
	printf("vec capacity after reserve of 8: %lu\n", DynVecCapacity(tmp));
	printf("###############################################\n");
	
	/* get address of element n */
	DynVecGetItemAddress(tmp, 1);
	printf("###############################################\n");
	
	/* PUSH element */
	DynVecPushBack(tmp, (void*)&ch);
	printf("###############################################\n");
	
	/* get new SIZE */
	printf("###############################################\n");
	printf("vec size: %lu\n", DynVecSize(tmp));
	
	/* POP 
	DynVecPopBack(tmp);
	printf("###############################################\n");
	get new SIZE 
	printf("vec size: %lu\n", DynVecSize(tmp));
	printf("###############################################\n");
	 get new CAPACITY
	printf("vec capacity: %lu\n", DynVecCapacity(tmp));
	printf("###############################################\n");*/
	
	/* attemp to PRINT */
	DynVecPrint(tmp);
	
	
	/* DESTROY */
	DynVecDestroy(tmp);
	
	return(0);
}
