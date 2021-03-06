/*
 *
 * Xilinx, Inc.
 * XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" AS A 
 * COURTESY TO YOU.  BY PROVIDING THIS DESIGN, CODE, OR INFORMATION AS
 * ONE POSSIBLE   IMPLEMENTATION OF THIS FEATURE, APPLICATION OR 
 * STANDARD, XILINX IS MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION 
 * IS FREE FROM ANY CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE 
 * FOR OBTAINING ANY RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION
 * XILINX EXPRESSLY DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO 
 * THE ADEQUACY OF THE IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO 
 * ANY WARRANTIES OR REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE 
 * FROM CLAIMS OF INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY 
 * AND FITNESS FOR A PARTICULAR PURPOSE.
 */

/*
 * 
 *
 * This file is a generated sample test application.
 *
 * This application is intended to test and/or illustrate some 
 * functionality of your system.  The contents of this file may
 * vary depending on the IP in your system and may use existing
 * IP driver functions.  These drivers will be generated in your
 * SDK application project when you run the "Generate Libraries" menu item.
 *
 */

#include <stdio.h>
#include "xparameters.h"
#include "xil_cache.h"
#include "xuartlite.h"
#include "xbasic_types.h"
#include "xgpio.h"
//#include "my_keypad.h"
#include "my_lcd.h"
#include "my_multiple_periferic.h"
//#include "my_speaker.h"
//#include "my_motor.h"
/*#include "gpio_header.h"
 */

#include <xstatus.h>

#define XPAR_RS232_UART_1_BASEADDR 0x84000000
#define LEDs_HW_BASEaddress 0x84034000
//#define BASE_ADDRESS_KEYPAD 0x84018000
#define BASE_ADDRESS_LCD 0x84010000
//#define BASE_ADDRESS_SPEAKER 0x84028000
//#define BASE_ADDRESS_MOTOR 0x84014000
#define BASE_ADDRESS_MULTIPLE_PERIFERIC 0x84018000


# define CLEAR_DISPLAY_CMD 0x00000001
# define RETURN_HOME_CMD 0x00000002
# define WRITE_CMD 0x00000200
# define FIRST_ROW 0x00000080
# define SECOND_ROW 0x000000C0

#define SILENCIO 	0x00000000
#define DO 			0x00000BAA
#define RE 			0x00000A64
#define MI 			0x00000942
#define FA 			0x000008BD
#define SOL 		0x000007C9
#define LA 			0x000006F0
#define SI 			0x0000062E

#define OCTAVA 	3

int  N=1;



int getNumber() {

	Xuint8 byte;
	Xuint8 uartBuffer[16];
	Xboolean validNumber;
	int digitIndex;
	int digit, number, sign;
	int c;

	while (1) {
		byte = 0x00;
		digit = 0;
		digitIndex = 0;
		number = 0;
		validNumber = XTRUE;

		//get bytes from uart until RETURN is entered

		while (byte != 0x0d && byte != 0x0A) {
			byte = XUartLite_RecvByte(XPAR_RS232_UART_1_BASEADDR);
			uartBuffer[digitIndex] = byte;
			XUartLite_SendByte(XPAR_RS232_UART_1_BASEADDR, byte);
			digitIndex++;
		}

		//calculate number from string of digits

		for (c = 0; c < (digitIndex - 1); c++) {
			if (c == 0) {
				//check if first byte is a "-"
				if (uartBuffer[c] == 0x2D) {
					sign = -1;
					digit = 0;
				}
				//check if first byte is a digit
				else if ((uartBuffer[c] >> 4) == 0x03) {
					sign = 1;
					digit = (uartBuffer[c] & 0x0F);
				} else
					validNumber = XFALSE;
			} else {
				//check byte is a digit
				if ((uartBuffer[c] >> 4) == 0x03) {
					digit = (uartBuffer[c] & 0x0F);
				} else
					validNumber = XFALSE;
			}
			number = (number * 10) + digit;
		}
		number *= sign;
		if (validNumber == XTRUE) {
			return number;
		}
		print("This is not a valid number.\n\r");
	}
}

void LCD_enviarCMD(Xuint32 cmd) {
	// Comprobamos que la FIFO no est?? llena
	while (MY_LCD_mWriteFIFOFull ( BASE_ADDRESS_LCD)) {
	}
	// Escribimos el comando en la FIFO
	MY_LCD_mWriteToFIFO ( BASE_ADDRESS_LCD , 0, cmd );
}

void LCD_inicializa() {
	MY_LCD_mResetWriteFIFO (BASE_ADDRESS_LCD );
	LCD_enviarCMD(CLEAR_DISPLAY_CMD);
	LCD_enviarCMD(RETURN_HOME_CMD); // moverse al comienzo de la pantalla LCD
	LCD_enviarCMD(WRITE_CMD); // primera escritura
}

void print_numbers(Xuint32 valor) {

	char *n;
	n = malloc(sizeof(char) * 4);
	n += 4;

	if (valor >= 10) {
		*n = valor % 10;
		n--;
		valor = valor / 10;
		*n = valor;
		LCD_enviarCMD(WRITE_CMD + *n + '0');
		n++;
		LCD_enviarCMD(WRITE_CMD + *n + '0');
	} else
		LCD_enviarCMD(WRITE_CMD + valor + '0');
}

