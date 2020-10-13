/*
 * publicacion.c
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


#define LEN_NOMBRE 30
#define LEN_STRUCT 1000
#define LEN_CLIENTE 100
#define INTENTOS 3


static int pub_nuevoId(void);

/*
* \brief To indicate that all position in the array are empty, this function put the flag (isEmpty) in TRUE in all position of the array
* \param list Employee* Pointer to array of employees
* \param len int Array length
* \return return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int pub_initList(Publicacion* list, int len)
{
	int retorno=-1;
	if (list != NULL && len > 0)
	{
			for (int i = 0; i <len; i++)
			{
				list[i].id = -1;
				list[i].isEmpty = 1;
			}
			retorno = 0;
	}
	return retorno;
}
/*
* \brief genera identificadores únicos autoincrementales.
* \return el identificador único autoincremental generado.
*/
static int pub_nuevoId(void)
{
	static int id = 0;
	id = id + 1;
	return id;
}
/*
* \brief busca una posición en la memoria que tenga isEmpty en TRUE. Se usa para crear nuevos registros.
* \param puntero al array en el que busca la posición.
* \param longitud del array en el que busca la posición.
* \param puntero con la posición en la memoria que tiene isEmpty en TRUE.
* \return devuelve 0 si todo ok (list no apunta a null y encuentra un lugar en vacío en el array).
*/
int pub_indiceVacio(Publicacion *list, int len, int *pIndiceLibre)
{
	int retorno = -1;

	if (list != NULL)
	{
		for (int i = 0; i < len; i++)
		{
			if (list[i].isEmpty ==1)
			{
				*pIndiceLibre = i;
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/*
* \brief comprueba que hay por lo menos un elemento cargado en el array.
* 		 Se usa en lugar de una banera para acceder a las opciones de modificación.
* \param puntero al array que comprueba.
* \param longitud del array que comprueba.
* \return 1 si el array está vacío (todos sus elementos tienen iseEmpty en FALSE) y 0 si no lo está.
 */
int pub_isEmpty(Publicacion *list, int len)
{
	int retorno = 1;
	if(list != NULL && len > 0)
	{
		for(int i=0; i<len; i++)
		{
			if(list[i].isEmpty == 0)
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
/*
* \brief devuelve el lugar de la memoria en el que está un id introducido por parámetro.
* \param puntero a la lista de publicaciones.
* \param longitud del array.
* \param id a buscar.
* \return devuelve la posición de la memoria en la que está el ID o menor a 0 si no existe ese id en la memoria.
* 	      No devuelve resultado si el registro está marcado como vacío.
*/
int pub_findById(Publicacion* list,int len, int id)
{
	int retorno = -1;

	if(list!=NULL && len > 0 && id > 0)
	{
		for(int i=0; i<len;i++)
		{
			if(list[i].id==id && list[i].isEmpty == 0)
			{
				retorno=i;
				break;

			}else{retorno= -2;}
		}
	}
	return retorno;
}
/*
* \brief pausa o activa una publicación según lo introducido por parámtero.
* \param puntero al array que se imprime.
* \param longitud del array que se imprime.
* \param id del registro a modificar.
* \param el parámetro para saber si pausamos o activamos  el registro que entró por id.
*         (1 para pausar, 0 para activar)
* \return devuelve 0 si todo ok (list no apunta a null y encuentra un lugar en vacío en el array).
*/
int pausarActivar (Publicacion *list, int len, int id, int pausa)
{
	int retorno=-1;

	if(list != NULL && len>0 && id>0 && pausa >-1 && pausa<2)
	{
		for(int i=0; i<len; i++)
		{
			if(list[i].id == id)
			{
				if(pausa==1)
				{
					if(list[i].estado == 1)
					{
					list[i].estado = 0;
					retorno = 0;
					}
				}
				else
				{
					if(list[i].estado == 0)
					{
						list[i].estado = 1;
						retorno = 0;
					}
				}
				break;
			}
		}
	}
	return retorno;
}
/*
* \brief imprime una tabla.No imprime los registros marcados como vacíos.
* \param puntero al array que se imprime.
* \param longitud del array que se imprime.
* \return -1 si da error (puntero a nulo o longitud incorrecta) o 0 si sale bien.
*/
int pub_printList(Publicacion* list, int len)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		for(int i=0;i< len ;i++)
		{
			if(list[i].isEmpty == 0)
			{

				printf(
						"Id: %d. "
						"Rubro: %d. "
						"TextoAviso: %s. "
						"Estado: %d. "
						"isEmpty: %d. "
						"IdCliente: %d.\n",
						list[i].id,
						list[i].rubro,
						list[i].textoAviso,
						list[i].estado,
						list[i].isEmpty,
						list[i].idCliente);
			}
		}
		retorno = 0;
	}
	return retorno;
}

/**
 * \brief Función para ordenar por características. Se recibe por parámetro si es ascendente o descentente.
 * \param puntero al array que se quiere ordenar.
 * \param longitud al array que se quiere ordenar.
 * \param se recibe el orden en el que se quiere que se muestren los resultados (1 para ascendente y 0 para descendente)
 * \return -1 si algo fue mal, 0 si fue todo bien.

int sort(Publicacion *list, int len, int order)
{
	int retorno = -1;
		Publicacion auxSwap;
		int flagSwap;
		if(list != NULL && len > 0 && (order == 1 || order == 0))
		{
			do
			{
				flagSwap = 0;
				for(int i=0; i<len-1; i++)
				{
					if((order == 1 && //ASC
						//Comparar cadenas de caracteres
						((strncmp(list[i].nombre, list[i+1].nombre, LEN_NOMBRE) > 0) ||
						(strncmp(list[i].nombre, list[i+1].nombre, LEN_NOMBRE) == 0 &&
						//Comparar enteros
						list[i].id > list[i+1].id))) ||
						(order == 0 && //DESC
						( (strncmp(list[i].nombre, list[i+1].nombre, LEN_NOMBRE) < 0) ||
						(strncmp(list[i].nombre, list[i+1].nombre, LEN_NOMBRE) == 0 &&
						list[i].id < list[i+1].id))))
					{
						auxSwap = list[i];
						list[i] = list[i+1];
						list[i+1] = auxSwap;
						flagSwap = 1;
						retorno = 0;
					}
				}
			}while(flagSwap);
		}
		return retorno;;
}
 */
//FUNCIONES DE PRIMER NIVEL
/*
 * \brief pide el ID de un cliente para publicar un aviso relacionado a él.
 * 			Valida que el cliente exista antes de pedir los datos de la publicación.
 * 			Graba la publicación y devuelve por pantalla el ID de la publicación.
 * \param puntero a la lista de publicaciones.
 * \param longitud de la lista de la publicaciones.
 * \param puntero a la lista de clientes.
 * \param longitud de la lista de clientes.
 * \return -1 si algo fue mal, 0 si fue todo bien.
*/

int pub_altaRegistro(Publicacion *list,int len, Cliente *clienteList, int clienteLen)
{
	int retorno = -1;
	Publicacion buffer;
	int idCliente=INT_MAX;
	int i;

	if(list!=NULL && len>0 && clienteList!=NULL && clienteLen>0)
	{
		do
		{
			if(!utn_getNumeroInt(&idCliente,
									"\nIngrese el ID de un cliente para publicar un aviso o pulse 0 para ir al menú principal:",
									"\nError. Ingrese un número entero o pulse 0 para salir.",
									0,
									INT_MAX,
									INTENTOS) &&
				(cli_findById(clienteList, clienteLen, idCliente)>-1))
			{
				if(!pub_indiceVacio(list, LEN_STRUCT,&i) &&
					i >= 0  && list[i].isEmpty==1 &&
					!utn_getNumeroInt(&buffer.rubro,
										"\nRubro:"
										"\n-->1-Funebres"
										"\n-->2-Inmuebles"
										"\n-->3-Sociales\n",
										"\nError. Ingrese un número de rubro",
										1,
										3,
										INTENTOS) &&
				!utn_getCadena(buffer.textoAviso,
										LEN_NOMBRE,
										"\nTexto del aviso: ",
										"\nError. Introduzca solo letras y espacios.",
										INTENTOS))
				{
					buffer.id =pub_nuevoId();
					buffer.isEmpty=0;
					buffer.estado=1;
					buffer.idCliente=idCliente;
					list[i]= buffer;
					retorno=0;
					printf("\nAviso cargado con éxito. (ID: %d)\n", list[i].id);
					break;
				}
			}
			else
			{
				if(cli_findById(clienteList, clienteLen, idCliente)<-1)
				{
					printf("El ID no está en la base de datos.\n");
				}
			}
		}while(idCliente!=0);
	}
	return retorno;
}
/*
 * \brief pausa o activa una publicacion según valor introducido por parámetro.
 * \param puntero a la lista de publicaciones
 * \param longitud de la lista de la publicaciones.
 * \param puntero a la lista de clientes.
 * \param longitud de la lista de clientes.
 * \param el parámetro para saber si pausamos o activamos  el registro que entró por id.
 *         (1 para pausar, 0 para activar)
 * \return -1 si algo fue mal, 0 si fue todo bien.
 */
int pub_pausarActivarPublicacion(Publicacion *list, int len, Cliente *listCliente, int lenCliente, int pausa)
{
	 int retorno = -1;
	 int idPublicacion;
	 int indexPublicacion;
	 int confirmacion;
	 int estadoPublicacion;

	if(list!=NULL && len>1 && listCliente!=NULL && lenCliente>1 && pausa>-1 && pausa<2)
	{
		 if (!utn_getNumeroInt(&idPublicacion,
								"\nIngrese el ID de la publicación o 0 para salir. ",
								"\nError. El ID debe ser númerico.: ",
								0,
								INT_MAX,
								INTENTOS) &&
			pub_findById(list,LEN_STRUCT, idPublicacion)>-1)

		 {
			if(idPublicacion!=0)
			{
			 indexPublicacion=pub_findById(list,LEN_STRUCT, idPublicacion);
				estadoPublicacion=list[indexPublicacion].estado;

				do
				{
					if(estadoPublicacion == pausa &&
						!inf_printClientebyIdPublicacion(list,
														LEN_STRUCT,
														listCliente,
														LEN_CLIENTE,
														idPublicacion) &&
						((pausa==1 &&
						!utn_getNumeroInt(&confirmacion, //la pregunta de confirmación
									"\n¿Está seguro de que quiere pausar la publicación?\n"
									"Pulse 0 para salir. Pulse 1 para confirmar.\n",
									"\nERROR. Pulse 0 para salir. Pulse 1 para confirmar. : ",
									0,
									1,
									INTENTOS))  ||
						(pausa==0 &&
						!utn_getNumeroInt(&confirmacion, //la pregunta de confirmación
									"\n¿Está seguro de que quiere activar la publicación?\n"
									"Pulse 0 para salir. Pulse 1 para confirmar.\n",
									"\nERROR. Pulse 0 para salir. Pulse 1 para confirmar. : ",
									0,
									1,
									INTENTOS))) &&
						confirmacion==1 &&
						!pausarActivar(list, LEN_STRUCT, idPublicacion, pausa))
					{

							retorno=0;
							printf("\nModificacion realizada con éxito.");
							idPublicacion=0;
							confirmacion=0;
					}
					else
					{
						if(estadoPublicacion != pausa && idPublicacion!=0 )
						{
							if(pausa==1)
							{
								printf("\nEl aviso ya está pausado.");
								confirmacion=0;
							}
							else
							{
								printf("\nEl aviso ya está activo.");
								confirmacion=0;
							}
						}
					}
				}while(confirmacion!=0);
			}
		 }
		 else
		 {
			 if(idPublicacion==0)
			 {
				printf("Volviendo a menú principal...");
			 }
			 else
			 {
				 printf("No existe ningúna publicación con ese ID en la base de datos.\n\n");
			 }
		 }
	}
	return retorno;
}
/*
* \brief se dan de baja todas las publicaciones de un cliente cuyo id entra por puntero.
* \param puntero a la lista de publicaciones
* \param longitud de la lista de la publicaciones.
* \param el id del cliente cuyas publicaciones queremos dar de baja.
* \return -1 si algo fue mal, 0 si fue todo bien.
*/
int pub_bajaByIdCliente(Publicacion *list, int len, int idCliente)
{
	int idABuscar;
	int indiceAModificar;
	int retorno = -1;
	if (list != NULL &&
			len > 0 &&
			!pub_isEmpty(list, len))
	{
		do{

			for(int i=0; i<len;i++)//recorremos el array de publicaciones
			{
				if(list[i].idCliente==idCliente)
				{
					idABuscar= list[i].id;
					indiceAModificar=pub_findById(list, LEN_STRUCT, idABuscar);
					if(indiceAModificar!=-1)
					{
						list[indiceAModificar].isEmpty=1;
						retorno=0;
					}
					else
					{
						printf("ID inválido");
					}
				}
			}
			}while(retorno==-1);
	}else{printf("Error.\n");}
	return retorno;
}
/*
* \brief suma de las publicaciones activas de un cliente cuyo id entra por parámetro.
* \param puntero a la lista de publicaciones
* \param longitud de la lista de la publicaciones.
* \param id del cliente del cual queremos contar las publicaciones activas.
* \param puntero con el total de publicaciones activas del cliente.
* \return -1 si algo fue mal, 0 si fue todo bien.
 */
int pub_totalPubActivasByIdCliente(Publicacion * listPublicacion, int lenPublicacion, int idCliente, int *pTotalPubActivas)
{
	int retorno= -1;
	int contadorActivas = 0;
	if(listPublicacion != NULL && lenPublicacion > 0 && idCliente> -1 && pTotalPubActivas != NULL)
	{
		for(int i = 0; i< lenPublicacion; i++)
		{
			if(listPublicacion[i].isEmpty == 0 && listPublicacion[i].estado == 1 && listPublicacion[i].idCliente == idCliente)
			{
				contadorActivas++;
			}
		}
		*pTotalPubActivas = contadorActivas;
		retorno = 0;
	}
	return retorno;
}
/*
* \brief suma de todas las publicaciones de un cliente cuyo id entra por parámetro.
* \param puntero a la lista de publicaciones
* \param longitud de la lista de la publicaciones.
* \param id del cliente del cual queremos contar las publicaciones.
* \param puntero con el total de publicaciones del cliente.
* \return -1 si algo fue mal, 0 si fue todo bien.
 */
int pub_totalPubByIdCliente(Publicacion * listPublicacion, int lenPublicacion, int idCliente, int *pTotalPublicaciones)
{
	int retorno= -1;
	int contadorPublicaciones = 0;
	if(listPublicacion != NULL && lenPublicacion > 0 && idCliente> -1 && pTotalPublicaciones != NULL)
	{
		for(int i = 0; i< lenPublicacion; i++)
		{
			if(listPublicacion[i].isEmpty == 0 && listPublicacion[i].idCliente == idCliente)
			{
				contadorPublicaciones++;
			}
		}
		*pTotalPublicaciones = contadorPublicaciones;
		retorno = 0;
	}
	return retorno;
}
/*
* \brief suma de todas las publicaciones pausadas que hay en la base de datos..
* \param puntero a la lista de publicaciones
* \param longitud de la lista de la publicaciones.
* \param puntero con el total de publicaciones pausadas.
* \return -1 si algo fue mal, 0 si fue todo bien.
 */
int pub_totalPausadas(Publicacion * listPublicacion, int lenPublicacion, int *pTotalPubPausadas)
{
	int retorno= -1;
	int contadorPausadas = 0;
	if(listPublicacion != NULL && lenPublicacion > 0 && pTotalPubPausadas != NULL)
	{
		for(int i = 0; i< lenPublicacion; i++)
		{
			if(listPublicacion[i].isEmpty == 0 && listPublicacion[i].estado == 0)
			{
				contadorPausadas++;
			}
		}
		*pTotalPubPausadas = contadorPausadas;
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief calcula cuál es el cliente con más avisos (activos o no) en la base de datos.
 * \param puntero a la lista de clientes.
 * \param longitud de la lista de clientes.
 * \param puntero a la lista de publicaciones
 * \param longitud de la lista de la publicaciones.
 * * \return -1 si algo fue mal, 0 si fue todo bien.
 */
//PROBARLA
/*int pub_clienteConMasAvisos(Cliente *clienteList, int clienteLen, Publicacion *publicacionList, int publicacionLen, int *pIdClienteConMasAvisos)
{
	int retorno=-1;
	int totalPorCliente;
	int totalMasAlto;
	Cliente bufferCliente;
	int bufferClienteConMasAvisos;
	if(clienteList!=NULL && clienteLen>0 && publicacionList!=NULL && publicacionLen>0)
	{
		for(int i=0;i<clienteLen;i++)
		{
			pub_totalPubByIdCliente(publicacionList,publicacionLen, clienteList[i].id, &totalPorCliente);
			if(i==0 || totalPorCliente>totalMasAlto)
			{
				totalMasAlto = totalPorCliente;
				bufferCliente = clienteList[i];
				bufferClienteConMasAvisos=bufferCliente.id;
				retorno=0;
			}
		}
	}
	*pIdClienteConMasAvisos=bufferClienteConMasAvisos;
	return retorno;
}
*/
/*
 * \brief carga datos de manera automática para debuguear.
 * \param puntero a la lista de publicaciones
 * \return los datos cargados.
 */

/*void pub_cargaAutomatica(Publicacion *list)
{
	    list[0].id = (pub_nuevoId);
	    list[0].rubro = 1;
strncpy(list[0].textoAviso,"PUBLICACION",LEN_NOMBRE);
		list[0].estado = 1;
	    list[0].isEmpty = 0;
	    list[0].idCliente = 1;

	    list[1].id = (pub_nuevoId);
	    list[1].rubro = 1;
strncpy(list[1].textoAviso,"PUBLICACION2",LEN_NOMBRE);
		list[1].estado = 1;
	    list[1].isEmpty = 0;
	    list[1].idCliente = 1;

	    list[2].id = (pub_nuevoId);
	    list[2].rubro = 1;
strncpy(list[2].textoAviso,"PUBLICACION3",LEN_NOMBRE);
		list[2].estado = 1;
	    list[2].isEmpty = 1;
	    list[2].idCliente = 2;
}
*/






