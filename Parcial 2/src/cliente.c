/*
 * cliente.c
 *
 *  Created on: 22 nov. 2020
 *      Author: Silvia Rus Mata
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "getData.h"
#include "cliente.h"

/*
 * \brief construye un espacio de memoria para alojar un nuevo cliente.
 * 		  sustituye a la función que buscaba al primer índice vacío.
 * \return devuelve un puntero a dicho espacio si lo encontró o NULL si no.
 */
Cliente* cliente_new()
{
	Cliente* p;
	p=(Cliente*)malloc(sizeof(Cliente));

	if(p!=NULL)
	{
		cliente_setId(p, 0);
		cliente_setNombre(p, "\n");
		cliente_setApellido(p, "\n");
		cliente_setCuit(p, "\n");
		return p;
	}
	else{return NULL;}
}
/*
* \brief genera identificadores únicos autoincrementales.
* \return el identificador único autoincremental generado.
*/
int cli_nuevoId(void)
{
	static int id = 0;
	id = id + 1;
	return id;
}
/*
 * \brief constructor que inicializa los parámetros que puedo recibir.
 * \param id en formato int recibido para guardar.
 * \param nombre en formato char recibido para guardar.
 * \param apellido en formato char recibido para guardar.
 * \param CUIT en formato char recibido para guardar.
 * \return puntero al cliente que se graba.
 */
Cliente* cliente_newParametros(int id, char* nombreStr,char* apellidoStr,char* cuitStr)
{
	Cliente* punteroCliente= cliente_new();
	if(punteroCliente !=NULL && id>-1 && nombreStr != NULL && apellidoStr != NULL && cuitStr != NULL)
	{

		if(!cliente_setId(punteroCliente, id) &&
		   !cliente_setNombre(punteroCliente, nombreStr) &&
		   !cliente_setApellido(punteroCliente, apellidoStr) &&
		   !cliente_setCuit(punteroCliente, cuitStr))
		{
			return punteroCliente;
		}else{return NULL;}
	}else{return NULL;}
}

/*
 * \brief valida el id introducido y lo copia al array.
 * \param array en el que vamos a copiar el id
 * \param id a introducir.
 * \return 0 si lo copió sin problemas, -1 si hubo un error.
 */
int cliente_setId(Cliente* this,int id)
{
	int retorno = -1;

	if(this!=NULL && id>0)
	{
		this->id=id;
		retorno=0;
	}
	return retorno;
}
/*
 * \brief valida el id introducido como texto y lo copia al array como número entero.
 * \param array en el que vamos a copiar el id
 * \param id a introducir.
 * \return 0 si lo copió sin problemas, -1 si hubo un error.
 */
int cliente_setIdChar(Cliente* this, char* id)
{
	int retorno=-1;
	char auxId[AUX_LEN];
	if(this!=NULL && id!=NULL && esNumericaInt(id, AUX_LEN)==1)
	{
		strncpy(auxId, id, AUX_LEN);
		this->id = atoi(auxId);
		retorno=0;
	}
	return retorno;
}
/*
 * \brief va al array y devuelve por puntero el id.
 * \param array en el que buscamos el id.
 * \param el id que queremos recuperar.
 * \return 0 si lo devolvió sin problemas, -1 si hubo un error.
 */
int cliente_getId(Cliente* this,int* id)
{
	int retorno = -1;

	if(this!=NULL && id!=NULL)
	{
		*id = this->id;
		retorno=0;
	}
	return retorno;
}
/*
 * \brief valida el nombre introducido y lo copia al array.
 * \param array en el que vamos a copiar el nombre
 * \param nombre a introducir.
 * \return 0 si lo copió sin problemas, -1 si hubo un error.
 */
