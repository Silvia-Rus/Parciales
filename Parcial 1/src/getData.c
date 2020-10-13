/*
 * getData.c
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

#define ARRAY_SIZE 4096





static int myGets(char* cadena, int len);
static int esNumericaInt(char* cadena, int len);
static int esNumericaFloat(char* cadena, int len);
static int esLetrasYEspacios(char* cadena, int len);
static int getInt(int *pResultado);
static int getFloat(float *pResultado);
static int getLetrasYEspacios(char *pResultado, int len);
static int isCuit(char cadena[]);


/*
 * \brief valida que la cadena recibida no excede la memoria del array y hace obligatoria la entrada de datos.
 * \param puntero con el string validado.
 * \param longitud del string.
 * \return 0 si ha salido ok. -1 si no.
 */
static int myGets(char* cadena, int len)
{
	int retorno = -1;
	char buffer[4096];
	if(cadena != NULL && len > 0)
	{
		fflush(stdin);
		if(cadena !=NULL &&
				len>0 &&
				(fgets(buffer, sizeof(buffer), stdin) != NULL) &&
				buffer[0] !='\n')
		{
			if(buffer[strnlen(buffer, sizeof(buffer))-1] == '\n')
			{
				(buffer[strnlen(buffer, sizeof(buffer))-1] = '\0');
			}

			if(strnlen(buffer, sizeof(buffer)) <= len)
			{
				strncpy(cadena, buffer, len);
				retorno = 0;
			}
		}
	}
	return retorno;
}
/*
 * \brief valida que la cadena recibida es un número entero.
 * \param puntero con el string validado.
 * \param longitud del string.
 * \return 1 (verdadero) si es un número entero. 0 (falso) si no lo es.
 */
static int esNumericaInt(char* cadena, int len)
{
	int retorno=1;
	int i;
	for(i=0; i<len && cadena[i]!='\0'; i++)
	{
		if(i==0 && (cadena[i]=='+' || cadena[i]=='-'))
		{
			continue;
		}
		if(cadena[i]>'9' || cadena[i]<'0')
		{
			retorno=0;
				break;
		}
	}
	return retorno;
}
/*
 * \brief valida que la cadena recibida es un número flotante.
 * \param puntero con el string validado.
 * \param longitud del string.
 * \return 1 (verdadero) si es un número entero. 0 (falso) si no lo es.
 */
static int esNumericaFloat(char* cadena, int len)
{
	int retorno=1;
	int i;
	int contadorPuntos=0;
	for(i=0; i<len && cadena[i]!='\0'; i++)
	{
		if(cadena[i]=='.')
		{
			contadorPuntos++;
		}
		if((i==0 && (cadena[i]=='+' || cadena[i]=='-')) || (i>0 && cadena[i]=='.'))
		{
			continue;
		}
		if(contadorPuntos>1 || cadena[i]>'9' || cadena[i]<'0')
		{
			retorno=0;
				break;
		}
	}
	return retorno;
}
/*
 * \brief Valida que la cadena recibida está compuesta únicamente por letras o espacios.
 * \param puntero con el string validado.
 * \param longitud del string.
 * \return 1 (verdadero) si solo tiene letras y espacios. 0 (falso) si no.
 */
