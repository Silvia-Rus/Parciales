/*
 * Controller.c
 *
 *  Created on: 22 nov. 2020
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
 * \brief Alta de un cliente.
 * \param puntero a LinkedList.
 * \return 0 si se cargó el cliente, -1 si hubo un error.
 */
int controller_addCliente(LinkedList* pArrayListCliente)
{
	int retorno=-1;
	char auxNombre[NOMBRE_LEN];
	char auxApellido[APELLIDO_LEN];
	char auxCuit[ARRAY_SIZE];
	int auxId;
	Cliente* auxCliente;
	if(pArrayListCliente!=NULL)
	{
		if(	!utn_getLetrasYEspacios(auxNombre,  NOMBRE_LEN, "\nNombre: ","\nERROR. Ingrese solo nombres y espacios", INTENTOS) &&
			!utn_getLetrasYEspacios(auxApellido, APELLIDO_LEN, "\nApellido: ","\nERROR. Ingrese solo nombres y espacios", INTENTOS) &&
			!utn_getCuit(auxCuit,"\nCUIT: ","\nERROR. Ingrese un CUIT válido", INTENTOS, 14) &&
			!ll_mapExists(pArrayListCliente,cliente_existsCUIT,auxCuit))

		{
			//auxId=cli_nuevoId();
			auxId = cliente_idMasAltoMasUno(pArrayListCliente);
			auxCliente = cliente_newParametros(auxId, auxNombre, auxApellido, auxCuit);
			ll_add(pArrayListCliente, auxCliente);
			printf("\nId asignado: %d. Nomber: %s. Apellido: %s. Cuit: %s.", auxId, auxNombre, auxApellido, auxCuit);

		}
		else
		{
			printf("\nEl CUIT ya está en la base de datos.");
		}
		retorno=0;
	}
	return retorno;
}
/*
 * \brief Alta de una venta asociada a un cliente.
 * \param puntero a LinkedList.
 * \return 0 si se cargó el cliente, -1 si hubo un error.
 */
int controller_addVenta(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente)
{
    int retorno=-1;
	int id;
	char idCliente[4096];
	int idClienteInt;
    int cantidadAfiches;
    char nombreAfiche[AFICHE_LEN];
    int zona;
    int cobrado;
	Venta* auxVenta;
	if(pArrayListVenta != NULL && pArrayListCliente != NULL)
	{
		if(!utn_getCadena(idCliente,
							 4096,
							"\nIngrese el ID del cliente que efectua la compra: ",
							"\nERROR. Ingrese un número entero o pulse 0 para salir.",
							INTENTOS)&&
				ll_mapExists(pArrayListCliente, cliente_existsId, idCliente)==1)
			 {
				if(!utn_getNumeroInt(&cantidadAfiches,
									"\nIngrese la cantidad de afiches que desea comprar: ",
									"\nERROR. Ingrese un número entero.",
									1,
									INT_MAX,
									INTENTOS) &&
				  !utn_getCadena(nombreAfiche, AFICHE_LEN, "\nIngrese el nombre del afiche: ", "\nERROR", INTENTOS) &&
				  !utn_getNumeroInt(&zona,
									"\nIngrese la zona de se van a pegar los afiches."
									"\n1-CABA."
									"\n2-ZONA SUR,"
									"\n3-ZONA OESTE ",
									"\nERROR. Ingrese un número entero del 1 al 3.",
									1,
									3,
									INTENTOS))
				{
					//id=venta_nuevoId();
					idClienteInt= atoi(idCliente);
					id = venta_idMasAltoMasUno(pArrayListVenta);
					cobrado=0;
					auxVenta=venta_newParametros(id, idClienteInt, cantidadAfiches, nombreAfiche, zona, cobrado);
					ll_add(pArrayListVenta, auxVenta);
					printf("\nId asignado: %d. "
							"\nId del cliente: %d"
							"\nNombre de los afiches: %s."
							"\nCantidad de afiches: %d "
							"\nZona en la que se van a pegar: %d"
							"\nEstá cobrado? %d",
							id,
							idClienteInt,
							nombreAfiche,
							cantidadAfiches,
							zona,
							cobrado);
					retorno=0;
				}
			 }
			else
			{
				printf("\nEl ID no está en la base de datos.");
			}
	}
	return retorno;
}

/*
 * \brief Imprime según la funbción critero.
 * \param puntero a LinkedList.
 * \param función criterio.
 * \return 0 si se cargó el cliente, -1 si hubo un error.
 */
