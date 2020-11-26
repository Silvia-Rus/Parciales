/*
 * venta.c
 *
 *  Created on: 22 nov. 2020
 *      Author: Silvia Rus Mata
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "LinkedList.h"
#include "getData.h"
#include "cliente.h"
#include "venta.h"

/*
 * \brief construye un espacio de memoria para alojar una nueva venta.
 * 		  sustituye a la función que buscaba al primer índice vacío.
 * \return devuelve un puntero a dicho espacio si lo encontró o NULL si no.
 */
Venta* venta_new()
{

	Venta* p;
	p=(Venta*)malloc(sizeof(Venta));

	if(p!=NULL)
	{
		venta_setId(p, 0);
		venta_setIdCliente(p, 0);
		venta_setCantidadAfiches(p, 0);
		venta_setNombreAfiche(p, "\n");
		venta_setZona(p, 0);
		venta_setCobrado(p, 0);
		return p;
	}
	else{return NULL;}
}
/*
* \brief genera identificadores únicos autoincrementales.
* \return el identificador único autoincremental generado.
*/
int venta_nuevoId(void)
{
	static int id = 0;
	id = id + 1;
	return id;
}

/*
 * \brief valida el id introducido y lo copia al array.
 * \param array en el que vamos a copiar el id
 * \param id a introducir.
 * \return 0 si lo copió sin problemas, -1 si hubo un error.
 */
int venta_setId(Venta* this,int id)
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
int venta_setIdChar(Venta* this, char* id)
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
int venta_getId(Venta* this,int* id)
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
 * \brief constructor que inicializa los parámetros que puedo recibir.
 * \param id en formato int recibido para guardar.
 * \param nombre en formato char recibido para guardar.
 * \param apellido en formato char recibido para guardar.
 * \param CUIT en formato char recibido para guardar.
 * \return puntero al empleado que se graba.
 */
Venta* venta_newParametros(int id, int idCliente, int cantidadAfiches, char* nombreAfiche, int zona, int cobrado)
{
	Venta* punteroVenta= venta_new();
	if(punteroVenta !=NULL && id>-1 && idCliente>-1 && cantidadAfiches>1 && nombreAfiche != NULL && zona>0 && zona<5 && cobrado>-1 && cobrado <2 )
	{

		if(!venta_setId(punteroVenta, id) &&
		   !venta_setIdCliente(punteroVenta, idCliente) &&
		   !venta_setCantidadAfiches(punteroVenta, cantidadAfiches) &&
		   !venta_setNombreAfiche(punteroVenta, nombreAfiche) &&
		   !venta_setZona(punteroVenta, zona) &&
		   !venta_setCobrado(punteroVenta, cobrado))
		{
			return punteroVenta;
		}else{return NULL;}
	}else{return NULL;}
}
/*
 * \brief valida el id introducido y lo copia al array.
 * \param array en el que vamos a copiar el id
 * \param id a introducir.
 * \return 0 si lo copió sin problemas, -1 si hubo un error.
 */
int venta_setIdCliente(Venta* this,int idCliente)
{
	int retorno = -1;

	if(this!=NULL && idCliente>0)
	{
		this->idCliente=idCliente;
		retorno=0;
	}
	return retorno;
}
/*
 * \brief valida el id del cliente introducido como texto y lo copia al array como número entero.
 * \param array en el que vamos a copiar el id
 * \param id a introducir.
 * \return 0 si lo copió sin problemas, -1 si hubo un error.
 */
