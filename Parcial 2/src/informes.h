/*
 * informes.h
 *
 *  Created on: 26 nov. 2020
 *      Author: Silvia Rus Mata
 */

#ifndef INFORMES_H_
#define INFORMES_H_

int informes_informeCobradas(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente, int (pFunc)(void*),char* nombreArchivo);
int informes_cantidadTotalPorCliente(LinkedList* clientList, LinkedList* sellList, int idCliente, int* cantidad);
int informes_cantidadMasAlta(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente, int* pMaximo, int* pMinimo);
int informes_numeroVentaMasAlta(LinkedList* pArrayListVenta, int* pVentaMasAlta);
int informes_clienteCantidadMasAlta(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente, int maxMin);
int informes_ventaConVentaMasAlta(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente);



#endif /* INFORMES_H_ */