int controller_print(LinkedList* pArrayList, int (*pFuncListado)(void*))
{
	int retorno = -1;
	if(pArrayList!=NULL && !ll_isEmpty(pArrayList))
	{
		ll_map(pArrayList, *pFuncListado);
		retorno=0;
	}
	return retorno;
}
/*
 * \brief Lista todas las ventas existentes en una lista.
 * \param puntero a LinkedList.
 * \return 0 si imprimió sin problemas, -1 si no (no hay clientes en la base de datos).
 */
int controller_ListVenta(LinkedList* pArrayListVenta)
{
	int retorno=-1;
	Cliente* auxCliente;
	char auxNombre[NOMBRE_LEN];
	char auxApellido[APELLIDO_LEN];
	char auxCuit[ARRAY_SIZE];
	int auxId;
	int len = ll_len(pArrayListVenta);
	if(pArrayListVenta!=NULL)
	{

		if(ll_len(pArrayListVenta)<1)
		{
			printf("\nNo hay Clientes grabados en la base de datos."
					"\nVuelta al menú principal...");
		}
		else
		{
			printf("\nID    "
					"Nombre    "
					"Apellido    "
					"CUIT       ");
			for(int i=0; i<len;i++)
			{
				auxCliente = ll_get(pArrayListVenta, i);
				if(	!cliente_getId(auxCliente, &auxId) &&
					!cliente_getNombre(auxCliente, auxNombre) &&
					!cliente_getApellido(auxCliente, auxApellido) &&
					!cliente_getCuit(auxCliente, auxCuit))
				{
					printf("\n%-6d"
							"%-10s"
							"%-12s"
							"%-11s\n",
							auxId,
							auxNombre,
							auxApellido,
							auxCuit);
					retorno=0;
				}
			}
		}
	}
    return retorno;
}
/*
 * \brief Carga los datos de los clientes desde el archivo en la ruta especificada por parámetro(modo texto).
 * \param Ruta del archivo que contiene los datos que vamos a cargar.
 * \param puntero a LinkedList.
 * \param puntero a la función que parsea.
 * \return 0 si carga el archivo con éxito. -1 si ha habido algún problema.
*/
int controller_loadFromText(char* path , LinkedList* pArrayList, int (*pFuncParseo)(FILE *, LinkedList *))
{
	int retorno=-1;
	FILE* pFile;

	if(path!=NULL && pArrayList!=NULL)
	{
		pFile = fopen(path, "r");

		if(pFile!=NULL)
		{

			/*if(employee_hayIdRepetidos(pArrayList))
			{
				//ESTO YA VEREMOS
				printf("\nEl archivo tiene ids duplicados y no se ha cargado.");
				printf("\nVolviendo al menú principal...");
				ll_clear(pArrayList);
			}
			else*/
			//{
				pFuncParseo(pFile, pArrayList);
				//printf("\nArchivo cargado con éxito.");
				retorno=0;
			//}
		}
		else
		{
			printf("\nEl archivo no existe.");
		}
		fclose(pFile);
	}
	return retorno;
}
/*
 * \brief Modifica las ventas tanto campo por campo como cambiando el estado a cobrado.
 * \param puntero a LinkedList.
 * \param puntero a LinkedList.
 * \param modificación que queremos hacer (1 para modificar campos, 2 para pasar a cobrado).
 * \return 0 si modificó con éxito. -1 si ha habido algún problema.
*/
int controller_modifyVenta(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente, int operacion)
{
	int retorno = -1;
	LinkedList* listaNoCobrados;
	int idVenta;
	int idCliente;
	Venta* listVenta;
	//Cliente* listCliente;
	LinkedList* listCliente;
	int indexVenta;
	int indexCliente;

	if(pArrayListVenta != NULL && pArrayListCliente !=NULL && operacion>0 && operacion<3)
	{
		printf("\nLISTADO DE VENTAS POR COBRAR.\n");
		listaNoCobrados = ll_filter(pArrayListVenta, venta_estaCobrada);

		if (!controller_print(listaNoCobrados, venta_print)                 &&
			!utn_getNumeroInt(&idVenta,
							  "\n\nIntroduzca un ID del listado: ",
							  "\nERROR. Introduzca un número entero.",
							  1,
							  INT_MAX,
							  INTENTOS))
		{
			indexVenta = venta_findIndexById(listaNoCobrados, idVenta);
			if(indexVenta>-1)
			{
				listVenta=ll_get(listaNoCobrados, indexVenta);
				if(!venta_getIdCliente(listVenta, &idCliente))
				{
					indexCliente = cliente_findIndexById(pArrayListCliente, idCliente);
					listCliente=ll_get(pArrayListCliente, indexCliente);
					printf("\nCLIENTE ASOCIADO A LA COMPRA\n");
					if(!cliente_print(listCliente))
					{
						switch(operacion)
						{
							case 1://MODIFICAR
								if(venta_modify(listVenta))
								{
									printf("Hubo un problema modificando el registro.");
								}
								break;
							case 2://BORRAR
								if(venta_delete(listVenta))
								{
									printf("Hubo un problema eliminando el registro.");
								}
								break;
						}
					}
				}
			}
			else
			{
				printf("ID no perteneciente a la lista.");
			}
		}
		retorno = 0;
	}
	//borrarla listaNoCobrados
	return retorno;
}
/*
 * \brief guarda como texto en un archivo toda la información de la entidad Venta.
 * \param ruta del archivo.
 * \param puntero a LinkedList.
 * \return 0 si se guardó con éxito, -1 si hubo algún problema.
*/
int controller_saveVentaAsText(char* path , LinkedList* pArrayListCliente)
{
	int retorno=-1;
	int len = ll_len(pArrayListCliente);
	int id;
	int idCliente;
	int cantidadAfiches;
	char nombreAfiche[4096];
	int zona;
	int cobrado;
	FILE* pFile;
	Venta* auxVenta;

	if(path!=NULL && pArrayListCliente!=NULL)
	{
		if(ll_len(pArrayListCliente)<1)
		{
			printf("\nNo hay empleados grabados en la base de datos."
					"\nVuelta al menú principal...");
		}
		else
		{
			pFile = fopen(path, "w");//escribe en modo texto
			if(pFile!=NULL)
			{
				fprintf(pFile, "id,idCliente,Cantidad, Nombre, Zona, Cobrado\n");
				for(int i=0;i<len;i++)
				{
					auxVenta = ll_get(pArrayListCliente, i);
					if(!venta_getId(auxVenta, &id) &&
					   !venta_getIdCliente(auxVenta, &idCliente) &&
					   !venta_getCantidadAfiches(auxVenta, &cantidadAfiches) &&
					   !venta_getNombreAfiche(auxVenta, nombreAfiche) &&
					   !venta_getZona(auxVenta, &zona) &&
					   !venta_getCobrado(auxVenta, &cobrado))
					{
						fprintf(pFile, "%d,%d,%d,%s,%d,%d\n", id, idCliente, cantidadAfiches,nombreAfiche,zona, cobrado);
						retorno=0;
					}
				}
				//printf("Datos guardados con éxito");
				fclose(pFile);
			}
		}
	}
    return retorno;
}
/*
 * \brief guarda como texto en un archivo toda la información de la entidad Cliente.
 * \param ruta del archivo.
 * \param puntero a LinkedList.
 * \return 0 si se guardó con éxito, -1 si hubo algún problema.
*/
int controller_saveClienteAsText(char* path , LinkedList* pArrayListCliente)
{
	int retorno=-1;
	int len = ll_len(pArrayListCliente);
	int id;
	char nombre[4096];
	char apellido[4096];
	char cuit[4096];
	FILE* pFile;
	Cliente* auxCliente;

	if(path!=NULL && pArrayListCliente!=NULL)
	{
		if(ll_len(pArrayListCliente)<1)
		{
			printf("\nNo hay empleados grabados en la base de datos."
					"\nVuelta al menú principal...");
		}
		else
		{
			pFile = fopen(path, "w");//escribe en modo texto
			if(pFile!=NULL)
			{
				fprintf(pFile, "id,Nombre,Apellido, CUIT\n");
				for(int i=0;i<len;i++)
				{
					auxCliente = ll_get(pArrayListCliente, i);
					if(!cliente_getId(auxCliente, &id) &&
					   !cliente_getNombre(auxCliente, nombre) &&
					   !cliente_getApellido(auxCliente, apellido) &&
					   !cliente_getCuit(auxCliente, cuit))
					{
						fprintf(pFile, "%d,%s,%s,%s\n", id, nombre, apellido, cuit);
					}
				}
				//printf("Datos guardados con éxito");
				fclose(pFile);
			}
		}
	}
    return retorno;
}





