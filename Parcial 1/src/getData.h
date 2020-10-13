/*
 * getData.h
 *
 *  Created on: 10 oct. 2020
 *      Author: usuario
 */

#ifndef GETDATA_H_
#define GETDATA_H_

int utn_getNumeroInt(int* pResultado, char* mensaje, char* mensajeError, int minimo, int maximo, int reintentos);
int utn_getNumeroFloat(float* pResultado,char* mensaje,char* mensajeError,int minimo,int maximo,int reintentos);
int utn_getCadena(char* pResultado, int len, char* mensaje, char* mensajeError, int reintentos);
int utn_getLetrasYEspacios(char* pResultado, int len, char* mensaje, char* mensajeError, int reintentos);
int utn_getCuit(char* pResultado, char* mensaje, char* mensajeError, int reintentos, int len);

#endif /* GETDATA_H_ */
