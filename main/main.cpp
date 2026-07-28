#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")


const int MAXPUERTOS = 2000;

void mostrarMenu(int* res);
void escanearPuertos(int array[], int* cant, int inicio, int fin, char ipDestino[16]);
void ordenamientoBurbuja(int array[], int n);
void mostrarEscaneo(int array[], int n);
int buscarPuerto(int array[], int n, int puerto);



int main()
{
	int puertosEscaneados[MAXPUERTOS];
	int cantActual = 0; //cantidad de puertos escaneados
	int opcion, inicio, fin, puertoAbuscar;

	char ipDestino[16];

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Error, no se pudo inicializar el winsock");
		return 1;
	}


	do
	{
		mostrarMenu(&opcion);

		switch (opcion)
		{

		case 1:
			printf("Que ip desea escanear?");
			scanf_s("%15s", ipDestino, (unsigned int)sizeof(ipDestino));

			printf("donde desea iniciar el escaneo?");
			scanf_s("%d", &inicio);

			while (inicio < 0) {
				printf("[ERROR] El puerto inicial no puede ser negativo.\n");

				printf("Por favor, ingrese un puerto valido \n");
				scanf_s("%d", &inicio);
			}

			printf("donde desea finzalizar el escaneo?");
			scanf_s("%d", &fin);

			
			if (inicio > fin) {
				printf("[ERROR] El puerto de inicio no puede ser mayor al final.\n");
			}
			else if ((fin - inicio + 1) > MAXPUERTOS) {
				printf("[ERROR] El rango supera el maximo permitido (%d).\n", MAXPUERTOS);
			}
			else {
				printf("[INFO] Iniciando escaneo...\n");

				printf("[INFO]Iniciando escaneo...\n");
				escanearPuertos(puertosEscaneados, &cantActual, inicio, fin, ipDestino);
				ordenamientoBurbuja(puertosEscaneados, cantActual);
				printf("Escaneo finalizado.\n");
			}
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

				if (resultado != -1) printf("[INFO] El puerto se ha encontrado en la posicion %d \n", resultado);

				if (resultado == -1) printf("[INFO] No se ha encontrado el puerto.\n");
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

	WSACleanup();
	return 0;
}

void mostrarMenu(int* res)
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

void escanearPuertos(int array[], int* cant, int inicio, int fin, char ipDestino[16])
{
	int j = 0;



	for (int i = inicio; i < fin + 1; i++)
	{
		SOCKET escanear_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (escanear_socket == INVALID_SOCKET)
		{
			printf("[INFO] Error al crear el socket para el puerto %d \n", i);
			continue;
		}
		u_long modo = 1;
		ioctlsocket(escanear_socket, FIONBIO, &modo);

		sockaddr_in target;
		target.sin_family = AF_INET;
		target.sin_port = htons(i);
		inet_pton(AF_INET, ipDestino, &target.sin_addr);

		connect(escanear_socket, (sockaddr*)&target, sizeof(target));

		fd_set setEscritura;
		FD_ZERO(&setEscritura);
		FD_SET(escanear_socket, &setEscritura);

		// Estructura de tiempo para el limite de espera
		timeval timeout;
		timeout.tv_sec = 0;
		timeout.tv_usec = 15000;

		int seleccion = select(0, NULL, &setEscritura, NULL, &timeout);

		if (seleccion > 0)
		{
			array[j] = i;
			shutdown(escanear_socket, SD_BOTH);

			j += 1;
		}

		closesocket(escanear_socket);

	}
	*cant = j;

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


	for (int i = 0; i < n; i++)
	{
		printf(" %d ", *(array + i));
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