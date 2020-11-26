/*
 ============================================================================
 Name        : Parcial 2.c
 Author      : Silvia Rus Mata
 ============================================================================
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
#include "informes.h"

int main(void)
{

	setbuf(stdout, NULL);
	int option;

	LinkedList* listaClientes = ll_newLinkedList();
	LinkedList* listaVentas = ll_newLinkedList();

	printf("---¡¡Bienvenido al sistema de carga de clientes y ventas!!---\n");

	if(!controller_loadFromText("listaClientes.txt", listaClientes, parser_clienteFromText) &&
	   !controller_loadFromText("listaVentas.txt", listaVentas, parser_ventaFromText))
	{
		do{
			if(!utn_getNumeroInt(&option,
								"\n\nMENÚ PRINCIPAL:\n"
								"\nIngrese un número del 1 al 8:"
								"\n1-Agregar un cliente. "
								"\n2-Vender afiches. "
								"\n3-Modificar ventas. "
								"\n4-Cobrar venta."
								"\n5-Generar informe de cobros. "
								"\n6-Generar informe de deudas. "
								"\n7-Generar estadísticas. "
								"\n8-Salir del programa. ",
								"\n\nERROR. Ingrese un número del 1 al 8.\n\n\n",
								1,
								8,
								INTENTOS))
			{
				switch(option)
				{
					case 1://agregar unb cliente
						if(!controller_addCliente(listaClientes))
						{
							printf("\nVolviendo al menú principal...");
						}
						break;
					case 2://vender afiches
						if(ll_isEmpty(listaVentas))
						{
							printf("\nAñada primero un cliente.");
						}
						else
						{
							if(!controller_addVenta(listaVentas,listaClientes))
							{
								printf("\nVolviendo al menú principal...");
							}
						}
						break;
					case 3://modificar venta
						if(ll_isEmpty(listaVentas))
						{
							printf("\nAñada primero un cliente.");
						}
						else
						{
							if(ll_isEmpty(listaClientes))
							{
								printf("\nAñada primero una venta.");
							}
							else
							{
								if(!controller_modifyVenta(listaVentas,listaClientes, 1))
								{
									printf("\nVolviendo al menú principal...");
								}
							}
						}
						break;
					case 4://cobrar venta
						if(ll_isEmpty(listaVentas))
						{
							printf("\nAñada primero un cliente.");
						}
						else
						{
							if(ll_isEmpty(listaClientes))
							{
								printf("\nAñada primero una venta.");
							}
							else
							{
								if(!controller_modifyVenta(listaVentas,listaClientes, 2))
								{
									printf("\nVolviendo al menú principal...");
								}
							}
						}
						break;
					case 5://generar informe de cobros
						if(ll_isEmpty(listaVentas))
						{
							printf("\nAñada primero un cliente.");
						}
						else
						{
							if(ll_isEmpty(listaClientes))
							{
								printf("\nAñada primero una venta.");
							}
							else
							{
								if(!informes_informeCobradas(listaVentas,listaClientes, venta_noEstaCobrada, "ventas.txt" ))
								{

									printf("\nVolviendo al menú principal...");
								}
							}
						}

					break;
					case 6://generar informe de deudas
						if(ll_isEmpty(listaVentas))
						{
							printf("\nAñada primero un cliente.");
						}
						else
						{
							if(ll_isEmpty(listaClientes))
							{
								printf("\nAñada primero una venta.");
							}
							else
							{
								if(!informes_informeCobradas(listaVentas,listaClientes, venta_estaCobrada, "a_cobrar.txt" ))
								{
									printf("\nVolviendo al menú principal...");
								}
							}
						}
						break;
					case 7://generar estadísticas
						if(ll_isEmpty(listaVentas))
						{
							printf("\nAñada primero un cliente.");
						}
						else
						{
							if(ll_isEmpty(listaClientes))
							{
								printf("\nAñada primero una venta.");
							}
							else
							{
								if(!informes_clienteCantidadMasAlta(listaVentas, listaClientes,1) &&
								   !informes_clienteCantidadMasAlta(listaVentas, listaClientes,0) &&
								   !informes_ventaConVentaMasAlta(listaVentas, listaClientes))
								{

									printf("\nVolviendo al menú principal...");
								}
							}
						}
						break;
				}
			}
		}while(option!=8);
	}
	controller_saveClienteAsText("listaClientes.txt",listaClientes);
	controller_saveVentaAsText("listaVentas.txt", listaVentas);

	printf("¡Hasta la próxima!");
	ll_deleteLinkedList(listaClientes);
	return EXIT_SUCCESS;
}
