#include <stdio.h>


const int MAXPUERTOS = 20;

void mostrarMenu(int *res);
void escanearPuertos();
void ordenamientoBurbuja();
void mostrarEscaneo();



int main()
{
	int puertosEscaneados[MAXPUERTOS];
	int cantActual = 0; //cantidad de puertos escaneados
	int opcion;


	
	
	do
	{
		mostrarMenu(&opcion);

		switch (opcion)
		{

		case 1:

			printf("Iniciando escaneo...\n");
			//escanearPuertos();
			printf("Escaneo finalizado.\n");
			break;

		case 2:

			if (cantActual == 0) printf("Por favor, realice un escaneo primero.\n");
			else
			{
				printf("-----Reporte de escaneo-----\n");
				//ordenamientoBurbuja();
				//ordenamientoBurbuja();
				break;
			}

		case 3:

			if (cantActual == 0) printf("Por favor, realice un escaneo primero.\n");
			else
			{
				printf("-----Buscar puerto-----\n");
				//ordenamientoBurbuja();
				break;
			}

		default:

			printf("Opcion no valida. Introduzca una opcion valida.\n");
			break;

		}

	} while (opcion != 4);

	return 0;
}

void mostrarMenu(int *res)
{
	int respuesta;
		
	printf("_____________________________\n");
	printf("[1] escanear puertos\n");
	printf("[2] mostrar reporte\n");
	printf("[3] buscar puerto\n");
	printf("[4] salir\n");
	printf("------------------------------\n");
	scanf_s("%d", &respuesta);

	*res = respuesta;
}

void escanearPuertos()
{
}

void ordenamientoBurbuja()
{

}

void mostrarEscaneo()
{

}