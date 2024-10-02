#ifndef LCD_INT_H_
#define LCD_INT_H_




typedef enum{
	line_1=0,
	line_2=1,
	line_3=2,
	line_4=3
}LCD_NumLine_t;

void LCD_Init(void); 


void LCD_WriteNumber(s32 num);
void LCD_WriteBinary(u8 num);
void LCD_WriteHex(u8 num);

void LCD_WriteNumber4d(s16 num);

void LCD_SetCursor(LCD_NumLine_t line,u8 cell);
void LCD_WriteChar(u8 ch);
void LCD_WriteString(u8 *str);
void LCD_Clear(void);
typedef enum{
	
	CChar_1=0,
	CChar_2,
	CChar_3,
	CChar_4,
	CChar_5,
	CChar_6,
	CChar_7,
	CChar_8
	
}CGRAM_Char;

typedef struct{
	u8 u8Data[8];
}LCD_CChar_Data;

void LCD_CGRAM_UPLOAD(void); // input all character
void LCD_CallFromCGRAM (CGRAM_Char CChar);
void LCD_WriteCGRAM (CGRAM_Char CChar); // input one character

#endif /* LCD_INT_H_ */