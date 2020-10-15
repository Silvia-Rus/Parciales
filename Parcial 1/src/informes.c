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
					indexCliente= cli_findById(listCliente, lenCliente, idCliente);
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
		else
		{
			retorno=0;
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
		if(listPublicacion != NULL && lenPublicacion > 0 && listClient != NULL && lenClient > 0 && cli_isEmpty(listClient, lenClient)==0)
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
							retorno = 0;
				}
			}

		}
		else
		{
			if(cli_isEmpty(listClient, lenClient)==1)
			{
				printf("No hay clientes grabados en la base de datos.");
			}
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
			if(pub_isEmpty(listPublicacion, lenPublicacion)==1)
			{
				printf("\nNo hay ninguna publicación en el sistema.");
			}
			else
			{
				if(!pub_totalPausadas(listPublicacion, lenPublicacion, &totalPausadas))
				{

				printf("\nEl total de publicaciones pausadas es: %d.", totalPausadas);
				}
			}
		retorno = 0;
		}
		return retorno;
}
/* brief imprime el cliente con más publicaciones.
 * param array de clientes.
 * param longitud del array de clientes.
 * param array de publicaciones.
 * param longitud del array de publicaciones.
 * return -1 si todo sale ok. 0 si ha habido un problema.
 */
int inf_clienteConMasAvisos(Cliente *clienteList, int clienteLen, Publicacion *publicacionList, int publicacionLen,
		int tipoInforme)//1 para las totales, 2 para las pausadas, 3 para las activas
{
	int retornar=-1;
	int contador;
	int contadorActivas;
	int contadorPausadas;
	int maximo;
	int maximoActivas;
	int maximoPausadas;
	int index;
	int indexPausadas;
	int indexActivas;
	Cliente buffer;
	//Cliente bufferPausadas;
	//Cliente bufferActivas;
	if(clienteList!=NULL &&
			clienteLen>0 &&
			publicacionList!=NULL &&
			publicacionLen>0 &&
			cli_isEmpty(clienteList, clienteLen)==0)
	{
		for(int i=0;i<clienteLen;i++)
		{
			pub_totalPubByIdCliente(publicacionList, publicacionLen, clienteList[i].id, &contador, &contadorPausadas, &contadorActivas);
			if(i==0 || contador>maximo)
			{
				maximo = contador;
				buffer = clienteList[i];
			}
			if(i==0 || contadorPausadas>maximoPausadas)
			{
				maximoPausadas = contadorPausadas;
				indexPausadas = i;
				//bufferPausadas = clienteList[indexPausadas];
			}
			if(i==0 || contadorActivas>maximoActivas)
			{
				maximoActivas = contadorActivas;
				indexActivas = i;
				//bufferActivas = clienteList[indexActivas];
			}
		}
		index=cli_findById(clienteList, clienteLen, buffer.id);
		if(tipoInforme==1)
		{
			printf("\nEl cliente con mas avisos es: %s %s, CUIT: %s", clienteList[index].nombre, clienteList[index].apellido, clienteList[index].cuit);
			retornar = 0;
		}
		else
		{
			if(tipoInforme==2)
			{
				printf("\nEl cliente con mas avisos activos es: %s %s, CUIT: %s", clienteList[indexActivas].nombre, clienteList[indexActivas].apellido, clienteList[indexActivas].cuit);
				retornar = 0;
			}
			else
			{
				if(tipoInforme==3)
				{
					printf("\nEl cliente con mas avisos pausados es: %s %s, CUIT: %s", clienteList[indexPausadas].nombre, clienteList[indexPausadas].apellido, clienteList[indexPausadas].cuit);
					retornar = 0;
				}

			}

		}

	}
	else
	{
		if(cli_isEmpty(clienteList, clienteLen)==1)
		{
			printf("No hay clientes grabados en la base de datos.");
		}
	}
	return retornar;
}

/* brief imprime el rubro con más avisos en el sistema
 * param array de publicaciones.
 * param longitud del array de publicaciones.
 * return -1 si todo sale ok. 0 si ha habido un problema.
 */
int inf_rubroConMasAvisos(Publicacion *publicacionList, int publicacionLen)
{
	int retorno = -1;
	int contadorFunebres = 0;//1
	int contadorInmuebles = 0;//2
	int contadorSociales = 0;//3

	if(pub_isEmpty(publicacionList, publicacionLen)==1)
	{
		printf("\nNo hay publicaciones cargadas.\n");
	}
	else
	{
		for(int i=0;i< publicacionLen;i++)
		{

			if(publicacionList[i].isEmpty == 0)
			{
				switch(publicacionList[i].rubro)
				{
					case 1:
						contadorFunebres++;
						break;
					case 2:
						contadorInmuebles++;
						break;
					case 3:
						contadorSociales++;
						break;
				}
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
		printf("\n""El rubro con más avisos es 'Sociales' (total %d).", contadorSociales);
		retorno = 0;
	}

	else if((contadorFunebres==contadorInmuebles) && contadorFunebres >contadorSociales)
	{
		printf("\nLos rubros con más avisos son 'Funebres' e 'Inmuebles' (total %d).", contadorFunebres);
		retorno = 0;
	}
	else if((contadorFunebres==contadorSociales) && contadorFunebres >contadorInmuebles)
	{
		printf("\nLos rubros con más avisos son 'Funebres' y 'Sociales' (total %d).", contadorFunebres);
		retorno = 0;
	}
	else if((contadorInmuebles==contadorSociales) && contadorInmuebles >contadorFunebres)
	{
		printf("\nLos rubros con más avisos son 'Inmuebles' y 'Sociales' (total %d).", contadorFunebres);
		retorno = 0;
	}
	else if((contadorInmuebles==contadorSociales) && (contadorSociales==contadorFunebres))
	{
		printf("\nLos tres rubros tienen el mismo número de avisos (total %d).", contadorInmuebles);
		retorno = 0;
	}
	return retorno;
}





