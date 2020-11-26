/*
 * informes.c
 *
 *  Created on: 26 nov. 2020
 *      Author: Silvia Rus Mata
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "getData.h"
#include "LinkedList.h"
#include "Controller.h"
#include "cliente.h"
#include "venta.h"
#include "parser.h"
/*
 * \brief Guarda en un archivo informes sobre ventas y deudas.
 * \param puntero a LinkedList.
 * \param puntero a LinkedList.
 * \param funci�n criterio (venta o deuda).
 * \param nombre del archivo:
 * \return 0 si modific� con �xito. -1 si ha habido alg�n problema.
*/
int informes_informeCobradas(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente, int (pFunc)(void*),char* nombreArchivo)
{
	int retornar=-1;
	Cliente* bufferCliente;
	FILE* pFile;
	LinkedList* listaEstadoCobro;
	int contador=1;
	int bufferId;
	char bufferNombre[4096];
	char bufferApellido[4096];
	char bufferCuit[4096];
	if(pArrayListVenta!=NULL && pArrayListCliente!=NULL)
	{
		listaEstadoCobro = ll_filter(pArrayListVenta, pFunc);
		pFile = fopen(nombreArchivo, "w");
		if(pFile!=NULL)
		{
			fprintf(pFile, "id,nombre,apellido,cuit,ventas_a_cobrar\n");

			for(int i=0;i<ll_len(pArrayListCliente);i++)
			{

				bufferCliente = ll_get(pArrayListCliente, i);

				if(!cliente_getId(bufferCliente, &bufferId) &&
				   !cliente_getNombre(bufferCliente, bufferNombre) &&
				   !cliente_getApellido(bufferCliente, bufferApellido) &&
				   !cliente_getCuit(bufferCliente, bufferCuit))
				{
					if(!ll_reduceInt(listaEstadoCobro, venta_existsIdCliente, bufferId ,&contador) && contador!=0)
					{
						fprintf(pFile, "%d,%s,%s,%s,%d\n", bufferId, bufferNombre, bufferApellido, bufferCuit, contador);
					}
				}
			}
		}
		retornar=0;
		fclose(pFile);
		printf("\nInforme generado con �xito.");

	}
	return retornar;
}
/*
 * \brief Suma todos los afiches qe ha comprado un cliente en particular cuyo id entra por par�metro.
 * \param puntero a LinkedList.
 * \param puntero a LinkedList.
 * \param id del cliente del que queremos saber cu�ntos afiches ha comprado.
 * \param puntero a la cantidad de afiches del cliente.
 * \return 0 si se recuper� la cantidad con �xito. -1 si ha habido alg�n problema.
*/
int informes_cantidadTotalPorCliente(LinkedList* clientList, LinkedList* sellList, int idCliente, int* cantidad)
{
	int retorno = -1;
	Venta* auxVenta;
	int len = ll_len(sellList);
	int auxIdCliente;
	//int auxId;
	int auxCobrado;
	int auxCantidad;

	int totalAfichesComprados=0;
	//iteramos la lista ventas
	for(int i=0;i<len;i++)
	{
		auxVenta= ll_get(sellList, i);
		venta_getIdCliente(auxVenta, &auxIdCliente);
		venta_getCobrado(auxVenta, &auxCobrado);
		venta_getCantidadAfiches(auxVenta, &auxCantidad);
		if(auxCobrado == 1 && auxIdCliente==idCliente)
		{
			totalAfichesComprados = totalAfichesComprados+auxCantidad;
		}
	}
	retorno = 0;
	*cantidad=totalAfichesComprados;

	return retorno;
}
/*
 * \brief Calcula la cantidad de afiches m�s alta y m�s baja comprada por uno o m�s clientes.
 * \param puntero a LinkedList.
 * \param puntero a LinkedList.
 * \param puntero con la cifra m�xima.
 * \param puntero con la cifra m�nima.
 * \return 0 si se recuper� la cantidad con �xito. -1 si ha habido alg�n problema.
*/
int informes_cantidadMasAlta(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente, int* pMaximo, int* pMinimo)
{
	int retorno = -1;
	int len=ll_len(pArrayListCliente);
	Cliente* auxCliente;
	int auxId;
	int cantidad;
	int maximo;
	int minimo;

	if(pArrayListVenta != NULL && pArrayListCliente !=NULL && pMaximo!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			auxCliente=ll_get(pArrayListCliente, i);
			cliente_getId(auxCliente, &auxId);
			informes_cantidadTotalPorCliente(pArrayListCliente, pArrayListVenta, auxId, &cantidad);

			if(i==0 || cantidad>maximo)
			{
				maximo = cantidad;
			}
			else
			{
				if(i==0 || cantidad>minimo)
				{
					minimo = cantidad;
				}
			}
		}
		*pMaximo=maximo;
		*pMinimo=minimo;
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief Calcula la cantidad de afiches m�s alta o m�s baja comprada por uno o m�s clientes.
 * \param puntero a LinkedList.
 * \param puntero a LinkedList.
 * \param indicador de si queremos la m�s alta o m�s baja (1 para el m�ximo, 0 para el m�nimo).
 * \return 0 si se recuper� la cantidad con �xito. -1 si ha habido alg�n problema.
*/
int informes_clienteCantidadMasAlta(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente, int maxMin)
{
	int retorno = -1;
	int maximo;
	int minimo;
	int cantidad;
	int len=ll_len(pArrayListCliente);
	Cliente* auxCliente;
	int auxId;
	char nombre[4096];
	char apellido[4096];
	char cuit[4096];

	informes_cantidadMasAlta(pArrayListVenta, pArrayListCliente, &maximo, &minimo);
	if(pArrayListVenta != NULL && pArrayListCliente !=NULL)
	{
		if (maxMin==1)
		{
			printf("\n\nLos clientes con m�s compras son:");
		}
		else
		{
			printf("\n\nLos clientes con menos compras son:");
		}
		for(int i=0;i<len;i++)
		{
			auxCliente=ll_get(pArrayListCliente, i);
			cliente_getId(auxCliente, &auxId);
			cliente_getNombre(auxCliente, nombre);
			cliente_getApellido(auxCliente, apellido);
			cliente_getCuit(auxCliente, cuit);
			informes_cantidadTotalPorCliente(pArrayListCliente, pArrayListVenta, auxId, &cantidad);
			if(maxMin== 1 && cantidad == maximo)
			{

				printf("\nID: %d. Nombre: %s. Apellido: %s. CUIT: %s.", auxId, nombre, apellido, cuit);
			}
			else
			{
				if(maxMin== 0 && cantidad == minimo)
				{
					printf("\nID: %d. Nombre: %s. Apellido: %s. CUIT: %s.", auxId, nombre, apellido, cuit);
				}
			}

		}
		retorno = 0;
	}

	return retorno;
}
/*
 * \brief Devuelve por puntero el n�mero de afiches que se vendieron en la venta en la que m�s se vendieron.
 * \param puntero a LinkedList.
 * \param puntero con la cifra m�xima.
 * \return 0 si se recuper� la cantidad con �xito. -1 si ha habido alg�n problema.
*/
int informes_numeroVentaMasAlta(LinkedList* pArrayListVenta, int* pVentaMasAlta)
{
	int retorno = -1;
	int len=ll_len(pArrayListVenta);
	Venta* auxVenta;
	int ventaMasAlta;
	int cantidad;
	int cobrado;

	if(pArrayListVenta !=NULL  && pVentaMasAlta!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			auxVenta=ll_get(pArrayListVenta, i);
			venta_getCantidadAfiches(auxVenta, &cantidad);
			venta_getCobrado(auxVenta, &cobrado);

			if(cobrado==1)
			{
				if(i==0 || cantidad>ventaMasAlta)
				{
					ventaMasAlta = cantidad;
				}
			}
		}
		*pVentaMasAlta=ventaMasAlta;

		retorno = 0;
	}
	return retorno;
}
/*
 * \brief Informa del ID de la/s venta/s en la que se compraron m�s afiches y el CUIT del cliente que la realiz�.
 * \param puntero a LinkedList.
 * \param puntero a LinkedList.
 * \return 0 si se recuper� la cantidad con �xito. -1 si ha habido alg�n problema.
*/
int informes_ventaConVentaMasAlta(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente)
{
	int retorno = -1;
	Venta* auxVenta;
	Cliente* auxCliente;
	int auxIdCliente;
	int idVenta;
	int cantidad;
	char cuit[4096];
	int len = ll_len(pArrayListVenta);
	int indexCliente;
	int ventaMasAlta;

	informes_numeroVentaMasAlta(pArrayListVenta, &ventaMasAlta);

	printf("\n\nVenta/s con m�s afiches vendidos: ");
	for(int i=0;i<len;i++)
	{
		auxVenta=ll_get(pArrayListVenta, i);
		venta_getId(auxVenta, &idVenta);
		venta_getCantidadAfiches(auxVenta, &cantidad);
		venta_getIdCliente(auxVenta, &auxIdCliente);
		indexCliente = cliente_findIndexById(pArrayListCliente, auxIdCliente);
		auxCliente=ll_get(pArrayListCliente, indexCliente);
		cliente_getCuit(auxCliente, cuit);
		if(cantidad==ventaMasAlta)
		{
			printf("Id: %d. CUIT del cliente: %s", idVenta, cuit);
		}
	}
	return retorno;
}
