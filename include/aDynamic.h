/*
			aDynamic.h - Array Dynamic [v1.4]
			Copyright (c) David Román. All rights reserved.
*/

#ifndef _INC_ADYNAMIC
#define _INC_ADYNAMIC

#include <stdio.h> 
#include <stdlib.h> 

#ifndef MESSAGE_ALLOC
	#define MESSAGE_ALLOC	"Error allocating memory"
#endif

#ifndef MESSAGE_REALLOC
	#define MESSAGE_REALLOC "Error (re)allocating memory"
#endif

#ifndef MAX_ARRAYS 
	#error You must define the macro MAX_ARRAYS.
#endif

int __amount[MAX_ARRAYS]; /* Cantidad de elementos de cada array dinámico */
void* buf_ptr2[MAX_ARRAYS]; /* Búfer de punteros */

#ifndef error
	#define error(namefunc, ...) if(namefunc(__VA_ARGS__) == EXIT_FAILURE) return EXIT_FAILURE
#endif

/* Obtiene la cantidad de elementos de un arreglo dinámico */
#define getsize(arrayid) *(__amount + arrayid)

/* Asigna una cantidad de elementos para un arreglo dinámico */
#define setsize(arrayid, value) getsize(arrayid) = value

/* getal = getArrayElement -> Obtiene un elemento específico de un arreglo dinámico */
#define getal(typedata, arrayid, index) (*((typedata*)*(buf_ptr2 + arrayid) + index))

/* setal = setArrayElement -> Asgina un elemento específico a un arreglo dinámico */
#define setal(typedata, arrayid, index, value) getal(typedata, arrayid, index) = value

/* getad= getAddress -> Obtiene la dirección de memoria del primer elemento de un arreglo dinámico */
#define getad(arrayid) *(buf_ptr2 + arrayid)

/* Asigna memoria dinámicamente */
#define alloc_a(typedata, arrayid) if(alloc_aEx(arrayid, sizeof(typedata)) == NULL) return EXIT_FAILURE

/* Re-asigna memoria dinámica */
#define realloc_a(typedata, arrayid) if(realloc_aEx(arrayid, sizeof(typedata)) == NULL) return EXIT_FAILURE

/* Libera la memoria de todos los arrays dinámicos que existan en el heap */
#define free_a()																	\
for (unsigned int __arrayid = 0; __arrayid != MAX_ARRAYS; ++__arrayid)				\
{																					\
	if (*(buf_ptr2 + __arrayid) != NULL)											\
	{																				\
		dmat_a(__arrayid);															\
	}																				\
}*(buf_ptr2 + 0) = NULL

/* Libera la memoria de un específico array dinámico */
#define dmat_a(arrayid)																\
free(*(buf_ptr2 + arrayid));														\
*(buf_ptr2 + arrayid) = NULL;														\
*(__amount + arrayid) = 0	

void* alloc_aEx(size_t arrayid, size_t size)
{
	*(buf_ptr2 + arrayid) = malloc(*(__amount + arrayid) * size);
	if (*(buf_ptr2 + arrayid) == NULL)												
	{																				
		puts(""MESSAGE_ALLOC"");													
		return NULL;														
	}
	return *(buf_ptr2 + arrayid);
}

void* realloc_aEx(size_t arrayid, size_t size)
{
	void* __ptrtemp = *(buf_ptr2 + arrayid);												
	*(buf_ptr2 + arrayid) = realloc(__ptrtemp, *(__amount + arrayid) * size);	
	if (*(buf_ptr2 + arrayid) == NULL)												
	{																				
		puts(""MESSAGE_REALLOC"");													
		*(buf_ptr2 + arrayid) = __ptrtemp;											
		return NULL;														
	}
	return *(buf_ptr2 + arrayid);
}

												
/* Hook/enganche a main */

int aDynamic_main();

int main(void)
{
	unsigned char xx = aDynamic_main();
	free_a();
	return xx;
}

#ifndef _ALS_main
	#define _ALS_main
#else
	#undef main
#endif
#define main aDynamic_main

#endif /* _INC_ADYNAMIC */
