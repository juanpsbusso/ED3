/*
 * Copyright 2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here

#include "stdio.h"

// TODO: insert other definitions and declarations here

#define ENTRADA ~(1<<0)
#define SALIDA (1<<0)

void configGPIO(void);
void delay(uint32_t times);
void secuencia1(void);
void secuencia2(void);

int main(void) {

	uint32_t estadoBoton;

	SystemInit();

	//Tenemos que configurar el puerto 0.0 y el puerto 1.0 como GPIO
	//Para colocarlos en modo GPIO, los bits 0:1 de PINSEL0 deben ser 00b0
	//Los bits 0:1 de PINSEL2 deben ser 00b0
	while(1){

		estadoBoton = (LPC_GPIO2->FIOPIN>>ENTRADA) & 0x01;

		//Chequear puerto 1.0, si esta en bajo secuencia1, else secuencia 2

		if(estadoBoton==1){
			secuencia1();
		}else{
			secuencia2();
		}
	}

    return 0 ;
}

//Funcion para configurar los pines, primero los seleccionamos y despues los asignamos como salida y entrada respectivamente

void configGPIO(void) {
	/*PINSEL*/
	LPC_PINCON->PINSEL0 &= ~(0x3<<0);
	LPC_PINCON->PINSEL2 &= ~(0x3<<0);

	/*FIODIR*/
	LPC_GPIO0->FIODIR |= SALIDA;
	LPC_GPIO2->FIODIR |= ENTRADA;
}

// Funcion delay, funciona a partir del parametro times

void delay(uint32_t times) {
	for(uint32_t i=0; i<times; i++)
		for(uint32_t j=0; j<times; j++);
}

// Funcion para la secuencia 1 (10101)

void secuencia1(void){
	/*FIOSET*/
	LPC_GPIO0->FIOSET |= SALIDA;
	delay(1000);
	LPC_GPIO0->FIOCLR |= SALIDA;
	delay(1000);
}


void secuencia2(void){
	/*FIOSET*/
	LPC_GPIO0->FIOCLR |= SALIDA;
	delay(1000);
	LPC_GPIO0->FIOSET |= SALIDA;
	delay(1000);
}
