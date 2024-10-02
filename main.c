#include "MemMap.h"
#include "StdTypes.h"

#include "MCAL/DIO_int.h"
#include "MCAL/DIO_private.h"
#include "MCAL/ADC_int.h"

#include "Motor_int.h"
#include "LCD_int.h"
#include "Keypad_int.h"
#include "Sensors_int.h"
#include "Function.h"

#define  F_CPU 16000000
#include "util/delay.h"

void Volume_POT(u8 POTRead){
	u8 Vol;
	Vol= ((u16)POTRead*16)/100;
	if(POTRead==99){Vol++;}
	for(u8 i=0;i<Vol;i++){
		LCD_CallFromCGRAM(CChar_3);
	}

}

void LedsLight(){
	u8 led,Dark;
	led=((8*(u32)POT_GetRead())/100);
	Dark=8-led;
	for(u8 i=0;i<Dark;i++){
		CLR_BIT(PORTC,i);
	}
	for(u8 i=7;i>=Dark;i--){
		SET_BIT(PORTC,i);
	}
}



int main(void)
{

	DIO_Init();
	LCD_Init();
	KEYPAD_Init();
	
	u8 k,From=Dec,To=Dec,num=0 ,strBinary[8]="0",i=0, fb=0, strHex[2]="0" ,j=0, fh=0;
	s8 Flag=0,Flag2=1 ,start=0 , Again=0 , Elappr=0 ,GoFrom=0 , GoTo=0 ;
	while(1)
	{
		if(Again==0){
			if(Elappr==0){
			LCD_WriteString((u8*)"  Converter BY");
			LCD_SetCursor(line_2,4);
			LCD_WriteString((u8*)"Elsayed");
			_delay_ms(1500);
			Elappr=1;
			}
			LCD_Clear();
			LCD_WriteString((u8*)" Converter From");
			LCD_SetCursor(line_2,0);
			LCD_WriteString((u8*)"1-D   2-B   3-H");
			Again=1;
		}
		k=0;
		k=KEYPAD_GetKey();
		if(k!=No_KEY){
			if(k=='c')
			{
				LCD_Clear();
				Again=0;
				Elappr=0;
				Flag=0;
				Flag2=1 ;
				start=0;
				num=0;
				From=Dec;
				To=Dec;
				i=0;
				fb=0;
				j=0;
				fh=0;
			}
			if(k=='D'){
				if(GoFrom==1){
					Again=0;
					GoFrom=0;
					GoTo=0;
					Flag=0;
					num=0;
					From=Dec;
					To=Dec;
					i=0;
					fb=0;
					j=0;
					fh=0;				
				}else if(GoTo==1){
					Flag=1;
					start=0;
					LCD_Clear();
					LCD_WriteString((u8*)" Converter To");
					LCD_SetCursor(line_2,0);
					LCD_WriteString((u8*)"1-D   2-B   3-H");
					GoFrom=1;
					GoTo=0;
		      		num=0;
		      		From=Dec;
		      		To=Dec;
		      		i=0;
		      		fb=0;
		      		j=0;
		      		fh=0;									    
				}	
			}
			if(start==0){
				if(k>=Dec && Flag==0 && k<=Hexa ){
					From=k;
					Flag=1;
					LCD_Clear();
					LCD_WriteString((u8*)" Converter To");
					LCD_SetCursor(line_2,0);
					LCD_WriteString((u8*)"1-D   2-B   3-H");
					GoFrom=1;
					GoTo=0;
				}
				else if(k>=Dec && k<=Hexa && Flag==1 )
				{
						To=k;
						GoTo=1;
					    GoFrom=0;
					switch(From){						
						case Dec:	LCD_Clear();
						LCD_WriteString((u8*)"Dec:");
						LCD_SetCursor(line_2,0);
						if(To==Hexa){
							LCD_WriteString((u8*)"Hexa:");
							Flag2=0;
							Flag=-1;
							start=1;
							LCD_SetCursor(line_1,4);
							}else if(To==Binary){
							LCD_WriteString((u8*)"Binary:");
							Flag2=0;
							Flag=-1;
							start=1;
							LCD_SetCursor(line_1,4);
 							}else{
								 GoFrom=1;
								 GoTo=0;
								 LCD_Clear();
								 LCD_WriteString((u8*)" Converter To");
								 LCD_SetCursor(line_2,0);
								 LCD_WriteString((u8*)"1-D   2-B   3-H");
							 }
						     break;
						case Binary:
						LCD_Clear();
						LCD_WriteString((u8*)"Binary:");
						LCD_SetCursor(line_2,0);
						if(To==Dec){
							LCD_WriteString((u8*)"Dec:");
							Flag2=0;
							Flag=-1;
							start=1;
							LCD_SetCursor(line_1,7);
							}else if(To==Hexa){
							LCD_WriteString((u8*)"Hexa:");
							Flag2=0;
							Flag=-1;
							start=1;
							LCD_SetCursor(line_1,7);
							}else{
						    GoFrom=1;
							GoTo=0;
							LCD_Clear();
							LCD_WriteString((u8*)" Converter To");
							LCD_SetCursor(line_2,0);
							LCD_WriteString((u8*)"1-D   2-B   3-H");
						}
						break;
						
						case Hexa:
						LCD_Clear();
						LCD_WriteString((u8*)"Hexa:");
						LCD_SetCursor(line_2,0);
						if(To==Dec){
							LCD_WriteString((u8*)"Dec:");
							Flag2=0;
							Flag=-1;
							start=1;
							LCD_SetCursor(line_1,5);
							}else if(To==Binary){
							LCD_WriteString((u8*)"Binary:");
							Flag2=0;
							Flag=-1;
							start=1;
							LCD_SetCursor(line_1,5);
							}else{
							GoFrom=1;
							GoTo=0;								
							LCD_Clear();
							LCD_WriteString((u8*)" Converter To");
							LCD_SetCursor(line_2,0);
							LCD_WriteString((u8*)"1-D   2-B   3-H");
						}
						break;
						default:
						break;
					}
				}
				}else{
				switch(From){
					case Dec :    if (k>='0' && k<='9'&& Flag2==0 ){
						LCD_WriteChar(k);
						num= num*10 +k - '0';
					}
					break;
					
					case Binary : if (k>='0' && k<='1' && fb==0){
						strBinary[i]=k;
						i++;
						LCD_WriteChar(k);
						if(i==8){
							i=0;
							fb=1;
						}
					}
					break;
					case Hexa :	 if(k!='='  && fh==0){
						LCD_WriteChar(k);
						strHex[j]=k;
						j++;
						if(j==2){
							j=0;
							fh=1;
						}
					}
					break;
				}
				
				if(k=='=' && Flag2==0){
					
					switch(To){
						case Dec : if(From == Binary){
							u8 b=BinaryToDecimal(strBinary);
							LCD_SetCursor(line_2,5);
							LCD_WriteNumber(b);
							}else{
							u8 b=HexaToDecimal(strHex);
							LCD_SetCursor(line_2,4);
							LCD_WriteNumber(b);
						}
						break;
						case Binary : if(From == Dec){
							LCD_SetCursor(line_2,7);
							LCD_WriteBinary(num);
							}else{
							LCD_SetCursor(line_2,7);
							HexaToBinary(strHex);
						}
						break;
						case Hexa : if(From == Dec){
							LCD_SetCursor(line_2,5);
							LCD_WriteHex(num);
							}else{
							LCD_SetCursor(line_2,5);
							BinaryToHexa(strBinary);
						}
						break;
						default: break;
					}
				}
				
			}
		}

	}
}