void print_lcd() {
	LCD_enviarCMD(WRITE_CMD + ' ');
	LCD_enviarCMD(WRITE_CMD + 'P');
	LCD_enviarCMD(WRITE_CMD + 'i');
	LCD_enviarCMD(WRITE_CMD + 's');
	LCD_enviarCMD(WRITE_CMD + 'o');
	LCD_enviarCMD(WRITE_CMD + ' ');
	LCD_enviarCMD(WRITE_CMD + 'a');
	LCD_enviarCMD(WRITE_CMD + 'c');
	LCD_enviarCMD(WRITE_CMD + 't');
	LCD_enviarCMD(WRITE_CMD + 'u');
	LCD_enviarCMD(WRITE_CMD + 'a');
	LCD_enviarCMD(WRITE_CMD + 'l');
	LCD_enviarCMD(WRITE_CMD + '-');
	LCD_enviarCMD(WRITE_CMD + '>');
}

void print_lcd_second_row(){
	LCD_enviarCMD(SECOND_ROW);
	LCD_enviarCMD(WRITE_CMD + ' ');
	LCD_enviarCMD(WRITE_CMD + 'P');
	LCD_enviarCMD(WRITE_CMD + 'i');
	LCD_enviarCMD(WRITE_CMD + 's');
	LCD_enviarCMD(WRITE_CMD + 'o');
	LCD_enviarCMD(WRITE_CMD + ' ');
	LCD_enviarCMD(WRITE_CMD + 'd');
	LCD_enviarCMD(WRITE_CMD + 'e');
	LCD_enviarCMD(WRITE_CMD + 's');
	LCD_enviarCMD(WRITE_CMD + 't');
	LCD_enviarCMD(WRITE_CMD + '-');
	LCD_enviarCMD(WRITE_CMD + '>');
}
void my_delay(int delay) {
	int i, j;
	for (i = 0; i < delay; i = i + 1)
		for (j = 0; j < 500; j = j + 1) {
		}
}



void ALTAVOZ_suena(Xuint32 nota, Xuint32 octava) {
	MY_MULTIPLE_PERIFERIC_mWriteReg(BASE_ADDRESS_MULTIPLE_PERIFERIC,MY_MULTIPLE_PERIFERIC_SLV_REG1_OFFSET, nota << octava);
}

void musica(){
	Xuint32 Notas[7]={SILENCIO,DO,RE,MI,FA,SOL,LA,SI};
	if(N==8){
		N=1;
	}
	ALTAVOZ_suena(Notas[N], OCTAVA);
	N++;
}
void vuelta_completa(Xuint32 Data){
	int i=0;
	while(i<100){
	MY_MULTIPLE_PERIFERIC_mWriteReg(BASE_ADDRESS_MULTIPLE_PERIFERIC,MY_MULTIPLE_PERIFERIC_SLV_REG2_OFFSET,Data);
	Data = MY_MULTIPLE_PERIFERIC_mReadReg ( BASE_ADDRESS_MULTIPLE_PERIFERIC ,MY_MULTIPLE_PERIFERIC_SLV_REG2_OFFSET);
	while (!( Data & 0x40000000 )) {
	Data = MY_MULTIPLE_PERIFERIC_mReadReg (BASE_ADDRESS_MULTIPLE_PERIFERIC,MY_MULTIPLE_PERIFERIC_SLV_REG2_OFFSET);
	}
	i++;
	}
}



int main() {
	Xuint32 valor;
	Xuint32 old_valor;
	Xuint32 pisoActual = 1;
	Xuint32 Data;
	Xuint32 v=0x00000000;
	Xuint32 suena=0;

	LCD_inicializa();
	MY_MULTIPLE_PERIFERIC_mWriteReg(BASE_ADDRESS_MULTIPLE_PERIFERIC,0,v);

	xil_printf(" Pulse una tecla cualquiera \n\r");

	print_lcd();
	print_numbers(pisoActual);
	while (1) {
		while(valor==0)
		valor = MY_MULTIPLE_PERIFERIC_mReadReg ( BASE_ADDRESS_MULTIPLE_PERIFERIC , 0);
		xil_printf(" Se ha ledio la tecla %X\n\r",valor);
		valor=valor>>28;

		MY_MULTIPLE_PERIFERIC_mWriteReg(BASE_ADDRESS_MULTIPLE_PERIFERIC,0,v);
		while (pisoActual != valor&&valor!=0) {
			xil_printf(" Se ha ledio la tecla %X\n\r",valor);
			if (valor < pisoActual) {
				pisoActual--;
				Data = 0xAE000000;
			} else if(valor>pisoActual){
				pisoActual++;
				Data = 0x2E000000;
			}
			musica();
			suena=1;
			my_delay(2000);

			LCD_inicializa();
			print_lcd();
			print_numbers(pisoActual);
			print_lcd_second_row();
			print_numbers(valor);

			vuelta_completa(Data);
		}
		if (suena){
			MY_MULTIPLE_PERIFERIC_mWriteReg (BASE_ADDRESS_MULTIPLE_PERIFERIC, MY_MULTIPLE_PERIFERIC_SLV_REG1_OFFSET,SILENCIO);
		 suena = 0;
		}
		my_delay(50);
	}



	print("---Exiting main---\n\r");
	//Xil_DCacheDisable();
	//Xil_ICacheDisable();

	return 0;
}

