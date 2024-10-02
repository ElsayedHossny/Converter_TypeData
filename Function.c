#include "MemMap.h"
#include "StdTypes.h"

#include "LCD_int.h"
#include "Function.h"


/*************************************Converter_project******************************************/

u8 BinaryToDecimal(u8 *str){
	
	u32 dec = 0;
	s8 i = 7 , j=0;
	int rem;

	while (i>=0) {

		// get remainder of n divided by 10
		rem = str[i] -'0';

		// add the rem * (2 ^ i) to dec
		dec += rem << j; // Using bitwise shift instead of pow

		// dencrement i
		j++;
		i--;
	}

	return dec;
}

void BinaryToHexa(u8 *str){
	u8 dec= BinaryToDecimal(str);
	LCD_WriteHex(dec);
}

u8 HexaToDecimal(u8 *str){
	
	u16 num=0 ,res=0;
	for(s8 i=1 ; i>=0 ; i--){
		if(str[i] >= 'A'){
			num = str[i]-'A'+10;
		}else{
			num = str[i] - '0';
		}
		if(i==0){
			num=num*16;
		}
		res = res+num;
	}
	return res;
}

void HexaToBinary(u8 *str){
	u8 dec=HexaToDecimal(str);
	LCD_WriteBinary(dec);
}
