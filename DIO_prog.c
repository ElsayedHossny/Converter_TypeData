#include "StdTypes.h"
#include "MemMap.h"

#include "DIO_int.h"
#include "DIO_private.h"

volatile u8*RegArr[4][3]={  {&DDRA,&PORTA,&PINA},
{&DDRB,&PORTB,&PINB},
{&DDRC,&PORTC,&PINC},
{&DDRD,&PORTD,&PIND}
};


/*****************************Driver_For_(pin)-Use*****************************/
void DIO_Init(void)
{
	DIO_Pin_t i;
	for (i=PINA0;i<TOTAL_PINS ;i++)
	{
		DIO_InitPin(i,PinsStatusArr[i]);
	}
	
}

void DIO_InitPin(DIO_Pin_t pin,DIO_PinStatus_t status)
{
	DIO_Port_t port=pin/8;
	u8 pin_num=pin%8;
			switch(status)
			{
				case OUTPUT:SET_BIT(*RegArr[port][DDR],pin_num);	CLR_BIT(*RegArr[port][PORT],pin_num);	break;
				case INFREE:CLR_BIT(*RegArr[port][DDR],pin_num);	CLR_BIT(*RegArr[port][PORT],pin_num);	break;				
				case INPULL:CLR_BIT(*RegArr[port][DDR],pin_num);	SET_BIT(*RegArr[port][PORT],pin_num);	break;	
			}
}

void DIO_WritePin(DIO_Pin_t pin , DIO_Voltage_t Volt){
			DIO_Port_t port = pin/8;
			u8 pin_num =pin %8;
			if(Volt==HIGH){
				SET_BIT(*RegArr[port][PORT],pin_num);
				}
			else if (Volt==LOW){
				ClrPin(*RegArr[port][PORT],pin_num);
				}			
}

DIO_Voltage_t DIO_ReadPin(DIO_Pin_t pin){
			DIO_Port_t port = pin/8;
			u8 pin_num =pin %8;
			DIO_Voltage_t volt=HIGH;		
			volt = GetPin(*RegArr[port][PIN],pin_num);
			return volt;
}

void DIO_TogglePin(DIO_Pin_t pin){
				DIO_Port_t port = pin/8;
				u8 pin_num =pin %8;
				togglepin(*RegArr[port][PORT],pin_num);
}


/*****************************Driver_For_(Port)-Task*****************************/
void DIO_WritePort(DIO_Port_t port , u8 data){

	switch(port){
		case PA:
		DDRA=0xff;
		PORTA=data;
		break;
		case PB:
		DDRB=0xff;
		PORTB=data;
		break;
		case PC:
		DDRC=0xff;
		PORTC=data;
		break;
		case PD:
		DDRD=0xff;
		PORTD=data;
		break;
	}
	
}

u8 DIO_ReadPort(DIO_Port_t port){

	u8 Data=0;
	switch(port){
		
		case PA:
		DDRA=0x00;
		Data=PINA;
		break;
		case PB:
		DDRB=0x00;
		Data=PINB;
		break;
		case PC:
		DDRC=0x00;
		Data=PINC;
		break;
		case PD:
		DDRD=0x00;
		Data=PIND;
		break;
	}

	return Data;
}

