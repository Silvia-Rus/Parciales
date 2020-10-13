/*
 * cliente.c
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
#define INTENTOS 3
#define LEN_CLIENTE 10
#define CUIT_SIZE 12


static int cli_nuevoId(void);

/*
* \brief To indicate that all position in the array are empty, this function put the flag (isEmpty) in TRUE in all position of the array
* \param list Employee* Pointer to array of employees
* \param len int Array length
* \return return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int cli_initList(Cliente* list, int len)
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
static int cli_nuevoId(void)
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
int cli_indiceVacio(Cliente *list, int len, int *pIndiceLibre)
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
* \param puntero al array que comprueba.
* \param longitud del array que comprueba.
* \return 1 si el array está vacío (todos sus elementos tienen iseEmpty en FALSE) y 0 si no lo está.
 */
int cli_isEmpty(Cliente *list, int len)
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
* \param puntero a la lista de clientes.
* \param longitud del array.
* \param id a buscar.
* \return Return employee index position or (-1) if [Invalid length or NULL pointer received or employee not found]
*/
int cli_findById(Cliente* list,int len, int id)
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
* \brief imprime una tabla.
* \param puntero al array que se imprime.
* \param longitud del array que se imprime.
* \return -1 si da error (puntero a nulo o longitud incorrecta) o 0 si sale bien.
*/
int cli_printList(Cliente* list, int len)
{
	int retorno = -1;
	if(list != NULL && len > 0)
	{
		printf("\n\nLISTADO:\n\n"
				"Nombre         "
				"Nombre2        "
				"CUIT      "
				"ID   "
				"Vacío\n");

		for(int i=0;i< len ;i++)
		{
			if(list[i].isEmpty == 0)
			{

				printf(
						"%-15s"
						"%-15s"
						"%-10s"
						"%-5d "
						"%-d\n",
						list[i].nombre,
						list[i].apellido,
						list[i].cuit,
						list[i].id,
						list[i].isEmpty);
			}
		}
		retorno = 0;
	}
	return retorno;
}
/*
 * \brief Función para ordenar por características. Se recibe por parámetro si es ascendente o descentente.
 * \param puntero al array que se quiere ordenar.
 * \param longitud al array que se quiere ordenar.
 * \param se recibe el orden en el que se quiere que se muestren los resultados (1 para ascendente y 0 para descendente)
 * \return -1 si algo fue mal, 0 si fue todo bien.
 */
