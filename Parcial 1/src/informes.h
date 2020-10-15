/*
 * informes.h
 *
 *  Created on: 10 oct. 2020
 *      Author: usuario
 */

#ifndef INFORMES_H_
#define INFORMES_H_
#include "cliente.h"
#include "publicacion.h"

int inf_printClientebyIdPublicacion(Publicacion *list, int len, Cliente *listCliente, int lenCliente, int idPub);
int inf_printPublicacionbyIdCliente(Publicacion *list, int len ,Cliente *listCliente,int lenCliente, int idCliente);
int inf_printSumaAvisosActivosByCliente(Publicacion * listPublicacion, int lenPublicacion, Cliente* listClient, int lenClient);
int inf_printTotalPausadas(Publicacion * listPublicacion, int lenPublicacion);
int inf_printClienteConMasAvisos(Publicacion * publicacionList, int publicacionLen, Cliente *clienteList, int clienteLen);
int info_clientWithMaxAdQty(Cliente *clienteList, int clienteLen, Publicacion *publicacionList, int publicacionLen);
int inf_rubroConMasAvisos(Publicacion *publicacionList, int publicacionLen);
int inf_clienteConMasAvisos(Cliente *clienteList, int clienteLen, Publicacion *publicacionList, int publicacionLen, int tipoInforme);

#endif /* INFORMES_H_ */
