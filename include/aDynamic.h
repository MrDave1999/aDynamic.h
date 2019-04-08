/*
			mDynamic.h - Array Dynamic.
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
void* __ptrtemp; /* Puntero temporal */

#ifndef error
	#define error(namefunc, ...) if(namefunc(__VA_ARGS__) == EXIT_FAILURE) return EXIT_FAILURE
#endif

#define getsize(arrayid) *(__amount + arrayid)
#define setsize(arrayid, value) getsize(arrayid) = value

#ifndef __cplusplus
/* Asigna/reserva memoria para un búfer de X elementos */
#define alloc_a(arrayid, nameptr)													\
	*(buf_ptr2 + arrayid) = malloc(*(__amount + arrayid) * sizeof *nameptr);		\
	if (*(buf_ptr2 + arrayid) == NULL)												\
	{																				\
		puts(""MESSAGE_ALLOC"");													\
		return EXIT_FAILURE;														\
	}																				\
	nameptr = *(buf_ptr2 + arrayid) 
#else
#define alloc_a(arrayid, nameptr, typedata)											\
	*(buf_ptr2 + arrayid) = malloc(*(__amount + arrayid) * sizeof(typedata));		\
	if (*(buf_ptr2 + arrayid) == NULL)												\
	{																				\
		puts(""MESSAGE_ALLOC"");													\
		return EXIT_FAILURE;														\
	}																				\
	nameptr = (typedata*)*(buf_ptr2 + arrayid)
#endif

#ifndef __cplusplus
/* Re-asigna memoria para un búfer de x elementos */
#define realloc_a(arrayid, nameptr)													\
	__ptrtemp = *(buf_ptr2 + arrayid);												\
	*(buf_ptr2 + arrayid) = realloc(__ptrtemp, *(__amount + arrayid) * sizeof *nameptr);	\
	if (*(buf_ptr2 + arrayid) == NULL)												\
		{																			\
		puts(""MESSAGE_REALLOC"");													\
		*(buf_ptr2 + arrayid) = __ptrtemp;											\
		return EXIT_FAILURE;														\
		}																			\
	nameptr = *(buf_ptr2 + arrayid)
#else
#define realloc_a(arrayid, nameptr, typedata)										\
	__ptrtemp = *(buf_ptr2 + arrayid);												\
	*(buf_ptr2 + arrayid) = realloc(__ptrtemp, *(__amount + arrayid) * sizeof(typedata));	\
	if (*(buf_ptr2 + arrayid) == NULL)												\
		{																			\
		puts(""MESSAGE_REALLOC"");													\
		*(buf_ptr2 + arrayid) = __ptrtemp;											\
		return EXIT_FAILURE;														\
		}																			\
	nameptr = (typedata*)*(buf_ptr2 + arrayid)
#endif

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
