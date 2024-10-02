/*************************************Converter_project******************************************/
typedef enum{
	Dec='1',
	Binary='2',
	Hexa='3',
}Converter_t;

void HexaToBinary(u8 *str);
u8 HexaToDecimal(u8 *str);
void BinaryToHexa(u8 *str);
u8 BinaryToDecimal(u8 *str);
