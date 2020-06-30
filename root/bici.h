/*
 * bici.h
 *
 *  Created on: 29 jun. 2020
 *      Author: Nico
 */

#ifndef BICI_H_
#define BICI_H_

typedef struct{
	int id;
	char nombre[100];
	char tipo[20];
	int tiempo;
}eBicicleta;

#endif /* BICI_H_ */

eBicicleta* bicicleta_new();
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee);
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee);
int controller_ListBicicletas(LinkedList* pArrayListEmployee);
void bici_show(eBicicleta* this);
void generarListaFiltrada(LinkedList* lista, LinkedList* newLista, char* tipo);
void filtrarPorTipo(LinkedList* ListaBicicletas);
int filtTipo(eBicicleta* this, eBicicleta* thistwo);
int filtTiempo(eBicicleta* this, eBicicleta* thistwo);
