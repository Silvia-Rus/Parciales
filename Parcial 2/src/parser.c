/*
 * parser.c
 *
 *  Created on: 23 nov. 2020
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

#define NOMBRE_LEN 128
#define APELLIDO_LEN 128
#define AUX_LEN 4095
#define CUIT_LEN 14
#define ID_LEN 4096
#define CANTIDAD_AFICHES 4096
#define ZONA_LEN 4096
#define COBRADO 1
/* \brief Parsea los datos los datos de los clientes desde el archivo cargado por parámetro (modo texto).
 * \param la ruta del archivo que queremos parsear
 * \param la lista a la que queremos incorporar lo parseado.
 * \return 0 si todo ok, -1 si hay errores.
 */
/*int parser_clienteFromText(FILE* pFile , LinkedList* pArrayListCliente)
{
	int retornar=-1;
    char id[ID_LEN];;
    char nombre[NOMBRE_LEN];
    char apellido[APELLIDO_LEN];
    char cuit[CUIT_LEN];
	int r;
	Cliente* auxCliente;

	if(pFile!=NULL && pArrayListCliente!=NULL)
	{
		ll_clear(pArrayListCliente);
		do
		{
			r = fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id, nombre, apellido, cuit);

				if(r==4 && esNumericaInt(id, sizeof(id)))
				{
					auxCliente = cliente_newParametrosChar(id, nombre, apellido, cuit);
					ll_add(pArrayListCliente, auxCliente);
					retornar=0;
				}

		}while(feof(pFile)==0);
		fclose(pFile);
	}
	return retornar;
}
*/
int parser_clienteFromText(FILE* pFile, LinkedList* pArrayListCliente)
{
	int retornar=-1;
    char id[ID_LEN];
    char nombre[NOMBRE_LEN];
    char apellido[APELLIDO_LEN];
    char cuit[CUIT_LEN];
	int r;
	Cliente* auxCliente;

	if(pFile!=NULL && pArrayListCliente!=NULL)
	{
		ll_clear(pArrayListCliente);
		do
		{
			r = fscanf(pFile,"%[^,],%[^,],%[^,],%[^\n]\n",id, nombre, apellido, cuit);

				if(r==4 && esNumericaInt(id, sizeof(id)))
				{
					auxCliente = cliente_newParametrosChar(id, nombre, apellido, cuit);
					ll_add(pArrayListCliente, auxCliente);
					retornar=0;
				}

		}while(feof(pFile)==0);
		fclose(pFile);
	}
	return retornar;
}
/* \brief Parsea los datos los datos de las ventas desde el archivo cargado por parámetro (modo texto).
 * \param la ruta del archivo que queremos parsear
 * \param la lista a la que queremos incorporar lo parseado.
 * \return 0 si todo ok, -1 si hay errores.
 */
int parser_ventaFromText(FILE* pFile, LinkedList* pArrayListVenta)
{
	int retornar=-1;
	char id[4096];
	char idCliente[4096];
	char cantidadAfiches[4096];
	char nombreAfiche[4096];
	char zona[4096];
	char cobrado[4096];
	int r;
	Venta* auxVenta;

	if(pFile!=NULL && pArrayListVenta!=NULL)
	{
		ll_clear(pArrayListVenta);
		do
		{
			r = fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",id, idCliente, cantidadAfiches, nombreAfiche, zona, cobrado);

				if(r==6 && esNumericaInt(id, sizeof(id)))
				{
					//(char* id, char* idCliente,char* nombreAfiche,char* cantidadAfiches, char* zona, char* cobrado)
					auxVenta = venta_newParametrosChar(id, idCliente, nombreAfiche, cantidadAfiches, zona, cobrado);
					ll_add(pArrayListVenta, auxVenta);
					retornar=0;
				}

		}while(feof(pFile)==0);
		fclose(pFile);
	}
	return retornar;
}