int cliente_setNombre(Cliente* this,char* nombre)
{
	int retorno=-1;

	if(this != NULL &&
		nombre !=NULL &&
		esNombreValido(nombre, NOMBRE_LEN) )
	{
		strncpy(this->nombre, nombre, NOMBRE_LEN);
		retorno= 0;
	}
	return retorno;
}
/*
 * \brief va al array y devuelve por puntero el nombre.
 * \param array en el que buscamos el nombre,
 * \param nombre que queremos recuperar.
 * \return 0 si lo devolvió sin problemas, -1 si hubo un error.
 */
int cliente_getNombre(Cliente* this,char* nombre)
{
	int retorno=-1;

	if(this != NULL && nombre !=NULL)
	{
		strncpy(nombre, this->nombre, NOMBRE_LEN);
		retorno= 0;
	}
	return retorno;
}
/*
 * \brief valida el apellidop introducido y lo copia al array.
 * \param array en el que vamos a copiar el apellido.
 * \param apellido a introducir.
 * \return 0 si lo copió sin problemas, -1 si hubo un error.
 */
int cliente_setApellido(Cliente* this,char* apellido)
{
	int retorno=-1;

	if(this != NULL &&
		apellido !=NULL &&
		esNombreValido(apellido, APELLIDO_LEN))
	{
		strncpy(this->apellido,apellido, APELLIDO_LEN);
		retorno= 0;
	}
	return retorno;
}
/*
 * \brief va al array y devuelve por puntero el apellido.
 * \param array en el que buscamos el apellido,
 * \param apellido que queremos recuperar.
 * \return 0 si lo devolvió sin problemas, -1 si hubo un error.
 */
int cliente_getApellido(Cliente* this,char* apellido)
{
	int retorno=-1;

	if(this != NULL && apellido !=NULL)
	{
		strncpy(apellido, this->apellido, APELLIDO_LEN);
		retorno= 0;
	}
	return retorno;
}
/*
 * \brief valida el CUIT introducido y lo copia al array.
 * \param array en el que vamos a copiar el CUIT.
 * \param CUIT a introducir.
 * \return 0 si lo copió sin problemas, -1 si hubo un error.
 */
int cliente_setCuit(Cliente* this,char* cuit)
{
	int retorno=-1;

	if(this != NULL &&
		cuit !=NULL)
		//validar que es un cuit
	{
		strncpy(this->cuit,cuit, CUIT_LEN);
		retorno= 0;
	}
	return retorno;
}
/*
 * \brief va al array y devuelve por puntero el apellido.
 * \param array en el que buscamos el apellido,
 * \param apellido que queremos recuperar.
 * \return 0 si lo devolvió sin problemas, -1 si hubo un error.
 */
int cliente_getCuit(Cliente* this,char* cuit)
{
	int retorno=-1;

	if(this != NULL && cuit !=NULL)
	{
		strncpy(cuit, this->cuit, CUIT_LEN);
		retorno= 0;
	}
	return retorno;
}

/*
* \brief calcula un id calculando el id más alto de los disponibles en el sistema y sumándole uno.
* \param el listado en el que se va a buscar.
* \return el id calculado.
*/
int cliente_idMasAltoMasUno(LinkedList* this)
{
	int retorno=-1;
	int len = ll_len(this);
	Cliente* auxCliente;
	int id;
	int idMasAlto;
	if(this!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			auxCliente = ll_get(this, i);
			cliente_getId(auxCliente, &id);
			if(i==0 || id>idMasAlto)
			{
				idMasAlto = id;
				retorno = idMasAlto+1;
			}
		}
	}
	return retorno;
}
/*
 * \brief constructor que inicializa los parámetros que puedo recibir.
 * \param id en formato char recibido para guardar.
 * \param nombre en formato char recibido para guardar.
 * \param apellido en formato char recibido para guardar.
 * \param CUIT en formato char recibido para guardar.
 * \return puntero al cliente que se graba.
 */