int venta_setIdClienteChar(Venta* this, char* idCliente)
{
	int retorno=-1;
	char auxId[AUX_LEN];
	if(this!=NULL && idCliente!=NULL && esNumericaInt(idCliente, AUX_LEN)==1)
	{
		strncpy(auxId, idCliente, AUX_LEN);
		this->idCliente = atoi(auxId);
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
int venta_getIdCliente(Venta* this,int* idCliente)
{
	int retorno = -1;

	if(this!=NULL && idCliente!=NULL)
	{
		*idCliente = this->idCliente;
		retorno=0;
	}
	return retorno;
}
/*
 * \brief valida la cantidad de afiches introducido y lo copia al array.
 * \param array en el que vamos a copiar la cantidad de afcihes.
 * \param cantidad de afiches a introducir.
 * \return 0 si lo copió sin problemas, -1 si hubo un error.
 */
int venta_setCantidadAfiches(Venta* this,int cantidadAfiches)
{
	int retorno = -1;

	if(this!=NULL && cantidadAfiches>0)
	{
		this->cantidadAfiches=cantidadAfiches;
		retorno=0;
	}
	return retorno;
}
/*
 * \brief valida la cantidad de afcihes introducida como texto y lo copia al array como número entero.
 * \param array en el que vamos a copiar la cantidad de afiches.
 * \param cantidad de afiches a introducir.
 * \return 0 si lo copió sin problemas, -1 si hubo un error.
 */
int venta_setCantidadAfichesChar(Venta* this, char* cantidadAfiches)
{
	int retorno=-1;
	char auxCantidadAfiches[AUX_LEN];
	if(this!=NULL && cantidadAfiches!=NULL && esNumericaInt(cantidadAfiches, AUX_LEN)==1)
	{
		strncpy(auxCantidadAfiches, cantidadAfiches, AUX_LEN);
		this->cantidadAfiches = atoi(auxCantidadAfiches);
		retorno=0;
	}
	return retorno;
}
/*
 * \brief va al array y devuelve por puntero la cantidad de afiches.
 * \param array en el que buscamos la cantidad de afiches.
 * \param el valor en cantidad de afiches que queremos recuperar.
 * \return 0 si lo devolvió sin problemas, -1 si hubo un error.
 */
int venta_getCantidadAfiches(Venta* this,int* cantidadAfiches)
{
	int retorno = -1;

	if(this!=NULL && cantidadAfiches!=NULL)
	{
		*cantidadAfiches = this->cantidadAfiches;
		retorno=0;
	}
	return retorno;
}
/*
 * \brief valida el nombre del afiche introducido y lo copia al array.
 * \param array en el que vamos a copiar el nombre del afiche.
 * \param nombre del afiche a introducir.
 * \return 0 si lo copió sin problemas, -1 si hubo un error.
 */
int venta_setNombreAfiche(Venta* this,char* nombreAfiche)
{
	int retorno=-1;

	if(this != NULL &&
		nombreAfiche !=NULL &&
		esNombreValido(nombreAfiche, AFICHE_LEN))
	{
		strncpy(this->nombreAfiche, nombreAfiche, AFICHE_LEN);
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
int venta_getNombreAfiche(Venta* this,char* nombreAfiche)
{
	int retorno=-1;

	if(this != NULL && nombreAfiche !=NULL)
	{
		strncpy(nombreAfiche, this->nombreAfiche, AFICHE_LEN);
		retorno= 0;
	}
	return retorno;
}

/*
 * \brief valida la zona introducida y la copia al array.
 * \param array en el que vamos a copiar la zona.
 * \param zona a introducir.
 * \return 0 si lo copió sin problemas, -1 si hubo un error.
 */
int venta_setZona(Venta* this,int zona)
{
	int retorno = -1;

	if(this!=NULL && zona>0)
	{
		this->zona=zona;
		retorno=0;
	}
	return retorno;
}
/*
 * \brief valida la zona introducida como texto y lo copia al array como número entero.
 * \param array en el que vamos a copiar la zona.
 * \param zona a introducir.
 * \return 0 si lo copió sin problemas, -1 si hubo un error.
 */
int venta_setZonaChar(Venta* this, char* zona)
{
	int retorno=-1;
	char auxZona[AUX_LEN];
	if(this!=NULL && zona!=NULL && esNumericaInt(zona, AUX_LEN)==1)
	{
		strncpy(auxZona, zona, AUX_LEN);
		this->zona = atoi(zona);
		retorno=0;
	}
	return retorno;
}
/*
 * \brief va al array y devuelve por puntero la zona.
 * \param array en el que buscamos la zona.
 * \param la zona que queremos recuperar.
 * \return 0 si lo devolvió sin problemas, -1 si hubo un error.
 */
int venta_getZona(Venta* this,int* zona)
{
	int retorno = -1;

	if(this!=NULL && zona!=NULL)
	{
		*zona = this->zona;
		retorno=0;
	}
	return retorno;
}
/*
 * \brief valida si está cobrado y copia el dato al array.
 * \param array en el que vamos a copiar si está cobrado.
 * \param valor a introducir.
 * \return 0 si lo copió sin problemas, -1 si hubo un error.
 */
int venta_setCobrado(Venta* this,int cobrado)
{
	int retorno = -1;

	if(this!=NULL && cobrado>-1)
	{
		this->cobrado=cobrado;
		retorno=0;
	}
	return retorno;
}
/*
 * \brief valida el valor de cobrado introducido como texto y lo copia al array como número entero.
 * \param array en el que vamos a copiar el valor de cobrado.
 * \param el valor de cobrado a introducir.
 * \return 0 si lo copió sin problemas, -1 si hubo un error.
 */
int venta_setCobradoChar(Venta* this, char* cobrado)
{
	int retorno=-1;
	char auxCobrado[AUX_LEN];
	if(this!=NULL && cobrado!=NULL && esNumericaInt(cobrado, AUX_LEN)==1)
	{
		strncpy(auxCobrado, cobrado, AUX_LEN);
		this->cobrado = atoi(cobrado);
		retorno=0;
	}
	return retorno;
}
/*
 * \brief va al array y devuelve por puntero al dato de si está cobrado.
 * \param array en el que buscamos el dato.
 * \param puntero al dato que queremos recuperar.
 * \return 0 si lo devolvió sin problemas, -1 si hubo un error.
 */
int venta_getCobrado(Venta* this,int* cobrado)
{
	int retorno = -1;

	if(this!=NULL && cobrado!=NULL)
	{
		*cobrado = this->cobrado;
		retorno=0;
	}
	return retorno;
}

/*
* \brief calcula un id calculando el id más alto de los disponibles en el sistema y sumándole uno.
* \param el listado en el que se va a buscar.
* \return el id calculado.
*/
int venta_idMasAltoMasUno(LinkedList* this)
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
 * \param idCliente en formato char recibido para guardar.
 * \param nombre del afiche en formato char recibido para guardar.
 * \param cantidad de afiches en formato char recibido para guardar.
 * \param zona en formato char recibido para guardar.
 * \param estado de cobrado o no en formato char recibido para guardar.
 * \return puntero al empleado que se graba.
 */
Venta* venta_newParametrosChar(char* id, char* idCliente,char* nombreAfiche,char* cantidadAfiches, char* zona, char* cobrado)
{
	Venta* punteroVenta=0;
	punteroVenta = venta_new();
	if(punteroVenta !=NULL && id != NULL && idCliente != NULL && nombreAfiche != NULL && cantidadAfiches != NULL && zona != NULL && cobrado != NULL)
	{
		if(!venta_setIdChar(punteroVenta, id) &&
		   !venta_setIdClienteChar(punteroVenta, idCliente) &&
		   !venta_setNombreAfiche(punteroVenta, nombreAfiche) &&
		   !venta_setCantidadAfichesChar(punteroVenta, cantidadAfiches) &&
		   !venta_setZonaChar(punteroVenta, zona) &&
		   !venta_setCobradoChar(punteroVenta, cobrado))
		{
			return punteroVenta;
		}else{return NULL;}
	}else{return NULL;}
}
/*
* \brief imprime los campos del listado de ventas.
* \param el listado en el que se va a buscar.
* \return 0 si imprimió sin problemas, -1 si hubo un error.
*/
int venta_print(void* this)
{
	int retorno = -1;
	Venta* auxVenta;
	auxVenta = (Venta*)this;
	int id;
	int idCliente;
	int cantidadAfiches;
	char nombreAfiche[AFICHE_LEN];
	int zona;
	int cobrado;

	if(auxVenta != NULL)
	{
		if(!venta_getId(auxVenta, &id) &&
		   !venta_getIdCliente(auxVenta, &idCliente) &&
		   !venta_getCantidadAfiches(auxVenta, &cantidadAfiches) &&
		   !venta_getNombreAfiche(auxVenta, nombreAfiche) &&
		   !venta_getZona(auxVenta, &zona) &&
		   !venta_getCobrado(auxVenta, &cobrado))
		{
			printf("\nId: %-6d"
					"Id Cliente: %-10d"
					"Cantidad: %-6d"
					"Nombre: %-15s"
					"Zona: %-6d"
					"Cobrado: %-6d",
					id,
					idCliente,
					cantidadAfiches,
					nombreAfiche,
					zona,
					cobrado);
			retorno=0;
		}
	}
	return retorno;
}
/*
 * \brief comprueba si una venta está cobrada (=1)
 * \param linkedlist en el que vamos a buscar.
 * \param valor que se quiere comprobar.
 * \int Retorna  (-1) Error: si el puntero a la listas es NULL
				( 0) Si no está cobrada.
				( 1) Si está cobnrada.
 */
int venta_estaCobrada(void* this)
{
	int retorno = -1;
	int cobrado;
	if(this != NULL && !venta_getCobrado((Venta*)this, &cobrado))
	{
		if(cobrado)
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


int venta_noEstaCobrada(void* this)
{
	int retorno = -1;
	int cobrado;
	if(this != NULL && !venta_getCobrado((Venta*)this, &cobrado))
	{
		if(!cobrado)
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
 * \brief recibe el id de una venta y devuelve el índice de dicha venta.
 * \param linkedlist en el que vamos a buscar.
 * \param id de la venta.
 * \int Retorna  (-1) Error: si el puntero a la lista es NULL, el id es menor a 1 o no existe en la base.
				 el índice en el que está la compra cuyo id entra por parámetro.
 */
int venta_findIndexById(LinkedList* sellList, int id)
{
	int retorno=-1;
	int len = ll_len(sellList);
	int bufferId;
	Venta* bufferVenta;
	if(sellList!=NULL && id>0)
	{
		for(int i=0;i<len;i++)
		{
			bufferVenta = ll_get(sellList, i);
			if(!venta_getId(bufferVenta, &bufferId) && bufferId == id)
			{
				retorno = i;
				break;
			}
		}
	}
	return retorno;
}

/*
 * \brief despliega un menú para modificar los datos de una venta.
 * \param lista sobre la que se va a hacer la modificación.
 * \int Retorna  (-1) Error: si el puntero a la lista es NULL.
				 ( 0) Si se hizo la modificación con éxito.
 */
int venta_modify(Venta* this)
{
	int retorno = -1;
	int opcion;
	int cantidad;
	char nombre[4096];
	int zona;

	if(!utn_getNumeroInt(&opcion,
						  "\n\n¿Qué campo desea modificar? "
						  "\n1-Cantidad de afiches."
						  "\n2-Nombre del afiche."
						  "\n3-Zona.",
						  "\nERROR. Ingrese un número del 1 al 3.",
						  1,
						  3,
						  INTENTOS))
	{
		switch(opcion)
		{
		case 1://cantidad
		 if(!utn_getNumeroInt(&cantidad,
							  "\nIntroduzca la nueva cantidad: ",
							  "\nERROR. Ingrese un número entero.",
							  1,
							  INT_MAX,
							  INTENTOS) &&
				!venta_setCantidadAfiches(this, cantidad))
		  {
			 printf("\nModificación realizada con éxito.");
		  }
			break;
		case 2://nombre del afiche
			  if(!utn_getCadena(nombre,
					  	  	  	 4096,
								 "\nIngrese el nuevo nombre del afiche: ",
								 "\nERROR",
								 INTENTOS) &&
				!venta_setNombreAfiche(this, nombre))
			  {
				  printf("\nModificación realizada con éxito.");
			  }
			break;
		case 3://zona
			if(!utn_getNumeroInt(&zona,
								  "\nIntroduzca la nueva Zona: "
								  "\n1-CABA."
								  "\n2-ZONA SUR."
								  "\n3-ZONA OESTE ",
								  "\nERROR. Ingrese un número entero del 1 al 3.",
								  1,
								  3,
								  INTENTOS) &&
				!venta_setZona(this, zona))
		   {
			 printf("\nModificación realizada con éxito.");
		   }
			break;
		}
		retorno = 0;
	}

	return retorno;
}

int venta_delete(Venta* this)
{
	int retorno = -1;
	int opcion;
	if(!utn_getNumeroInt(&opcion,
					  "\n\n¿Está seguro que desea dar por cobrada la venta? "
					  "\n1-Sí."
					  "\n2-No.",
					  "\nERROR. Ingrese 1 ó 2.",
					  1,
					  2,
					  INTENTOS))
	{

		switch(opcion)
		{
		case 1:
			if(!venta_setCobrado(this, 1))
			{
				printf("\nVenta cobrada con éxito.");
			}
			break;
		case 2:
			printf("\nNo se hizo ninguna modificación.");
			break;
		}
		retorno = 0;
	}
	return retorno;
}

/*
 * \brief comprueba si existe un id en el listado
 * \param linkedlist en el que vamos a buscar.
 * \param valor que se quiere comprobar.
 * \int Retorna  (-1) Error: si el puntero a la listas es NULL
				( 0) Si no existe el id en el listado.
				( 1) Si existe el id en el listado.
 */
int venta_existsIdCliente(void* this, void* idCliente)
{
	int retornar=0;
	int comparadorIdCliente;
	int auxIdCliente = (int) idCliente;
	Venta* auxListVenta = (Venta*) this;
	if(!venta_getIdCliente(auxListVenta, &comparadorIdCliente))
	{
		if(comparadorIdCliente == auxIdCliente)
		{
			retornar=1;
		}
	}
	return retornar;

}




