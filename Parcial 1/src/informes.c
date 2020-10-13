/*
 * informes.c
 *
 *  Created on: 10 oct. 2020
 *      Author: Silvia Rus Mata
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "cliente.h"
#include "publicacion.h"
#include "informes.h"
#include "getData.h"
#define LEN_CLIENTE 10
#define LEN_PUBLICACION 10
#define LEN_PUB 10

/* brief imprime el cliente asociado a una publicación cuyo Id entra por parámetro.
 * param array de publicaciones.
 * param longitud del array de publicaciones.
 * param array de clientes.
 * param longitud del array de publicaciones.
 * param el id de a publicación cuyo cliente asociado queremos encontrar.
 * return -1 si todo sale ok. 0 si ha habido un problema.
 */
int inf_printClientebyIdPublicacion(Publicacion *list, int len, Cliente *listCliente, int lenCliente, int idPub)
 {
	 int retorno = -1;
	 int idCliente;
	 int indexCliente;

	if(list!=NULL && len>0 &&
			 listCliente!=NULL &&
			 lenCliente>0 &&
			 idPub>0)
	 {
	 	for(int i=0; i<len;i++)
			{
				if(idPub==list[i].id)
				{
					idCliente=list[i].idCliente;
					indexCliente= cli_findById(listCliente,LEN_CLIENTE, idCliente);
					if(list[i].isEmpty == 0)
					{
						printf ("CLIENTE QUE CONTRATÓ EL AVISO:\n\n");
						printf("Id   "
								"Nombre         "
								"Apellido       "
								"CUIT           ");
						printf(	"\n%-5d"
								"%-15s"
								"%-15s"
								"%-15s\n\n ",
								listCliente[indexCliente].id,
								listCliente[indexCliente].nombre,
								listCliente[indexCliente].apellido,
								listCliente[indexCliente].cuit);
						retorno = 0;
						break;
					}
				}
			}
		}
	 return retorno;
 }
/* brief imprime las publicaciones asociadas por cliente cuyo Id entra por parámetro.
 * param array de clientes.
 * param longitud del array de clientes.
 * param array de publicaciones.
 * param longitud del array de publicaciones.
 * param el id del cliente cuyas publicaciones asociadas queremos encontrar.
 * return -1 si todo sale ok. 0 si ha habido un problema.
 */
int inf_printPublicacionbyIdCliente(Publicacion *list, int len ,Cliente *listCliente,int lenCliente, int idCliente)
{
	int retorno = -1;


		if (list != NULL && len > 0 && pub_isEmpty(list, len)==0)
		{
			printf("\nPUBLICACIONES DEL CLIENTE N°: %d \n",idCliente);
			printf("\nId   "
					"Rubro "
					"Texto          ");
			for (int i = 0; i < len; i++)
			{
				if(list[i].isEmpty == 0 && list[i].idCliente == idCliente)
				{
					printf(	"\n%-5d"
							"%-6d"
							"%-15s",
							list[i].id,
							list[i].rubro,
							list[i].textoAviso);
							retorno = 0;
					retorno = 0;
				}
			}
	    }
	return retorno;
}
/* brief imprime los datos de todos los clientes junto con el total de publicaciones activas que tiene cada uno de ellos..
 * param array de clientes.
 * param longitud del array de clientes.
 * param array de publicaciones.
 * param longitud del array de publicaciones.
 * return -1 si todo sale ok. 0 si ha habido un problema.
 */
int inf_printSumaAvisosActivosByCliente(Publicacion * listPublicacion, int lenPublicacion, Cliente* listClient, int lenClient)
{
	int retorno=-1;
	int contadorActivas = 0;
		if(listPublicacion != NULL && lenPublicacion > 0 && listClient != NULL && lenClient > 0)
		{	printf("ID   "
				"Nombre         "
				"Apellido       "
				"Cuit	        "
				"Pub. Activas");
			for(int i = 0; i< lenClient; i++)
			{
				if(listClient[i].isEmpty == 0)
				{
					pub_totalPubActivasByIdCliente(listPublicacion, lenPublicacion, listClient[i].id, &contadorActivas);
					printf("\n%-5d"
							"%-15s"
							"%-15s"
							"%-15s"
							"%-10d \n",
							listClient[i].id,
							listClient[i].nombre,
							listClient[i].apellido,
							listClient[i].cuit,
							contadorActivas);
				}
			}
			retorno = 0;
		}
		return retorno;
}
/* brief imprime el total de publicaciones pausadas que hay en el sistema.
 * param array de publicaciones.
 * param longitud del array de publicaciones.
 * return -1 si todo sale ok. 0 si ha habido un problema.
 */