/*int sort(Cliente *list, int len, int order)
{
	int retorno = -1;
		Cliente auxSwap;
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
						((strncmp(list[i].nombre, list[i+1].name, LEN_NOMBRE) > 0) ||
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
 * \brief da de alta un cliente nuevo.
 * \param puntero a la lista de clientes.
 * \param longitud de la lista de clientes.
 * \param puntero a la lista de clientes.
 * \param longitud de la lista de clientes.
 * \return -1 si algo fue mal, 0 si fue todo bien.
*/
int cli_altaRegistro(Cliente *list,int len)
{
	int retorno = -1;
	Cliente buffer;
	int i;
	if(list!=NULL &&
			len>0 &&
			!cli_indiceVacio(list, LEN_NOMBRE,&i) &&
			i >= 0  &&
			list[i].isEmpty==1 &&
			!utn_getLetrasYEspacios(buffer.nombre,
									LEN_NOMBRE,
									"Nombre del cliente:",
									"\nError. Introduzca únicamente letras y espacios.",
									INTENTOS) &&
			!utn_getLetrasYEspacios(buffer.apellido,
									LEN_NOMBRE,
									"Apellido del cliente: ",
									"\nError. Introduzca solo letras y espacios.",
									INTENTOS) &&
			//conseguir GET_CUIT
			!utn_getCadena(buffer.cuit,
							CUIT_SIZE,
							"CUIT del cliente::",
							"\nError. Introduzca un CUIT válido.",
							INTENTOS))
	//int utn_getCuit(char* pResultado,int len, char* mensaje, char* mensajeError, int reintentos)
			/*!utn_getCuit(buffer.cuit,
						//CUIT_SIZE,
						"Ingrese el nuevo CUIT: ",
						"\nERROR.Ingrese un CUIT válido: ",
						INTENTOS))*/
	{
			buffer.id =cli_nuevoId();
			buffer.isEmpty=0;
			list[i]= buffer;
			retorno=0;
			printf("Se ha grabado con éxito:\n"
					"\nNombre: %s."
					"\nApellido: %s."
					"\nCUIT: %s.\n",
					list[i].nombre,
					list[i].apellido,
					list[i].cuit);
	}
	return retorno;
}
/*
* \brief busca el id de un registro para modificarlo.
* \param puntero al array a modificar.
* \param longitud del array a modificar.
 * \return -1 si algo fue mal, 0 si fue todo bien.
*/
int cli_modify(Cliente *list, int len)
{
	int retorno = -1;
	int idABuscar;
	int indiceAModificar;
	int campoAModificar;
	Cliente buffer;

	if (list!=NULL &&
			len >0 &&
			!cli_isEmpty(list, len) &&
			!utn_getNumeroInt(&idABuscar,
							"\nID del registro a modificar: ",
							"\nError. El ID debe ser númerico.: ",
							0,
							INT_MAX,
							INTENTOS))
	{
		indiceAModificar = cli_findById(list, len, idABuscar);
			if(indiceAModificar!=-1)
			{
			buffer = list[indiceAModificar];
			do
			{
				if(!utn_getNumeroInt(&campoAModificar,
									"\nMENÚ MODIFICACIÓN.\n"
									"Elija el dato que quiera modificar: \n"
									"1-Nombre. \n"
									"2-Apellido. \n"
									"3-CUIT. \n"
									"\n4-Volver a menú principal.\n\n",
									"\nIngrese una opcion valida: ",
									1,
									4,
									INTENTOS))
				{
					switch(campoAModificar)
					{
					case 1:
						if(!utn_getLetrasYEspacios(buffer.nombre,
													LEN_NOMBRE,
													"\nIngrese el nuevo nombre: ",
													"\nERROR.Ingrese un nombre válido: ",
													INTENTOS))
						{
							printf("Nombre actualizado a %s.\n", buffer.nombre);
							retorno=0;
						}
						break;
					case 2:
						if(!utn_getLetrasYEspacios(buffer.apellido,
													LEN_NOMBRE,
													"\nIngrese el nuevo apellido: ",
													"\nERROR.Ingrese un nombre válido: ",
													INTENTOS))
						{
								printf("Apellido actualizado a %s.\n", buffer.nombre);
								retorno=0;
						}
						break;
					case 3:
						//int utn_getCuit(char* pResultado,int len, char* mensaje, char* mensajeError, int reintentos)
						/*if(!utn_getCuit(buffer.cuit,
										//CUIT_SIZE,
										"\nIngrese el nuevo CUIT: ",
										"\nERROR.Ingrese un CUIT válido: ",
										INTENTOS))*/
						if(!utn_getCadena(buffer.cuit,
								LEN_NOMBRE,
								"\nIngrese el nuevo CUIT: ",
								"\nERROR.Ingrese un CUIT válido: ",
								INTENTOS))
						{
								printf("CUIT actualizado a %s.\n", buffer.nombre);
								retorno=0;
						}
					}
					list[indiceAModificar] = buffer;
					retorno = 0;
				}
			}while(campoAModificar!=4);
		}
	}
	return retorno;
}
/*
* \brief da de baja a un cliente cuyo id entró por parámtero.
* \param puntero al array de empleados.
* \param longitud del array de empleados.
* \param id del cliente que se quiere dar de baja.
* \return -1 si algo fue mal, 0 si fue todo bien.
*/
int cli_bajaById(Cliente *list, int len, int idCliente)
{
	int indiceAModificar;
	int retorno = -1;
	if (list != NULL &&
			len > 0 &&
			!cli_isEmpty(list, len))
	{
			indiceAModificar=cli_findById(list, LEN_CLIENTE, idCliente);
			if(indiceAModificar!=-1)
			{
				list[indiceAModificar].isEmpty=1;
				retorno=0;
				printf("%s %s ha sido dado de baja exitosamente.\n\n", list[indiceAModificar].nombre, list[indiceAModificar].apellido);
			}
			else
			{
				printf("ID inválido");
			}
	}else{printf("Error.\n");}
	return retorno;
}
/*
 * \brief carga datos de manera automática para debuguear.
 * \param puntero a la lista de publicaciones
 * \return los datos cargados.
 */
void cli_cargaAutomatica(Cliente *list)
{
	    list[0].id = 1;
strncpy(list[0].nombre,"Silvia",LEN_NOMBRE);
strncpy(list[0].apellido,"Rus Mata",LEN_NOMBRE);
strncpy(list[0].cuit,"1234",11);
	    list[0].isEmpty = 0;

	    list[1].id = 2;
strncpy(list[1].nombre,"Sara",LEN_NOMBRE);
strncpy(list[1].apellido,"Rus",LEN_NOMBRE);
strncpy(list[1].cuit,"5555",11);
	    list[1].isEmpty = 0;
}




