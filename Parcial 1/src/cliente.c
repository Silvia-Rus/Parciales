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
* \brief genera identificadores �nicos autoincrementales.
* \return el identificador �nico autoincremental generado.
*/
static int cli_nuevoId(void)
{
	static int id = 0;
	id = id + 1;
	return id;
}
/*
* \brief busca una posici�n en la memoria que tenga isEmpty en TRUE. Se usa para crear nuevos registros.
* \param puntero al array en el que busca la posici�n.
* \param longitud del array en el que busca la posici�n.
* \param puntero con la posici�n en la memoria que tiene isEmpty en TRUE.
* \return devuelve 0 si todo ok (list no apunta a null y encuentra un lugar en vac�o en el array).
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
* \return 1 si el array est� vac�o (todos sus elementos tienen iseEmpty en 0) y 0 si no lo est�.
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
* \brief devuelve el lugar de la memoria en el que est� un id introducido por par�metro.
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
				"Vac�o\n");

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
 * \brief Funci�n para ordenar por caracter�sticas. Se recibe por par�metro si es ascendente o descentente.
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
			!cli_indiceVacio(list, len,&i) &&
			i >= 0  &&
			list[i].isEmpty==1 &&
			!utn_getLetrasYEspacios(buffer.nombre,
									LEN_NOMBRE,
									"\nNombre del cliente:",
									"\nError. Introduzca �nicamente letras y espacios.",
									INTENTOS) &&
			!utn_getLetrasYEspacios(buffer.apellido,
									LEN_NOMBRE,
									"\nApellido del cliente: ",
									"\nError. Introduzca solo letras y espacios.",
									INTENTOS) &&
			!utn_getCuit(buffer.cuit,
						"\nCUIT: ",
						"\nERROR.Ingrese un CUIT v�lido: ",
						INTENTOS,
						LEN_CUIT))
	{
			buffer.id =cli_nuevoId();
			buffer.isEmpty=0;
			list[i]= buffer;
			retorno=0;
			printf("\nSe ha grabado con �xito:"
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
							"\nError. El ID debe ser n�merico.: ",
							0,
							INT_MAX,
							INTENTOS))
	{
		indiceAModificar = cli_findById(list, len, idABuscar);
			if(indiceAModificar!=-1)
			{
			buffer = list[indiceAModificar];
			printf("Modificaciones para %s %s (CUIT: %s).\n", buffer.nombre, buffer.apellido, buffer.cuit);
			do
			{
				if(!utn_getNumeroInt(&campoAModificar,
									"\nMEN� MODIFICACI�N.\n"
									"Elija el dato que quiera modificar: \n"
									"1-Nombre. \n"
									"2-Apellido. \n"
									"3-CUIT. \n"
									"4-Volver a men� principal.\n\n",
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
													"\nERROR.Ingrese un nombre v�lido: ",
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
													"\nERROR.Ingrese un nombre v�lido: ",
													INTENTOS))
						{
								printf("Apellido actualizado a %s.\n", buffer.nombre);
								retorno=0;
						}
						break;
					case 3:
						if(!utn_getCuit(buffer.cuit,
										"Ingrese el nuevo CUIT: ",
										"\nERROR.Ingrese un CUIT v�lido: ",
												INTENTOS,
												LEN_CUIT))
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
* \brief da de baja a un cliente cuyo id entr� por par�mtero.
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
			indiceAModificar=cli_findById(list, len, idCliente);
			if(indiceAModificar!=-1)
			{
				list[indiceAModificar].isEmpty=1;
				retorno=0;
				printf("%s %s ha sido dado de baja exitosamente.\n\n", list[indiceAModificar].nombre, list[indiceAModificar].apellido);
			}
			else
			{
				printf("ID inv�lido");
				retorno=0;
			}
	}else{printf("Error en la baja del cliente.\n");}
	return retorno;
}
/*
 * \brief carga datos de manera autom�tica para debuguear.
 * \param puntero a la lista de publicaciones
 * \return los datos cargados.
 */
void cli_cargaAutomatica(Cliente *list)
{

	list[0].id = cli_nuevoId();
	strncpy(list[0].nombre,"Silvia",LEN_NOMBRE);
	strncpy(list[0].apellido,"Rus Mata",LEN_NOMBRE);
	strncpy(list[0].cuit,"27-95418871-5",LEN_NOMBRE);
	list[0].isEmpty = 0;

	list[1].id = cli_nuevoId();
	strncpy(list[1].nombre,"Sara",LEN_NOMBRE);
	strncpy(list[1].apellido,"Rus Mata",LEN_NOMBRE);
	strncpy(list[1].cuit,"27-95418871-5",LEN_NOMBRE);
	list[1].isEmpty = 0;

	list[2].id = cli_nuevoId();
	strncpy(list[2].nombre,"Marcelo",LEN_NOMBRE);
	strncpy(list[2].apellido,"Zumbo",LEN_NOMBRE);
	strncpy(list[2].cuit,"27-95418871-5",LEN_NOMBRE);
	list[2].isEmpty = 0;

	list[3].id = cli_nuevoId();
	strncpy(list[3].nombre,"Evelyn",LEN_NOMBRE);
	strncpy(list[3].apellido,"Lugo",LEN_NOMBRE);
	strncpy(list[3].cuit,"27-95418871-5",LEN_NOMBRE);
	list[3].isEmpty = 0;

    list[4].id = cli_nuevoId();
    strncpy(list[4].nombre,"Mar�a",LEN_NOMBRE);
	strncpy(list[4].apellido,"Garc�a",LEN_NOMBRE);
	strncpy(list[4].cuit,"27-95418871-5",LEN_NOMBRE);
    list[4].isEmpty = 0;

    list[5].id = cli_nuevoId();
    strncpy(list[5].nombre,"Claudia",LEN_NOMBRE);
	strncpy(list[5].apellido,"P�rez",LEN_NOMBRE);
	strncpy(list[5].cuit,"27-95418871-5",LEN_NOMBRE);
    list[5].isEmpty = 0;

    list[6].id = cli_nuevoId();
	strncpy(list[6].nombre,"Roberto",LEN_NOMBRE);
	strncpy(list[6].apellido,"Mart�nez",LEN_NOMBRE);
	strncpy(list[6].cuit,"27-95418871-5",LEN_NOMBRE);
    list[6].isEmpty = 0;

    list[7].id = cli_nuevoId();
    strncpy(list[7].nombre,"Manuel",LEN_NOMBRE);
	strncpy(list[7].apellido,"Torres",LEN_NOMBRE);
	strncpy(list[7].cuit,"27-95418871-5",LEN_NOMBRE);
    list[7].isEmpty = 0;

    list[8].id = cli_nuevoId();
    strncpy(list[8].nombre,"Jos�",LEN_NOMBRE);
	strncpy(list[8].apellido,"Hh",LEN_NOMBRE);
	strncpy(list[8].cuit,"27-95418871-5",LEN_NOMBRE);
    list[8].isEmpty = 0;

    list[9].id = cli_nuevoId();
	strncpy(list[9].nombre,"Lorem",LEN_NOMBRE);
	strncpy(list[9].apellido,"Ipsum",LEN_NOMBRE);
	strncpy(list[9].cuit,"27-95418871-5",LEN_NOMBRE);
    list[9].isEmpty = 0;
}



