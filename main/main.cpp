#include <stdio.h>
//#include <winsock.h>
//#include <ws2tcpip.h>

//#pragma comment(lib, "ws2_32.lib")


const int MAXPUERTOS = 1023;

void mostrarMenu(int *res);
void escanearPuertos(int array[], int * cant, int inicio, int fin);
void ordenamientoBurbuja(int array[], int n);
void mostrarEscaneo(int array[], int n);
int buscarPuerto(int array[], int n, int puerto);



int main()
{
	int puertosEscaneados[MAXPUERTOS];
	int cantActual = 0; //cantidad de puertos escaneados
	int opcion, inicio, fin, puertoAbuscar;


	
	
	do
	{
		mostrarMenu(&opcion);

		switch (opcion)
		{

		case 1:
			printf("donde desea iniciar el escaneo?");
			scanf_s("%d", &inicio);

			printf("donde desea finzalizar el escaneo?");
			scanf_s("%d", &fin);

			printf("[INFO]Iniciando escaneo...\n");
			escanearPuertos(puertosEscaneados, &cantActual, inicio, fin);
			printf("Escaneo finalizado.\n");
			break;

		case 2:

			if (cantActual == 0) printf("Por favor, realice un escaneo primero.\n");
			else
			{
				printf("-----Reporte de escaneo-----\n");
				mostrarEscaneo(puertosEscaneados, cantActual);
				
			}
			break;

		case 3:

			if (cantActual == 0) printf("Por favor, realice un escaneo primero.\n");
			else
			{
				printf("-----Buscar puerto-----\n");
				printf("-Puerto a buscar: ");
				scanf_s("%d", &puertoAbuscar);

				int resultado = buscarPuerto(puertosEscaneados, cantActual, puertoAbuscar);
				printf("[INFO] El puerto se ha encontrado en la posicion %d \n", resultado);

				if(resultado == -1 ) printf("[INFO] No se ha encontrado el puerto.\n");
			}
			break;
		case 4:
			printf("Saliendo del programa... \n");
			printf("Adios!");
			break;
		default:

			printf("Opcion no valida! Introduzca una opcion valida.\n");
			break;

		}

	} while (opcion != 4);

	//WSACleanup();
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

void escanearPuertos(int array[], int *cant, int inicio, int fin)
{
	
	
	for ( int i = inicio; i < fin + 1; i++)
	{
		array[i-inicio] = i ;
	}
	*cant = (fin - inicio) + 1;

	printf("[INFO] Se encontraron %d puertos abiertos\n", *cant);


}

void ordenamientoBurbuja(int array[], int n)
{
	int i, j, temp;

	for (i = 0; i < n - 1; i++) 
	{

		for (j = 0; j < n - i - 1; j++) 
		{

			if (array[j] > array[j + 1]) 
			{
				
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}

void mostrarEscaneo(int array[], int n)
{

	ordenamientoBurbuja(array, n);

	for (int i = 0; i < n; i++)
	{
		printf(" %d ", array[i]);
	}
}

int buscarPuerto(int array[], int n, int puerto) 
{
	int derecha = n - 1;
	int izquierda = 0;
	int medio;
	
	while (izquierda <= derecha)
	{
		medio = (izquierda + derecha) / 2;
		if (array[medio] == puerto)
		{
			return medio;
		}
		if (puerto > array[medio])
		{
			izquierda = medio + 1;
		}
		else
		{
			derecha = medio - 1;
		}
	}


	return -1;
}