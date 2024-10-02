

#define KEYPADArr_Prog
#include "StdTypes.h"
#include "DIO_int.h"

#include "Keypad_cfg.h"

#include "Keypad_int.h"

#define  F_CPU 16000000
#include "util/delay.h"




Keypad_Row_Col KEY_ROW_COL[2]={ [Rows]= {.arr={PINB4,PINB5,PINB6,PINB7}},
								[Columns]={.arr={PIND2,PIND3,PIND4,PIND5}}
									};

void KEYPAD_Init(void){
	for(u8 r=0;r<ROW;r++){
		DIO_WritePin(KEY_ROW_COL[Rows].arr[r],HIGH);
	}
}

u8 KEYPAD_GetKey(void)
{
	u8 R,C,k=No_KEY;
	for(R=0;R<ROW;R++)
	{
		DIO_WritePin(KEY_ROW_COL[Rows].arr[R],LOW);
		for(C=0;C<COL;C++)
		{
			if(DIO_ReadPin(KEY_ROW_COL[Columns].arr[C])==LOW)
			{
				k= KEYPADArr[R][C];
				_delay_ms(30);
				while(DIO_ReadPin(KEY_ROW_COL[Columns].arr[C])==LOW);
				_delay_ms(30);
	
			}
		}
			DIO_WritePin(KEY_ROW_COL[Rows].arr[R],HIGH);
	}
	return k;
}
