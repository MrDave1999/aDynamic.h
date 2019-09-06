#include <pscanf.h>
#include <assertx.h>
#define MAX_ARRAYS 3
#include <aDynamic.h>

enum
{
	SUM_PROM_A1,
	SUM_A2,
	SUM_A3
};

float CalcularProm_Array1(const uint8_t arrayid)
{
	float suma = 0;
	for (int i = 0; i != getsize(arrayid); ++i)
	{
		setal(float, arrayid, i, (float)i);
		suma += getal(float, arrayid, i);
	}
	return (suma / getsize(arrayid));
}

uint8_t SumarArrays(const uint8_t arrayid, const int* const size)
{
	int suma = 0;
	int num;
	dataread("%d", &num, "Ingrese el elemento que quieres agregar en el array %d\n", arrayid + 1);
	setsize(arrayid, *size);
	realloc_a(int, arrayid); /* Re-dimensionamos un array dinámico */
	setal(int, arrayid, *size - 1, num);
	for (int i = 0; i != getsize(arrayid); ++i)
		suma += getal(int, arrayid, i);
	printf("La suma total de todos los elementos del array %d fue de %d\n\n", arrayid + 1, suma);
	return EXIT_SUCCESS;
}

int main(void)
{
	int size = 0;
	char opcion;
	while (1)
	{
		dataread("%d", &getsize(SUM_PROM_A1), "Ingrese la cantidad de elementos del array 1:");
		assertc(getsize(SUM_PROM_A1) >= 1, "Error: La dimension debe ser mayor a 0.")
		break;
	}
	alloc_a(float, SUM_PROM_A1); /* Crea el array dinámico */
	printf("\nEl promedio del array 1 fue: %f\n\n", CalcularProm_Array1(SUM_PROM_A1));
	do
	{
		++size;
		error(SumarArrays, SUM_A2, &size);
		error(SumarArrays, SUM_A3, &size);
		pauseprogram();
		dataread("%c", &opcion, "\nQuieres salir del programa? Presiona la letra N \n");
		if (opcion == 'n' || opcion == 'N') break;
	} while (1);
	return EXIT_SUCCESS;
}
