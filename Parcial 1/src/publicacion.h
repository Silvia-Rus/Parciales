/*
 * publicacion.h
 *
 *  Created on: 10 oct. 2020
 *      Author: usuario
 */

#ifndef PUBLICACION_H_
#define PUBLICACION_H_
#include "cliente.h"
#define AVISO_LEN 64
struct
{
	int id;
	int rubro;
	char textoAviso[AVISO_LEN];
	int estado;//1 para activa - 0 para pausada
	int isEmpty;
	int idCliente;
}typedef Publicacion;

int pub_initList(Publicacion* list, int len);
int pub_indiceVacio(Publicacion *list, int len, int *pIndiceLibre);
int pub_isEmpty(Publicacion *list, int len);
int pub_findById(Publicacion* list,int len, int id);
int pub_altaRegistro(Publicacion *list,int len, Cliente *clienteList, int clienteLen);
int pub_printList(Publicacion* list, int len);
int pub_pausarActivarPublicacion(Publicacion *list, int len, Cliente *listCliente, int lenCliente, int pausa);
int pausarActivar (Publicacion *list, int len, int id, int pausa);
int pub_bajaByIdCliente(Publicacion *list, int len, int idCliente);
int pub_totalPubByIdCliente(Publicacion * listPublicacion, int lenPublicacion, int idCliente, int *pTotalPublicaciones, int *pTotalPausadas, int *pTotalActivas);
int pub_totalPausadas(Publicacion * listPublicacion, int lenPublicacion, int *pTotalPubPausadas);
int pub_clienteConMasAvisos(Cliente *clienteList, int clienteLen, Publicacion *publicacionList, int publicacionLen, int *pIdClienteConMasAvisos);
int pub_totalPubActivasByIdCliente(Publicacion * listPublicacion, int lenPublicacion, int idCliente, int *pTotalPubActivas);
void pub_cargaAutomatica(Publicacion *list);


#endif /* PUBLICACION_H_ */