Cliente* cliente_newParametrosChar(char* id, char* nombreStr,char* apellidoStr,char* cuitStr)
{
	Cliente* punteroCliente=0;
	punteroCliente = cliente_new();
	if(punteroCliente !=NULL && id != NULL && nombreStr != NULL && apellidoStr != NULL && cuitStr != NULL)
		{

			if(!cliente_setIdChar(punteroCliente, id) &&
			   !cliente_setNombre(punteroCliente, nombreStr) &&
			   !cliente_setApellido(punteroCliente, apellidoStr) &&
			   !cliente_setCuit(punteroCliente, cuitStr))
			{
				return punteroCliente;
			}else{return NULL;}
		}else{return NULL;}

}

/*
 * \brief comprueba si existe un id en el listado
 * \param linkedlist en el que vamos a buscar.
 * \param valor que se quiere comprobar.
 * \int Retorna  (-1) Error: si el puntero a la listas es NULL
				( 0) Si no existe el id en el listado.
				( 1) Si existe el id en el listado.
 */
int cliente_existsId(void* this, void* id)
{
	int retorno = -1;
	int idComparador;
	int bufferId= atoi(id);//el id de cliente que entra por el maps casteado.
	if(this != NULL && !cliente_getId((Cliente*)this, &idComparador))
	{
		if(idComparador == bufferId)
		{
			retorno = 1;
		}
		else
		{
			retorno = 0;
		}
	}
	return retorno;
}

/*
 * \brief comprueba si existe un CUIT en el listado
 * \param linkedlist en el que vamos a buscar.
 * \param valor que se quiere comprobar.
 * \int Retorna  (-1) Error: si el puntero a la listas es NULL
				( 0) Si no existe el CUIT en el listado.
				( 1) Si existe el CUIT en el listado.
 */
int cliente_existsCUIT(void* this, void* cuit)
{
	int retorno = -1;
	char cuitClient[CUIT_LEN];
	if(this != NULL && !cliente_getCuit((Cliente*)this, cuitClient))
	{
		if(strncmp(cuitClient, (char*)cuit, sizeof(cuitClient))==0)
		{
			retorno = 1;
		}
		else
		{
			retorno = 0;
		}
	}
	return retorno;
}

/*
* \brief imprime los campos del listado de clientes.
* \param el listado en el que se va a buscar.
* \return 0 si imprimió sin problemas, -1 si hubo un error.
*/
int cliente_print(void* this)
{
	int retorno = -1;
	Cliente* auxCliente;
	auxCliente = (Cliente*)this;
	char auxNombre[NOMBRE_LEN];
	char auxApellido[APELLIDO_LEN];
	char auxCuit[ARRAY_SIZE];
	int auxId;

	if(auxCliente != NULL)
	{
		if(!cliente_getId(auxCliente, &auxId) &&
		   !cliente_getNombre(auxCliente, auxNombre) &&
		   !cliente_getApellido(auxCliente, auxApellido) &&
		   !cliente_getCuit(auxCliente, auxCuit))
		{
			printf("\nId: %-6d"
					"Nombre: %-10s"
					"Apellido: %-12s"
					"CUIT: %-11s",
					auxId,
					auxNombre,
					auxApellido,
					auxCuit);
			retorno=0;
		}
	}
	return retorno;
}
/*
 * \brief recibe el id de un cliente y devuelve el índice del cliente.
 * \param linkedlist en el que vamos a buscar.
 * \param id del cliente.
 * \int Retorna  (-1) Error: si el puntero a la lista es NULL, el id es menor a 1 o no existe en la base.
				 el índice en el que está el cliente cuyo id entra por parámetro.
 */
int cliente_findIndexById(LinkedList* sellList, int id)
{
	int retorno=-1;
	int len = ll_len(sellList);
	int bufferId;
	Cliente* bufferVenta;
	if(sellList!=NULL && id>0)
	{
		for(int i=0;i<len;i++)
		{
			bufferVenta = ll_get(sellList, i);
			if(!cliente_getId(bufferVenta, &bufferId) && bufferId == id)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}
