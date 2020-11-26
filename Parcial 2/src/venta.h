/*
 * venta.h
 *
 *  Created on: 22 nov. 2020
 *      Author: Silvia Rus Mata
 */

#ifndef VENTA_H_
#define VENTA_H_

#define AFICHE_LEN 4096
#define INTENTOS 3

typedef struct
{
    int id;
    int idCliente;
    int cantidadAfiches;
    char nombreAfiche[AFICHE_LEN];
    int zona;
    int cobrado;
}Venta;

int venta_setId(Venta* this,int id);
int venta_setIdChar(Venta* this, char* id);
int venta_getId(Venta* this,int* id);
int venta_setIdCliente(Venta* this,int idCliente);
int venta_setIdClienteChar(Venta* this, char* idCliente);
int venta_getIdCliente(Venta* this,int* idCliente);
int venta_setCantidadAfiches(Venta* this,int cantidadAfiches);
int venta_setCantidadAfichesChar(Venta* this, char* cantidadAfiches);
int venta_getCantidadAfiches(Venta* this,int* cantidadAfiches);
int venta_setNombreAfiche(Venta* this,char* nombreAfiche);
int venta_getNombreAfiche(Venta* this,char* nombreAfiche);
int venta_setZona(Venta* this,int zona);
int venta_setZonaChar(Venta* this, char* zona);
int venta_getZona(Venta* this,int* zona);
int venta_setCobrado(Venta* this,int cobrado);
int venta_setCobradoChar(Venta* this, char* cobrado);
int venta_getCobrado(Venta* this,int* cobrado);
int venta_idMasAltoMasUno(LinkedList* this);
Venta* venta_newParametros(int id, int idCliente, int cantidadAfiches, char* nombreAfiche, int zona, int cobrado);
Venta* venta_newParametrosChar(char* id, char* idCliente,char* nombreAfiche,char* cantidadAfiches, char* zona, char* cobrado);
int venta_print(void* this);
int venta_estaCobrada(void* this);

int venta_noEstaCobrada(void* this);
int venta_findIndexById(LinkedList* sellList, int id);
//int venta_modify(Venta* this, int indexVenta, int idVenta);
int venta_modify(Venta* this);
int venta_delete(Venta* this);
int venta_existsIdCliente(void* this, void* id);

Venta* venta_new();
int venta_nuevoId(void);


#endif /* VENTA_H_ */
