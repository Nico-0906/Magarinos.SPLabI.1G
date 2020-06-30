#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "LinkedList.h"
#include "herramientas.h"
#include "bici.h"


int getRandom(int desde, int hasta){
	int aleatorio = 50;
	aleatorio = rand()% hasta + desde;  // minimo 50 maximo 70 + 50

	return aleatorio;
}

int menuOpciones(void){
	int opcion;
	system("cls");

	printf("******  MENU DE OPCIONES ******\n\n");
	printf("1. Cargar archivo \n");
	printf("2. Imprimir lista \n");
	printf("3. Asignar tiempos\n");
	printf("4. Filtrar por tipo\n");
	printf("5. Mostrar posiciones\n");
	printf("6. Guardar posiciones\n");
	printf("7. Salir\n");
	printf("Ingrese opcion: ");

	scanf("%d", &opcion);
	return opcion;
}


int h_getName(char* nombre, int tam)
{
	int error = 1;
    char aux[tam];
    if(!h_fgets(aux, tam)){
        strcpy(nombre, aux);
    	error = 0;
    }

    return error;
}

int h_fgets(char* cadena, int tam)
{
	int error = 1;
    char aux[tam];
    int i = 0;
    fgets(aux,tam,stdin);
    if(cadena != NULL && tam > 0){
    	while(aux[i] != '\n'){
    			cadena[i] = aux[i];
    			i++;
    			error = 0;
    	}
    }
    return error;
}

int guardarCSV(LinkedList *lista, char *path){
	FILE* f;
	int error = 1;
	f = fopen(path, "w");
	eBicicleta* bici;

	int id;
	char nombre[150];
	char tipo[20];
	int tiempo;
	int tam;

	if(lista != NULL){

		tam = ll_len(lista);

		for(int i = 0 ; i < tam ; i++){
			bici = (eBicicleta*) ll_get(lista, i);
			id = bici->id;
			strcpy(nombre, bici->nombre);
			strcpy(tipo, bici->tipo);
			tiempo = bici->tiempo;
			fprintf(f, "%d,%s,%s,%d\n", id, nombre, tipo, tiempo);
		}
		error = 0;
	}
	free(bici);
	fclose(f);

	return error;

}
