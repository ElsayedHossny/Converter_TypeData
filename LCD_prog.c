#include "StdTypes.h"
#include "DIO_int.h"

#include "LCD_cfg.h"
#include "LCD_private.h"
#include "LCD_int.h"


#define  F_CPU 16000000
#include "util/delay.h"


#if LCD_mode==_8_BIT
 
static  void writeIns(u8 ins)
{
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(RS,LOW);  // 0->for instruction
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

static void writeData(u8 data)
{
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(RS,HIGH);  // 1->for Data
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void){
	
	_delay_ms(50);
	writeIns(0x38); // Function Set
	writeIns(0x0c); // Display on/off control
	writeIns(0x01); // clear LCD
	_delay_ms(1);
	writeIns(0x06); // Entry Mode Set (inc DDRAM ADDRESS)
}

#elif LCD_mode == _4_BIT

static  void writeIns(u8 ins)
{
	DIO_WritePin(RS,LOW);  // 0->for instruction	

				DIO_WritePin(D7,GET_BIT(ins,7)); // j=7 , 3
				DIO_WritePin(D6,GET_BIT(ins,(6))); // j=6 , 2
				DIO_WritePin(D5,GET_BIT(ins,(5))); // j=5 , 1
				DIO_WritePin(D4,GET_BIT(ins,(4))); //j=4 , 0
				DIO_WritePin(EN,HIGH);
				_delay_ms(1);
				DIO_WritePin(EN,LOW);
				_delay_ms(1);
		       DIO_WritePin(D7,GET_BIT(ins,3));
		       DIO_WritePin(D6,GET_BIT(ins,(2)));
		       DIO_WritePin(D5,GET_BIT(ins,(1)));
		       DIO_WritePin(D4,GET_BIT(ins,(0)));	
			   DIO_WritePin(EN,HIGH);
			   _delay_ms(1);
			   DIO_WritePin(EN,LOW);
			   _delay_ms(1);
}

static void writeData(u8 data)
{
	DIO_WritePin(RS,HIGH);  // 1->for instruction

		DIO_WritePin(D7,GET_BIT(data,7)); 
		DIO_WritePin(D6,GET_BIT(data,(6)));
		DIO_WritePin(D5,GET_BIT(data,(5))); 
		DIO_WritePin(D4,GET_BIT(data,(4))); 
		DIO_WritePin(EN,HIGH);
		_delay_ms(1);
		DIO_WritePin(EN,LOW);
		_delay_ms(1);
		DIO_WritePin(D7,GET_BIT(data,3));
		DIO_WritePin(D6,GET_BIT(data,(2)));
		DIO_WritePin(D5,GET_BIT(data,(1)));
		DIO_WritePin(D4,GET_BIT(data,(0)));
		DIO_WritePin(EN,HIGH);
		_delay_ms(1);
		DIO_WritePin(EN,LOW);
		_delay_ms(1);		

}

void LCD_Init(void){
	
	_delay_ms(50); 
	
	writeIns(0x02);// Function Set
	writeIns(0x28);// Function Set
	
	writeIns(0x0c); // Display on/off control
	writeIns(0x01); // clear LCD
	_delay_ms(1);
	writeIns(0x06); // Entry Mode Set (inc DDRAM ADDRESS)
}

#endif



void LCD_WriteNumber(s32 num)
{

	u8 i,str[20];
		s8 j;
		i=0;
		if (num==0)
		{
			LCD_WriteChar('0');
		}
		else{
		if (num<0)
		{
			LCD_WriteChar('-');
			num=-num;
		}
		while(num)
		{
			str[i]=num%10+'0';
			num=num/10;
			i++;
		}
		for (j=i-1;j>=0;j--)
		{
			LCD_WriteChar(str[j]);
		}
		
		}
}


void LCD_WriteNumber4d(s16 num){
	
	u8 i,str[4]={'0','0','0','0'};
	s8 j;
	i=0;
	if (num==0)
	{
		LCD_WriteChar('0');
	}
	else{
		if (num<0)
		{
			LCD_WriteChar('-');
			num=-num;
		}
		while(num)
		{
			str[i]=num%10+'0';
			num=num/10;
			i++;
		}
		for (j=0;j<4;j++)
		{
			LCD_WriteChar(str[3-j]);
		}
		
	}
	
	
}

void LCD_WriteBinary(u8 num){
	
	for (s8 i=7;i>=0;i--){
		
		LCD_WriteChar(GET_BIT(num,i)+'0');
		
	}
}

void LCD_WriteHex(u8 num){
	u8 LN=num & 0x0f;
	u8 HN=num>>4;
	
	if(HN<10){
		LCD_WriteChar(HN + '0');
		}else{
		LCD_WriteChar( HN - 10 +'A');
	}
	if(LN<10){
		LCD_WriteChar(LN + '0');
		}else{
		LCD_WriteChar( LN - 10 +'A');
	}
}

void LCD_SetCursor(LCD_NumLine_t line,u8 cell)
{
	 u8 lpline = 0x00;
	switch(line){
		case line_1: lpline = Cursor_line1; break;
		case line_2: lpline = Cursor_line2; break;
		case line_3: lpline = Cursor_line3; break;
		case line_4: lpline = Cursor_line4; break;
		default: break;
	}	
	if(cell<=15){
	writeIns((( 0x80 | lpline ) | cell));
	}
}

void LCD_WriteChar(u8 ch){
	writeData(ch);
}

void LCD_WriteString( u8*str ){
	
	u8 i;
	for(i=0;str[i];i++){
		writeData(str[i]);
	}
}

void LCD_Clear(void){
		writeIns(0x01); // clear LCD
		_delay_ms(1);
}



LCD_CChar_Data CCharArr[8]={
 [CChar_1] = {
	 .u8Data ={
		 0x04,
		 0x0A,
		 0x04,
		 0x0E,
		 0x15,
		 0x04,
		 0x0A,
		 0x0A
	 },
 },
 [CChar_2] = {
	 .u8Data = {  0x00,
		 0x00,
		 0x00,
		 0x0C,
		 0x0C,
		 0x00,
		 0x00,
		 0x00},
 },
 [CChar_3] = {
	 .u8Data =  {  
  0x0E,
  0x0E,
  0x0E,
  0x0E,
  0x0E,
  0x0E,
  0x0E,
  0x0E
		 },
 },
 [CChar_4] = {
	 .u8Data ={0x00, 0x0A, 0x1F, 0x1F, 0x0E, 0x04, 0x00, 0x00},
 },
 [CChar_5] = {
	 .u8Data = {0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00},

 },
 [CChar_6] = {
    .u8Data = {0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00},
},
 [CChar_7] = {
      .u8Data = {0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00},
  },
  [CChar_8] = {
      .u8Data = {0x00, 0x0A, 0x15, 0x11, 0x0A, 0x04, 0x00, 0x00},
  },
  
  };

void LCD_WriteCGRAM (CGRAM_Char CChar){
	
	writeIns(0x40 + (CChar*8));
	
	for(u8 i=0;i<8;i++){
		writeData(CCharArr[CChar].u8Data[i]);
	}
	
	writeIns(0x80); // To Return DDRam  
}

void LCD_CallFromCGRAM (CGRAM_Char CChar){
	
	writeData(CChar);
	
}

void LCD_CGRAM_UPLOAD(void){
	for(u8 i=CChar_1 ; i<=CChar_8 ;i++){
		LCD_WriteCGRAM(i);
	}
}