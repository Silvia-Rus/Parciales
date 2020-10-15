/*
 * cliente.h
 *
 *  Created on: 10 oct. 2020
 *      Author: usuario
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#define LEN_CUIT 14
#define LEN_NOMBRE 100

struct
{
	int id;
	char nombre[LEN_NOMBRE];
	char apellido[LEN_NOMBRE];
	char cuit [LEN_CUIT];
	int isEmpty;
}typedef Cliente;

int cli_initList(Cliente* list, int len);
int cli_indiceVacio(Cliente *list, int len, int *pIndiceLibre);
int cli_isEmpty(Cliente *list, int len);
int cli_findById(Cliente* list,int len, int id);
int cli_printList(Cliente* list, int len);
//int sort(Cliente *list, int len, int order);
int cli_altaRegistro(Cliente *list,int len);
int cli_modify(Cliente *list, int len);
int cli_bajaById(Cliente *list, int len, int idCliente);
void cli_cargaAutomatica(Cliente *list);



#endif /* CLIENTE_H_ */
