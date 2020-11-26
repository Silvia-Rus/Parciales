/*
 * Controller.h
 *
 *  Created on: 22 nov. 2020
 *      Author: usuario
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#define AFICHE_LEN 4096
#define INTENTOS 3


int controller_addCliente(LinkedList* pArrayListCliente);
int controller_addVenta(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente);


int controller_loadFromText(char* path , LinkedList* pArrayListCliente, int (*pFuncParseo)(FILE *, LinkedList *));
int controller_print(LinkedList* pArrayList, int (*pFuncListado)(void*));
int controller_modifyVenta(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente, int operacion);

int controller_saveVentaAsText(char* path , LinkedList* pArrayListCliente);
int controller_saveClienteAsText(char* path , LinkedList* pArrayListCliente);



#endif /* CONTROLLER_H_ */
