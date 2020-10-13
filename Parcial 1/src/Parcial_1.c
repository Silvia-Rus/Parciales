/*
 ============================================================================
 Name        : Parcial_1.c
 Author      : Silvia Rus Mata
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "cliente.h"
#include "publicacion.h"
#include "informes.h"
#include "getData.h"

#define LEN_CLI 100
#define LEN_PUB 1000
#define INTENTOS 3
#define CUIT_SIZE 14

int main(void)
{
	setbuf(stdout, NULL);
	int respuesta;
	int idBajaCliente;
	int confirmacion;
	int respuestaInformes;
	Cliente clienteList[LEN_CLI];
	Publicacion publicacionList[LEN_PUB];

	printf("---¡¡Bienvenido al Sistema de Avisos!!----\n\n");
	if(!cli_initList(clienteList, LEN_CLI)&&
		!pub_initList(publicacionList, LEN_PUB ))
	{
		cli_cargaAutomatica(clienteList);
		pub_cargaAutomatica(publicacionList);
		do{
			if(!utn_getNumeroInt(&respuesta,
								"\n\nMENÚ PRINCIPAL:\n"
								"Ingrese un número del 1 al 5:\n"
								"1-Para dar de alta a un cliente.\n"
								"2-Para modificar los datos de un cliente.\n"
								"3-Para dar de baja un cliente.\n"
								"4-Para crear un nuevo aviso.\n"
								"5-Para pausar una publicación.\n"
								"6-Para reanudar una publicación.\n"
								"7-Para imprimir todos los clientes con sus avisos.\n"
								"8-Para informes (explore opciones).\n"
								"9-Para salir.\n",
								"\n\nERROR\n\n\n",
								1,
								9,
								INTENTOS))
			{
				switch(respuesta)
				{
					case 1://ALTA CLIENTES
						if(cli_altaRegistro(clienteList, LEN_CLI))
						{
							printf("Error en la carga.");
						}
						break;
					case 2://MODIFICACIÓN CLIENTES
						if(cli_modify(clienteList, LEN_CLI))
						{
							printf("No hay registros dados de alta en la base de datos.\n\n");
						}
						break;
					case 3://DAR DE BAJA UN CLIENTE
						if(!utn_getNumeroInt(&idBajaCliente,
											"\nIngrese el ID del cliente que desee dar de baja. ",
											"\nError. El ID debe ser númerico.: ",
											0,
											INT_MAX,
											INTENTOS) &&
								//hacerlo by index
							cli_findById(clienteList, LEN_CLI, idBajaCliente)>-1 &&
							!inf_printPublicacionbyIdCliente(publicacionList,
															LEN_PUB,
															clienteList,
															LEN_CLI,
															idBajaCliente) &&
							!utn_getNumeroInt(&confirmacion, //la pregunta de confirmación
												"\n¿Está seguro de que desea dar de baja al cliente y todas sus publicaciones?\n"
												"Pulse 0 para salir. Pulse 1 para confirmar.\n",
												"\nERROR. Pulse 0 para salir. Pulse 1 para confirmar. : ",
												0,
												1,
												INTENTOS))
						{
							if(confirmacion==1)
							{
								if(!cli_bajaById(clienteList, LEN_CLI, idBajaCliente) &&
									!pub_bajaByIdCliente(publicacionList,LEN_PUB, idBajaCliente))
								{
									printf("Volviendo al menú principal...");
								}

							}
							else
							{
								printf("NO se ha hecho ninguna modificación.");
							}

						}else
						{
							printf("No existe ningún cliente con ese ID en la base de datos.");
						}
						break;
					case 4://DAR DE ALTA UN AVISO
						if(pub_altaRegistro(publicacionList, LEN_PUB, clienteList, LEN_CLI))
						{
							printf("No se cargó ningún aviso.\n\n");
						}
						break;
					case 5://PAUSAR UNA PUBLICACIÓN
						if(!pub_pausarActivarPublicacion(publicacionList, LEN_PUB, clienteList, LEN_CLI, 1))
						{
							printf("\nVolviendo al menú principal...\n");
						}

						break;
					case 6://REANUDAR UNA PUBLICACIÓN
						if(!pub_pausarActivarPublicacion(publicacionList, LEN_PUB, clienteList, LEN_CLI, 0))
						{
							printf("\nVolviendo al menú principal...\n");
						}
						break;
					case 7://IMPRIMIR LISTA DE CLIENTES CON SUS AVISOS

						if(!inf_printSumaAvisosActivosByCliente(publicacionList, LEN_PUB, clienteList, LEN_CLI))
						{
							printf("\nVolviendo al menú principal...\n");
						}
						break;
					case 8://SACAR INFORMES

						do
						{

						if(!utn_getNumeroInt(&respuestaInformes,
											"\n\nMENÚ INFORMES:\n"
											"Ingrese un número del 1 al 4:\n"
											"1-Cliente con más publicaciones.\n"
											"2-Cantidad de avisos pausados.\n"
											"3-Rubro con más avisos.\n"
											"4-Para salir.\n",
											"\n\nERROR.\n\n\n",
											1,
											4,
											INTENTOS))
						{
							switch(respuestaInformes)
							{
							case 1:
							{
								if(inf_clienteConMasAvisos(clienteList, LEN_CLI, publicacionList, LEN_PUB))
								{
									printf("\nVolviendo al menú principal...");
								}
							}
								break;

							case 2:
								if(inf_printTotalPausadas(publicacionList, LEN_PUB))
								{
									printf("\nVolviendo al menú principal...");
								}
								break;

							case 3:
								if(inf_rubroConMasAvisos(publicacionList, LEN_PUB, 1))
								{
									printf("\nVolviendo al menú principal...");
								}
								break;
							}
						}
						}while(respuestaInformes!=4);
				}
			}
			else
			{
				printf("Excedió el número de intentos");
				break;
			}
		}while(respuesta!=9);
	}

	printf("¡Hasta la próxima!");
	return EXIT_SUCCESS;
}


