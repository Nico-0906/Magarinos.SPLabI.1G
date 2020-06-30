#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "LinkedList.h"
#include "utn.h"
#include "herramientas.h"
#include "bici.h"

int main(void)
{
	srand(time(NULL));

	int opcion;
	char confirm;
	char archivo[30] = {'\n'};
	int binotext;

	LinkedList* ListaBicicletas = ll_newLinkedList();
	LinkedList* auxLista = ll_newLinkedList();

	do
	{
		opcion = menuOpciones();
		fflush(stdin);

		switch (opcion)
		{
		case 1:
			printf("\nIngrese archivo que desea cargar ej. bicicletas.csv : ");
			h_fgets(archivo, 30);
			printf("\nIngrese 1 si es texto o 2 si es binario: ");
			scanf("%d", &binotext);
			if(binotext == 1){
				if (!controller_loadFromText(archivo, ListaBicicletas))
				{
					printf("\nDatos cargados con exito!\n");
					getchar();
				}
			}else if(binotext == 2){
				if(!controller_loadFromBinary(archivo, ListaBicicletas)){
					printf("\nDatos cargados con exito!\n");
					getchar();
				}
			}else{
				printf("\nOPCION INCORRECTA");
				getchar();
			}

			getchar();

			break;
		case 2:
			controller_ListBicicletas(ListaBicicletas);
			getchar();
			break;
		case 3:
			//ll_map(ListaBicicletas, getRandom);
			printf("\nTiempo asignado a las bicicletas!");
			getchar();
			break;
		case 4:
			filtrarPorTipo(ListaBicicletas);
			getchar();
			break;
		case 5:
			auxLista = ll_clone(ListaBicicletas);
			ll_sort(auxLista, filtTipo, 1);
			controller_ListBicicletas(auxLista);
			getchar();
			break;
		case 6:
			printf("\nDesea generar el archivo listaFiltrada.csv? s/n: ");
			scanf("%c", &confirm);
			fflush(stdin);
			if(confirm == 's' || confirm == 'S'){
				if(!guardarCSV(auxLista, "listaFiltrada.csv")){
					printf("\nGuardado de archivo con exito!");
					getchar();
				}else{
					printf("\nNo se pudo guardar el archivo.");
					getchar();
				}
			}else if(confirm == 'n' || confirm == 'N'){
				printf("\nCancelado.");
				getchar();
			}
			break;
		case 7:
			printf("\nSeguro que desea salir? s/n : ");
			scanf("%c", &confirm);
			fflush(stdin);
			if (confirm == 's' || confirm == 'S')
			{
				break;
			}
			else if (confirm == 'n' || confirm == 'N')
			{
				opcion = 0;
			}
			else
			{
				printf("\nOpcion incorrecta.");
				getchar();
				opcion = 0;
				break;
			}
		}
	} while (opcion != 7);

	getchar();
	return EXIT_SUCCESS;
}