static int esLetrasYEspacios(char* cadena, int len)
{
	int retorno = 1;
	int i;

	for(i=0 ;  i<len && cadena[i] != '\0'; i++)
	{
		if((cadena[i] < 'A' || cadena[i] > 'Z') &&
			(cadena[i] < 'a' || cadena[i] > 'z') &&
			(cadena[i] != ' ') &&
			(cadena[i] < 'á' || cadena[i] > 'ú') &&
			(cadena[i] != 'é'))
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}
/**
 * \brief convierte la cadena recibida en un número entero con la función atoi.
 * \param puntero con el string validado.
 * \return 0 si ha salido ok. -1 si no.
 */
static int getInt(int *pResultado)
{
	int retorno=-1;
	char buffer[50];
	if(pResultado != NULL &&
			myGets(buffer, sizeof(buffer))==0 &&
			esNumericaInt(buffer, sizeof(buffer))==1)
	{
		retorno=0;
		*pResultado=atoi(buffer);
	}
	return retorno;
}
/*
 * \brief convierte la cadena recibida en un número flotante con la función atof.
 * \param puntero con el string validado.
 * \return 0 si ha salido ok. -1 si no.
 */
static int getFloat(float *pResultado)
{
	int retorno=-1;
	char buffer[50];
	if(pResultado != NULL &&
		myGets(buffer, sizeof(buffer))==0 &&
		esNumericaFloat(buffer, sizeof(buffer))==1)
	{
		retorno=0;
		*pResultado=atof(buffer);
	}
	return retorno;
}
/*
 * \brief convierte la cadena recibida en un número flotante con la función atof.
 * \param puntero con el string validado.
 * \param longitud del string.
 * \return 0 si ha salido ok. -1 si no.
 */
static int getLetrasYEspacios(char *pResultado, int len)
{
	int retorno=-1;
	char buffer[50];
	if(pResultado != NULL &&
		myGets(buffer, sizeof(buffer))==0 &&
		esLetrasYEspacios(buffer, sizeof(buffer))==1)
	{
		retorno=0;
		strncpy(pResultado, buffer, len);
	}
	return retorno;
}
/*
 * \brief solicita un número entero por pantalla y lo valida.
 * \param puntero con el número.
 * \param mensaje para solicitar el número entero.
 * \param mensaje de error si no cumple las condiciones preestablecidas.
 * \param cifra mínima que se puede introducir.
 * \param cifra máxima que se puede introducir.
 * \param cantidad de reintentos para introducir un valor válido.
 * \return 0 si ha salido ok. -1 si no (punteros nulos, mínimo mayor al máximo, reintentos menor a 0)
 */
int utn_getNumeroInt(int* pResultado,
					char* mensaje,
					char* mensajeError,
					int minimo,
					int maximo,
					int reintentos)
{
	int retorno = -1;
	int buffer;

	if(pResultado != NULL &&
			mensaje != NULL &&
			mensajeError != NULL &&
			minimo <= maximo &&
			reintentos > 0)
	{
		do{
			printf("%s", mensaje);
			fflush(stdin);
			if(getInt(&buffer) == 0 &&
					buffer >= minimo &&
					buffer <= maximo)
			{
				*pResultado = buffer;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", mensajeError);
				reintentos--;
			}
		}while(reintentos >=0);
	}
	return retorno;
}
/*
 * \brief solicita un número flotante por pantalla y lo valida.
 * \param puntero con el número.
 * \param mensaje para solicitar el número flotante..
 * \param mensaje de error si no cumple las condiciones preestablecidas.
 * \param cifra mínima que se puede introducir.
 * \param cifra máxima que se puede introducir.
 * \param cantidad de reintentos para introducir un valor válido.
 * \return return 0 si ha salido ok. -1 si no (punteros nulos, mínimo mayor al máximo, reintentos menor a 0)
 */
int utn_getNumeroFloat(float* pResultado,
						char* mensaje,
						char* mensajeError,
						int minimo,
						int maximo,
						int reintentos)
{
	int retorno = -1;
	float buffer;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos > 0)
	{
		do{
			printf("%s", mensaje);
			fflush(stdin);
			if(getFloat(&buffer) == 0 &&
					buffer >= minimo &&
					buffer <= maximo)
			{
				*pResultado = buffer;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", mensajeError);
				reintentos--;
			}
		}while(reintentos >=0);
	}
	return retorno;
}
/*
 * \brief solicita una cadena de valores.
 * \param puntero con la cadena.
 * \param mensaje para solicitar la cadena..
 * \param mensaje de error si no cumple las condiciones preestablecidas.
 * \param cantidad de reintentos para introducir un valor válido.
 * \return 0 si ha salido ok. -1 si no.
 */
int utn_getCadena(char* pResultado,
					int len,
					char* mensaje,
					char* mensajeError,
					int reintentos)
{
	int retorno = -1;
	char buffer[4096];

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && reintentos > 0)
	{
		do{
			printf("%s",mensaje);
			if(myGets(buffer,sizeof(buffer))==0 && strlen(buffer) < len)
			{
				strncpy(pResultado,buffer,len-1);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}
/*
 * \brief solicita una cadena de valores.
 * \param puntero con la cadena.
 * \param mensaje para solicitar la cadena..
 * \param mensaje de error si no cumple las condiciones preestablecidas.
 * \param cantidad de reintentos para introducir un valor válido.
 * \return 0 si ha salido ok. -1 si no.
 */
int utn_getLetrasYEspacios(char* pResultado,
							int len,
							char* mensaje,
							char* mensajeError,
							int reintentos)
{
	int retorno = -1;
	char buffer[4096];
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && reintentos > 0)
	{
		do{
			printf("%s",mensaje);
			if(getLetrasYEspacios(buffer, len)==0  && strlen(buffer) < len)
			{
				strncpy(pResultado,buffer,len-1);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}

static int isCuit(char *cadena)
{
	int retorno;
	int contadorLugares=0;
	if(cadena != NULL && strlen(cadena) > 0 && cadena[2] == '-' && cadena[11] == '-' && cadena[12] != '\0')
	{
		retorno = 1;
		for(int i = 0;cadena[i] != '\0'; i++)
		{
			if(cadena[i] == '-')
			{
				contadorLugares++;
			}
			if(contadorLugares>2 || ((cadena[i] < '0' || cadena[i] > '9') && cadena[i] != '-'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
int utn_getCuit(char* pResultado, char* mensaje, char* mensajeError, int reintentos, int len)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];

	//(myGets(bufferString, ARRAY_SIZE) == 0 && isCuit(bufferString) == 1 && strnlen(bufferString, sizeof(bufferString)) < limit)

		if(mensaje != NULL && mensajeError != NULL && pResultado != NULL && reintentos >= 0)
		{
			do
			{
				printf("\n%s", mensaje);
				if(!myGets(bufferString, ARRAY_SIZE) &&
						isCuit(bufferString) == 1 &&
						strnlen(bufferString, sizeof(bufferString)) < len)
				{
					retorno = 0;
					strncpy(pResultado, bufferString, len);
					break;
				}
				else
				{
					printf("%s", mensajeError);
					reintentos--;
				}
			}while(reintentos>= 0);
		}

	return retorno;
}



