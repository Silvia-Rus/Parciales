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

	printf("---��Bienvenido al Sistema de Avisos!!----\n\n");
	if(!cli_initList(clienteList, LEN_CLI)&&
		!pub_initList(publicacionList, LEN_PUB ))
	{
		//cli_cargaAutomatica(clienteList);
		//pub_cargaAutomatica(publicacionList);
		do{
			if(!utn_getNumeroInt(&respuesta,
								"\n\nMEN� PRINCIPAL:\n"
								"Ingrese un n�mero del 1 al 5:\n"
								"1-Para dar de alta a un cliente.\n"
								"2-Para modificar los datos de un cliente.\n"
								"3-Para dar de baja un cliente.\n"
								"4-Para crear un nuevo aviso.\n"
								"5-Para pausar una publicaci�n.\n"
								"6-Para reanudar una publicaci�n.\n"
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
							printf("\nIntentos agotados.");
						}
						break;
					case 2://MODIFICACI�N CLIENTES
						if(cli_modify(clienteList, LEN_CLI))
						{
							printf("No hay registros dados de alta en la base de datos.\n\n");
						}
						break;
					case 3://DAR DE BAJA UN CLIENTE

						if(cli_isEmpty(clienteList, LEN_CLI)==1)
						{
							printf("No hay ning�n cliente en la base de datos");
						}
						else
						{
							if(!utn_getNumeroInt(&idBajaCliente,
												"\nIngrese el ID del cliente que desee dar de baja. ",
												"\nError. El ID debe ser n�merico.: ",
												0,
												INT_MAX,
												INTENTOS) &&
								cli_findById(clienteList, LEN_CLI, idBajaCliente)>-1 &&
								!inf_printPublicacionbyIdCliente(publicacionList,
																LEN_PUB,
																clienteList,
																LEN_CLI,
																idBajaCliente) &&
								!utn_getNumeroInt(&confirmacion, //la pregunta de confirmaci�n
													"\n�Est� seguro de que desea dar de baja al cliente y todas sus publicaciones?\n"
													"Pulse 0 para salir. Pulse 1 para confirmar.\n",
													"\nERROR. Pulse 0 para salir. Pulse 1 para confirmar. : ",
													0,
													1,
													INTENTOS))
							{
								if(confirmacion==1)
								{
									if(!pub_bajaByIdCliente(publicacionList,LEN_PUB, idBajaCliente) ||
									!cli_bajaById(clienteList, LEN_CLI, idBajaCliente))

									{
										printf("Volviendo al men� principal...");
									}
								}
								else
								{
									printf("NO se ha hecho ninguna modificaci�n.");
								}

							}else
							{

								if(cli_findById(clienteList, LEN_CLI, idBajaCliente)<-1)
								{
									printf("No existe ning�n cliente con ese ID en la base de datos.");
								}
								else
								{
									if(inf_printPublicacionbyIdCliente(publicacionList,
																			LEN_PUB,
																			clienteList,
																			LEN_CLI,
																			idBajaCliente))
									{
										printf("Sin avisos para imprimir.");

									}
								}

							}
						}
						break;
					case 4://DAR DE ALTA UN AVISO
						if(!pub_altaRegistro(publicacionList, LEN_PUB, clienteList, LEN_CLI))
						{
							printf("Volviendo al men� principal...\n\n");
						}
						break;
					case 5://PAUSAR UNA PUBLICACI�N
						if(!pub_pausarActivarPublicacion(publicacionList, LEN_PUB, clienteList, LEN_CLI, 1))
						{
							printf("\nVolviendo al men� principal...\n");
						}

						break;
					case 6://REANUDAR UNA PUBLICACI�N
						if(!pub_pausarActivarPublicacion(publicacionList, LEN_PUB, clienteList, LEN_CLI, 0))
						{
							printf("\nVolviendo al men� principal...\n");
						}
						break;
					case 7://IMPRIMIR LISTA DE CLIENTES CON SUS AVISOS

						if(!inf_printSumaAvisosActivosByCliente(publicacionList, LEN_PUB, clienteList, LEN_CLI))
						{
							printf("\nVolviendo al men� principal...\n");
						}
						break;
					case 8://SACAR INFORMES
						do
						{

						if(!utn_getNumeroInt(&respuestaInformes,
											"\n\nMEN� INFORMES:\n"
											"Ingrese un n�mero del 1 al 4:\n"
											"1-Cliente con m�s publicaciones.\n"
											"2-Cantidad de avisos pausados.\n"
											"3-Rubro con m�s avisos.\n"
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
									printf("\nVolviendo al men� principal...");
								}
							}
								break;

							case 2:
								if(inf_printTotalPausadas(publicacionList, LEN_PUB))
								{
									printf("\nVolviendo al men� principal...");
								}
								break;
							case 3:
								if(inf_rubroConMasAvisos(publicacionList, LEN_PUB))
								{
									printf("\nVolviendo al men� principal...");
								}
								break;
							}
						}
					}while(respuestaInformes!=4);
				}
			}
			else
			{
				printf("Excedi� el n�mero de intentos");
				break;
			}
		}while(respuesta!=9);
	}
	printf("�Hasta la pr�xima!");
	return EXIT_SUCCESS;
}


