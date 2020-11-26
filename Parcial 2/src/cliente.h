/*
 * cliente.h
 *
 *  Created on: 22 nov. 2020
 *      Author: Silvia Rus Mata
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#define NOMBRE_LEN 128
#define APELLIDO_LEN 128
#define AUX_LEN 4095
#define CUIT_LEN 14

typedef struct
{
    int id;
    char nombre[NOMBRE_LEN];
    char apellido[APELLIDO_LEN];
    char cuit[CUIT_LEN];
}Cliente;

int cli_nuevoId(void);
int cliente_setId(Cliente* this,int id);
int cliente_setIdChar(Cliente* this, char* id);
int cliente_getId(Cliente* this,int* id);
int cliente_setNombre(Cliente* this,char* nombre);
int cliente_getNombre(Cliente* this,char* nombre);
int cliente_setApellido(Cliente* this,char* apellido);
int cliente_getApellido(Cliente* this,char* apellido);
int cliente_setCuit(Cliente* this,char* cuit);
int cliente_getCuit(Cliente* this,char* cuit);
Cliente* cliente_new();
int cliente_idMasAltoMasUno(LinkedList* this);
Cliente* cliente_newParametros(int id, char* nombreStr,char* apellidoStr,char* cuitStr);
Cliente* cliente_newParametrosChar(char* id, char* nombreStr,char* apellidoStr,char* cuitStr);
int cliente_print(void* this);
int cliente_existsId(void* this, void* id);
int cliente_existsCUIT(void* this, void* cuit);
int cliente_findIndexById(LinkedList* sellList, int id);



#endif /* CLIENTE_H_ */

