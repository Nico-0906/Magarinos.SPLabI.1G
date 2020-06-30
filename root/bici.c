#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"
#include "bici.h"
#include "herramientas.h"

eBicicleta* bicicleta_new()
{
    eBicicleta* pEmp;
    pEmp = (eBicicleta*) malloc(sizeof(eBicicleta));
    return pEmp;
}

int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
    char buffer[4][129];
    int error = 1;
    int scnVls;
    eBicicleta* auxEmp;
    FILE* txtFile;
    txtFile = fopen(path,"r");
    while(!feof(txtFile))
    {
        scnVls=fscanf(txtFile,"%[^,],%[^,],%[^,],%[^\n]\n",buffer[0],buffer[1],buffer[2],buffer[3]);
        if(scnVls==4)
        {
            auxEmp=bicicleta_new();
            auxEmp->id=atoi(buffer[0]);
            strcpy(auxEmp->nombre,buffer[1]);
            strcpy(auxEmp->tipo, buffer[2]);
            auxEmp->tiempo = atoi(buffer[3]);
            ll_add(pArrayListEmployee,auxEmp);
            error=0;
        }
    }
    fclose(txtFile);
    return error;
}

int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
    int isError = 1;
    eBicicleta* auxEmp;
    FILE* binFile;
    binFile = fopen(path,"rb");
    while(!feof(binFile))
    {
        auxEmp= bicicleta_new();
        fread(auxEmp,sizeof(eBicicleta),1,binFile);
        if(auxEmp->id!=0)
        {
            ll_add(pArrayListEmployee,auxEmp);
            isError=0;
        }
    }
    if(isError)
    {
        printf("ERROR! No se pudo cargar los datos del documento, es posible que\n");
        printf("el documento no exista o este dañado.\n");
    }
    else
    {
        printf("Datos cargados.\n");
    }
    fclose(binFile);

    return isError;
}

int controller_ListBicicletas(LinkedList* pArrayListEmployee)
{
    int length;
    int error = 1;
    eBicicleta* auxEmp;
    length = ll_len(pArrayListEmployee);
    if (length > 0)
    {
        printf("  ID           Nombre       Tipo     Tiempo\n\n");
        for(int i=0; i<length; i++)
        {
            auxEmp = (eBicicleta*) ll_get(pArrayListEmployee,i);
            bici_show(auxEmp);
        }
        error=0;
    }
    else
    {
        printf("\nNo hay bicicletas para mostrar. Primero deben cargarse.\n");
    }
    free(auxEmp);
    return error;
}

void bici_show(eBicicleta* this)
{
    if (this!=NULL)
    {
        printf(" %04d   %15s    %15s    %6d\n",this->id,this->nombre,this->tipo,this->tiempo);
    }
}

void generarListaFiltrada(LinkedList* lista, LinkedList* newLista, char* tipo){
	eBicicleta* aux;

	for(int i = 0 ; i < ll_len(lista) ; i++){
		aux = (eBicicleta*) ll_get(lista, i);
		if(aux != NULL){
			if(strcmp(aux->tipo, tipo) == 0){
				ll_add(newLista, aux);
			}
		}
	}
	free(aux);
}

void filtrarPorTipo(LinkedList* ListaBicicletas){
	int opcionFiltrado;

	LinkedList* newLista1 = ll_newLinkedList();
	LinkedList* newLista2 = ll_newLinkedList();
	LinkedList* newLista3 = ll_newLinkedList();
	LinkedList* newLista4 = ll_newLinkedList();

	system("cls");
	printf("****** Filtrar por tipo ******\n\n");
	printf("1-. BMX\n2-. PLAYERA\n3-. MTB\n4-. PASEO\n5-. SALIR");
	printf("\n\nIngrese el tipo que desea filtrar: ");
	scanf("%d", &opcionFiltrado);

	switch(opcionFiltrado){
	case 1:
		generarListaFiltrada(ListaBicicletas, newLista1, "BMX");
		guardarCSV(newLista1, "bicicletasFiltradas.csv");
		printf("\nArchivo de bicicletas filtradas creado con exito!");
		getchar();
		break;
	case 2:
		generarListaFiltrada(ListaBicicletas, newLista2, "PLAYERA");
		guardarCSV(newLista2, "bicicletasFiltradas2.csv");
		printf("\nArchivo de bicicletas filtradas creado con exito!");
		getchar();
		break;
	case 3:
		generarListaFiltrada(ListaBicicletas, newLista3, "MTB");
		guardarCSV(newLista3, "bicicletasFiltradas3.csv");
		printf("\nArchivo de bicicletas filtradas creado con exito!");
		getchar();
		break;
	case 4:
		generarListaFiltrada(ListaBicicletas, newLista4, "PASEO");
		guardarCSV(newLista4, "bicicletasFiltradas4.csv");
		printf("\nArchivo de bicicletas filtradas creado con exito!");
		getchar();
		break;
	case 5:
		break;
	}
}

int filtTipo(eBicicleta* this, eBicicleta* thistwo){
	int retorno = -1;
	if(strcmp(this->tipo, thistwo->tipo) < 0){
		retorno = 1;
	}
	return retorno;
}

int filtTiempo(eBicicleta* this, eBicicleta* thistwo){
	int retorno = -1;
	if(this->tiempo > thistwo->tiempo){
		retorno = 1;
	}
	return retorno;
}
