#ifndef KEYPAD_INT_H_
#define KEYPAD_INT_H_

#include "Keypad_cfg.h" // i call because  ROW COL Notdefine

typedef struct{
	u8 arr[ROW];
}Keypad_Row_Col;
typedef enum{
	Rows,
	Columns
}ROW_COL;


#define No_KEY 'T'

u8 KEYPADArr[ROW][COL];

void KEYPAD_Init(void);

u8 KEYPAD_GetKey(void);
	






#endif /* KEYPAD_INT_H_ */