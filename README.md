# aDynamic.h
[![aDynamic.h](https://shields.southcla.ws/badge/C-aDynamic.h-2f2f2f.svg?style=flat-square)](https://github.com/MrDave1999/aDynamic.h)

Con este archivo de cabecera no tendrás que preocuparte en liberar la memoria a cada rato con la función free, porqué el include lo hace por ti, además de eso, te proporciona una sintaxis viable y entendible.

# Instalación

Agrega el fichero `aDynamic.h` en el directorio donde esté el código fuente del programa y lo incluyes de esta forma:
```C
#include "aDynamic.h"
```
Sí vas a usar el include para varios programas, lo puedes agregar directamente en la carpeta `include` (la que viene por defecto en el IDE). Luego de eso, puedes incluir el archivo de esta forma:
```C
#include <aDynamic.h>
```

# Requisitos

Para que el include funcione correctamente necesitas definir la macro `MAX_ARRAYS` antes de incluir `aDynamic.h`, de lo contrario, el compilador lanzará un error.
```C
#define MAX_ARRAYS 3 /* Aquí especificas la cantidad de arrays dinámicos que vayas a utilizar .*/
#include <aDynamic.h> /* Luego de eso, incluyes el archivo de cabecera */
```

# Macros

- `getsize(arrayid)`:

Obtiene la cantidad de elementos de un array dinámico.

- `setsize(arrayid, value)`:

Asigna una cantidad de elementos a un array dinámico.
  
- `dmat_a(arrayid)`:

Libera la memoria de un específico array dinámico.

- `free_a()`:

Libera la memoria de cada array dinámico que exista en el heap/montón.

- `alloc_a(arrayid, nameptr)`:	

Asigna memoria para un array dinámico. 
  
**Ejemplo:**
```C
#define MAX_ARRAYS 2 /* Especificamos la cantidad de arrays a crear */
#include <aDynamic.h> /* Incluimos el archivo de cabecera */

/* La identificación de cada array debe comenzar desde 0 */
#define ARRAY_ID1 0
#define ARRAY_ID2 1

int main(void)
{
	int* pa;
	int* pb;
	/* Asignamos el tamaño de elementos del array A y B */
	setsize(ARRAY_ID1, 5);
	setsize(ARRAY_ID2, 6);
	/* El puntero pa y pb tendrán la dirección de memoria del primer elemento del array  */
	alloc_a(ARRAY_ID1, pa);
	alloc_a(ARRAY_ID2, pb);
	/* La memoria se libera automáticamente */
	return 0;
}   
```
Sí llega a ver algún fallo en la asignación de memoria, la macro `alloc_a` hace que la función main retorne 1.
  
**Nota:** En el primer argumento de `alloc_a` se especifica la ID del array.
  
- `realloc_a(arrayid, nameptr)`:	

Re-dimensiona el tamaño de un array dinámico.
  
**Ejemplo:**
```C
#define MAX_ARRAYS 2
#include <aDynamic.h>

#define ARRAY_ID1 0
#define ARRAY_ID2 1

int Array(const int arrayid, const int size)
{
	int* ptr;
	setsize(arrayid, size);
	/*
	Con esta macro podemos asignar memoria solo una vez y luego de eso,
	podemos re-dimensionará el array
	*/
	realloc_a(arrayid, ptr);
	return 0;
}

int main(void)
{
	if (Array(ARRAY_ID1, 7) == 1) return 1;
	if (Array(ARRAY_ID2, 9) == 1) return 1;
	/* La memoria se libera automáticamente */
	return 0;
}

```
La macro "realloc_a" hace que la función "Array" retorne 1 si es que hubo algún fallo en la re-asignación de memoria. Por esa razón     cuando llamamos la función "Array" agregamos esa condición para detectar si hay un error al momento de re-dimensionar.
  
- `error(namefunc, ...)`:

Permite llamar una función cuando en esa misma subrutina se (re)asigna memoria.
  
Esta expresión:
```C
if (Array(ARRAY_ID1, 7) == 1) return 1;
```
Es equivalente a esto:
```C
error(Array, ARRAY_ID1, 7);
```
La mayoría de las macros llevan un guion bajo + una letra 'a', eso hace referencia a un "array dinámico".
  
# Uso

```C
#define MAX_ARRAYS 2
#include "aDynamic.h"

enum 
{ 
	AA,  //Array A
	AB  //Array B
};

/* Función que sirve para re-dimensionar el array B (AB) */
int Re_DimensionarAB(void)
{
	int i;
	int* pb;
	/* Este código re-dimensiona el array B tres veces. */
	for (setsize(AB, 1); getsize(AB) != 4; ++getsize(AB))
	{
		realloc_a(AB, pb);
		for (i = 0; i != getsize(AB); ++i)
			printf("%d\n", &pb[i]);
		printf("\n");
	}
	return 0;
}

int main(void)
{
	/* Con este puntero podemos a acceder/modificar el array A */
	char* pa;
	/* Pedimos al usuario el tamaño de elementos del array A */
	printf("Ingrese la cantidad de elementos del array A:\n");
	scanf("%d", &getsize(AA));
	/* Reservamos memoria para construir el array A */
	alloc_a(AA, pa);
	/* Imprime las direcciones de memoria de cada elemento del array A */
	for (int i = 0; i != getsize(AA); ++i)
		printf("%d\n", &pa[i]);

	printf("\n\n");
	/* Llamamos la función y detectamos si hubo algún error en la asignación */
	error(Re_DimensionarAB);

	/* La memoria se libera automáticamente */
	return 0;
}
```
En el siguiente enlace hay un programa completo aplicando `aDynamic.h`: [Ejemplo](https://github.com/MrDave1999/aDynamic.h/blob/master/Example/Example.c)

Para la realización de ese programa se usó los siguientes header files:

- [pscanf.h](https://github.com/MrDave1999/pscanf.h)
- [assertx.h](https://github.com/MrDave1999/assertx.h)

# Arrays de Estructuras

Arrays de estructuras son búfers contiguos. Eso quiere decir que sí hago esto:
```C
#define MAX_ARRAYS 2
#include <aDynamic.h>
```
Es como si tuviera 2 búfers contiguos de X elementos. Miremos el siguiente ejemplo:
```C
#define MAX_ARRAYS 1 /* Solo quiero un búfer contiguo */
#include <aDynamic.h>

enum ID_ARRAY
{
	ARRAY_A //La ID del primer búfer contiguo
};

/* Los elementos de cada búfer contiguo */
struct _tipo
{
	float a;
	int b;
	char c;
};

/* Asignamos un alias al nombre de la estructura "_tipo" */
typedef struct _tipo tipo;

int Array(tipo** pa)
{
	/* El puntero aux es necesario para la invocación de las macros alloc_a y realloc_a */
	tipo* aux;
	/* Asignamos el tamaño del array de estructura */
	setsize(ARRAY_A, 5);
	/* Reservamos memoria para 5 buffers contiguos */
	alloc_a(ARRAY_A, aux);
	for (int i = 0; i != getsize(ARRAY_A); ++i)
	{
		aux[i].a = 2.9f;
		aux[i].b = 5;
		aux[i].c = 'a';
	}
	/* Re-dimensionamos el array de estructura a 2 buffers */
	setsize(ARRAY_A, 2);
	realloc_a(ARRAY_A, aux);
	/* Mandamos la dirección de memoria del primer elemento de ese array al puntero que pasamos por referencia */
	*pa = aux;
	return 0;
}

int main(void)
{
	tipo* pa;
	/* Pasamos la dirección de memoria del puntero PA */
	error(Array, &pa);
	printf("\n");
	printf("[Updates]: data Array A:\n\n");
	for (int i = 0; i != getsize(ARRAY_A); ++i)
	{
		printf("%f\n", pa[i].a);
		printf("%d\n", pa[i].b);
		printf("%c\n", pa[i].c);
		printf("\n");
	}
	/* La memoria se libera automáticamente */
	return 0;
}
```
**Nota:** Búfers contiguo significa que varios búfer estarán juntos entre sí, por esa razón es posible usar esta sintaxis para acceder/modificar algún miembro de cualquier búfer.
```C
pa[i].a = 9;
```

# Créditos

- [MrDave](https://github.com/MrDave1999)
  - Por la idea de crear aDynamic.h
- [Microsoft](https://www.microsoft.com/es-ec/)
  - Por el desarrollo de las funciones malloc y realloc.