int inf_printTotalPausadas(Publicacion * listPublicacion, int lenPublicacion)
{
	int retorno=-1;
	int totalPausadas;
		if(listPublicacion != NULL && lenPublicacion)
		{
			if(!pub_totalPausadas(listPublicacion, LEN_PUBLICACION, &totalPausadas))
			{
				printf("El total de publicaciones pausadas es: %d.", totalPausadas);
			}
		retorno = 0;
		}


		return retorno;
}
//PROBARLA MAÑANA
/* int inf_printClienteConMasAvisos(Publicacion * publicacionList, int publicacionLen, Cliente *clienteList, int clienteLen)
{
	int retorno=-1;
	int idClienteConMasAvisos;
	int index;
		if(clienteList!=NULL && clienteLen>0 && publicacionList!=NULL && publicacionLen>0)
		{	printf("aquí sí llega");
			if(!pub_clienteConMasAvisos(clienteList, clienteLen, publicacionList,publicacionLen, &idClienteConMasAvisos))
			{
				//cli_findById(Cliente* list,int len, int id)
				printf("y aquí????");
				cli_findById(clienteList, clienteLen, idClienteConMasAvisos)=index;
				printf("\nEl cliente con mas avisos es: %s %s, (CUIT: %s)", clienteList[index].nombre, clienteList[index].apellido, clienteList[index].cuit);
				retorno = 0;
			}

		}
		return retorno;
}

*/

//VER MAÑANA QUÉ ANDA MEJOR
int inf_clienteConMasAvisos(Cliente *clienteList, int clienteLen, Publicacion *publicacionList, int publicacionLen)
{
	int retornar=-1;
	int currentCounter;
	int maxCounter;
	int index;
	Cliente bufferMax;
	if(clienteList!=NULL && clienteLen>0 && publicacionList!=NULL && publicacionLen>0)
	{
		for(int i=0;i<clienteLen;i++)
		{
			pub_totalPubByIdCliente(publicacionList, publicacionLen, clienteList[i].id, &currentCounter);
			if(i==0 || currentCounter>maxCounter)
			{
				maxCounter = currentCounter;
				bufferMax = clienteList[i];
			}
		}
		index=cli_findById(clienteList, clienteLen, bufferMax.id);
		printf("\nEl cliente con mas avisos es: %s %s, CUIT: %s", clienteList[index].nombre, clienteList[index].apellido, clienteList[index].cuit);
		retornar = 0;

	}
	return retornar;
}

/* brief imprime el total de publicaciones pausadas que hay en el sistema.
 * param array de publicaciones.
 * param longitud del array de publicaciones.
 * return -1 si todo sale ok. 0 si ha habido un problema.
 */

int inf_rubroConMasAvisos(Publicacion *publicacionList, int publicacionLen, int banderaPrimeraCarga)
{
	int retorno = -1;
	int contadorFunebres = 0;//1
	int contadorInmuebles = 0;//2
	int contadorSociales = 0;//3

	if(banderaPrimeraCarga == 0)
	{
		printf("\nNO HAY PUBLICIDADES CARGADAS.\n");
	}
	else
	{
		for(int i=0;i< publicacionLen ;i++)
		{

			if(publicacionList[i].rubro==1)
			{
				contadorFunebres++;
			}
			else if(publicacionList[i].rubro==2)
			{
				contadorInmuebles++;
			}
			else if(publicacionList[i].rubro==3)
			{
				contadorSociales++;
			}
		}
	}

	if(contadorFunebres>contadorInmuebles && contadorFunebres >contadorSociales)
	{
		printf("\nEl rubro con más avisos es 'Funebres' (total %d).", contadorFunebres);
		retorno = 0;
	}
	else if(contadorInmuebles>contadorFunebres && contadorInmuebles>contadorSociales)
	{
		printf("\nEl rubro con más avisos es 'Inmuebles' (total %d).", contadorInmuebles);
		retorno = 0;
	}
	else if(contadorSociales>contadorFunebres && contadorSociales>contadorInmuebles)
	{
		printf("\n""El rubro con más avisos es 'Sociales' (total %d).", contadorInmuebles);
		retorno = 0;
	}

	return retorno;
}



