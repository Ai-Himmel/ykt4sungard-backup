#include	<stdio.h>

/* ‹@í–¼’è‹` */
#define POPLAR_L	0
#define POPLAR_N	1
#define POPLAR_B	2
#define POPLAR_H	3
#define ANZU_L		4

/* ƒ‚ƒgƒ[ƒ‰‚g‚d‚wƒtƒ@ƒCƒ‹(*.mot)
** ‚PƒŒƒR[ƒh‚Ìƒf[ƒ^‚ğæ‚èo‚·\‘¢‘Ì
** ƒŒƒR[ƒh‚Ì\‘¢‚É‚Â‚¢‚Ä‚ÍƒŠƒ“ƒP[ƒWƒGƒfƒBƒ^‚Ìƒ}ƒjƒ…ƒAƒ‹QÆ
*/
struct RecordControl_t {
	unsigned char Type;			/* ƒŒƒR[ƒhí•Ê */
	unsigned char ByteCount;	/* ƒŒƒR[ƒhƒf[ƒ^ƒoƒCƒg”iƒAƒhƒŒƒXAƒ`ƒFƒbƒNƒTƒ€ŠÜ‚Ü‚¸j */
	unsigned long Address;		/* ƒAƒhƒŒƒX */
	unsigned char Data[16];		/* ƒf[ƒ^ */
	unsigned char Sum;			/* ƒ`ƒFƒbƒNƒTƒ€ */
} RecordControl;

/* ƒŒƒR[ƒhí•Ê */
#define RCD_HEADER	(unsigned char)0	/* ƒwƒbƒ_ƒŒƒR[ƒh */
#define RCD_DATA_1	(unsigned char)1	/* ƒf[ƒ^ƒŒƒR[ƒh Load Address      0x00 -     0x0ffff */
#define RCD_DATA_2	(unsigned char)2	/* ƒf[ƒ^ƒŒƒR[ƒh Load Address   0x10000 -   0x0ffffff */
#define RCD_DATA_3	(unsigned char)3	/* ƒf[ƒ^ƒŒƒR[ƒh Load Address 0x1000000 - 0x0ffffffff */
#define RCD_END_1	(unsigned char)4	/* ƒGƒ“ƒhƒŒƒR[ƒh Entry Address      0x00 -     0x0ffff */
#define RCD_END_2	(unsigned char)5	/* ƒGƒ“ƒhƒŒƒR[ƒh Entry Address   0x10000 -   0x0ffffff */
#define RCD_END_3	(unsigned char)6	/* ƒGƒ“ƒhƒŒƒR[ƒh Entry Address 0x1000000 - 0x0ffffffff */

unsigned long GetConvertStartAddress(char *);
void ConvertMotToBin(FILE **, FILE **, unsigned long, unsigned long, unsigned long);
void SetRecordControl(FILE **, FILE **);
unsigned char AsciiToDigit(unsigned char );
void ErrorExit(unsigned char);

FILE *ReadFileHandle;
FILE *WriteFileHandle;
unsigned char record_data[47];

/*************************************************************************
	module		:[ƒ‚ƒgƒ[ƒ‰‚g‚d‚wƒoƒCƒiƒŠ•ÏŠ·ƒƒCƒ“]
	function	:[]
	common		:[]
	condition	:[]
	comment		:[
		‰Šú‰»’l‚Í‚O‚˜‚e‚eŒÅ’è
	]
	return		:[
		0:OK  iDOS‚Ö•Ô‚·j
		1:NG
	]
	machine		:[]
	language	:[MS-C(Ver.6.0)]
	keyword		:[X]
	date		:[1998/03/20]
	author		:[–ì£•qO]
*************************************************************************/
int main(int ac, char *av[])
{
	unsigned long count;
	unsigned long convert_start_address;
	unsigned long convert_end_address;
	unsigned long offset_address;
	unsigned long paste_start_address;

	/* debug */
	RecordControl.Type = 0;
	RecordControl.ByteCount = 0;
	RecordControl.Address = 0;
	for (count = 0; count < 16; count++) {
		RecordControl.Data[count] = 0;
	}
	RecordControl.Sum = 0;

	if (ac == 1) { /* ˆø”‚ª‚È‚¢ */
		ErrorExit(4); /* "Usage"‚ğ•\¦‚µ‚ÄI—¹ */
	}

	/* •ÏŠ·Œ³ƒtƒ@ƒCƒ‹ƒI[ƒvƒ“ */
	if ((ReadFileHandle = fopen(av[4], "r")) == NULL) {
		ErrorExit(0);
	}
	/* •ÏŠ·æƒtƒ@ƒCƒ‹ƒI[ƒvƒ“ */
	WriteFileHandle = fopen(av[5], "wb+");

	printf("\n[1;32m‰Šú‰» ‰Šú’l:0xFF\n");
	for (count = 0; count < 0x100000 ;count++) {
		putc(0xff,WriteFileHandle);
	}

	switch (*av[1]) {
	case '0':/* POPLAR_L */
	case '1':/* POPLAR_N */
		paste_start_address = 0x1000000;
		break;
	case '2':/* POPLAR_B */
	case '3':/* POPLAR_H */
	case '4':/* ANZU_L   */
		paste_start_address = 0x1100000;
		break;
	default:
		ErrorExit(4);
	}

	printf("•ÏŠ·’†\n");
	/* ‚oC‚bC‚b‚f‚q‚n‚lƒZƒNƒVƒ‡ƒ“ ƒoƒCƒiƒŠ•ÏŠ· */
	convert_start_address = GetConvertStartAddress(av[2]);
	convert_end_address = convert_start_address + 0x100000;
	offset_address = 0;
	ConvertMotToBin(&ReadFileHandle,&WriteFileHandle,
	                convert_start_address,
					convert_end_address,
					offset_address);

	/* ‚o‚e‚k‚`‚r‚gƒZƒNƒVƒ‡ƒ“ ƒoƒCƒiƒŠ•ÏŠ· */
	convert_start_address = GetConvertStartAddress(av[3]);
	convert_end_address = convert_start_address + (unsigned long)0x2000;
	offset_address = convert_start_address - paste_start_address;
	ConvertMotToBin(&ReadFileHandle,&WriteFileHandle,
	                convert_start_address,
					convert_end_address,
					offset_address);

	printf("\nI—¹‚µ‚Ü‚µ‚½");

	/* •ÏŠ·Œ³ƒtƒ@ƒCƒ‹ƒNƒ[ƒY */
	fclose(ReadFileHandle);
	/* •ÏŠ·æƒtƒ@ƒCƒ‹ƒNƒ[ƒY */
	fclose(WriteFileHandle);
	/* ³íI—¹ */
	exit(0);
}


/*************************************************************************
	module		:[•¶š—ñ‚ğƒAƒhƒŒƒX‚É•ÏŠ·‚·‚é]
	function	:[]
	common		:[]
	condition	:[]
	comment		:[]
	return		:[
		‚R‚QƒrƒbƒgƒAƒhƒŒƒX
	]
	machine		:[]
	language	:[MS-C(Ver.6.0)]
	keyword		:[FLASH]
	date		:[1998/04/22]
	author		:[–ì£•qO]
*************************************************************************/
unsigned long GetConvertStartAddress(char *src)
{
	unsigned long h = 0;

	while(*src)
	{
		h = h*16 + (((*src >= '0') && (*src <= '9')) ? *src&0x0f : ((*src&0x0f)+9));
		src++;
	}
	return(h);
}

/*************************************************************************
	module		:[w’è”ÍˆÍƒoƒCƒiƒŠ•ÏŠ·]
	function	:[]
	common		:[]
	condition	:[]
	comment		:[]
	return		:[
		END_OK
		END_NG
	]
	machine		:[]
	language	:[MS-C(Ver.6.0)]
	keyword		:[X]
	date		:[1998/03/20]
	author		:[–ì£•qO]
*************************************************************************/
void ConvertMotToBin(
	FILE **src_hdl,
	FILE **dst_hdl,
	unsigned long start_address,
	unsigned long end_address,
	unsigned long offset)
{
	unsigned char digit_count;

	printf("%lx - %lx -> %lx\n",start_address,end_address,offset);

	rewind(*src_hdl);	/* “Ç‚İo‚µˆÊ’u‚ğƒtƒ@ƒCƒ‹‚Ìæ“ª‚ÉƒZƒbƒg‚·‚é */

	while (1) {
		SetRecordControl(src_hdl, dst_hdl);		/* ‚PƒŒƒR[ƒh‚Ìƒf[ƒ^‚ğæ‚èo‚· */

		switch (RecordControl.Type) {	/* ƒŒƒR[ƒh‚Ìí—Ş‚Ì”»•Ê */
		case RCD_HEADER: /* ƒwƒbƒ_ƒŒƒR[ƒh */
			/* ‰½‚à‚µ‚È‚¢ */
			break;
		case RCD_DATA_1: /* ƒf[ƒ^ƒŒƒR[ƒh */
		case RCD_DATA_2:
		case RCD_DATA_3:
			/* ƒoƒCƒiƒŠƒf[ƒ^‘‚«‚İ */
			if ((start_address <= RecordControl.Address)
			 && (end_address >= (RecordControl.Address + (unsigned long)RecordControl.ByteCount))) {
				fseek(*dst_hdl, (RecordControl.Address - start_address + offset), SEEK_SET);
				for (digit_count = 0; digit_count < RecordControl.ByteCount; digit_count++) {
					putc(RecordControl.Data[digit_count], *dst_hdl);
				}
			}
			break;
		case RCD_END_1:  /* ƒGƒ“ƒhƒŒƒR[ƒh */
		case RCD_END_2:
		case RCD_END_3:
			/* I—¹ */
			return;
		default:
			ErrorExit(1);
		}
	}
}

/*************************************************************************
	module		:[ƒ‚ƒgƒ[ƒ‰‚g‚d‚w‚PƒŒƒR[ƒh‚Ì“à—e‚ğ\‘¢‘Ì‚Éæ‚èo‚·]
	function	:[]
	common		:[]
	condition	:[]
	comment		:[
		ƒtƒ@ƒCƒ‹ƒnƒ“ƒhƒ‹‚ªƒŒƒR[ƒh‚Ìæ“ª‚ğw‚µ‚½ó‘Ô‚Å“n‚·‚±‚Æ
	]
	return		:[‚È‚µ]
	machine		:[]
	language	:[MS-C(Ver.6.0)]
	keyword		:[X]
	date		:[1998/03/20]
	author		:[–ì£•qO]
*************************************************************************/
void SetRecordControl(FILE **src_hdl, FILE **dst_hdl)
{
	unsigned char digit_byte;
	unsigned long digit_long;
	unsigned char position;
	unsigned char digit_count;
	unsigned char ascii_count;

	ascii_count = 0;
	while (ascii_count < 47) {
		record_data[ascii_count] = (unsigned char)getc(*src_hdl);
		if (record_data[ascii_count] == 0x0a) {
			break;
		}
		ascii_count++;
	}

	if (record_data[0] != 'S') {
		ErrorExit(2);
	}

	switch (record_data[1]) {
	case '0':
		RecordControl.Type = RCD_HEADER;
		break;
	case '1':
		RecordControl.Type = RCD_DATA_1;
		break;
	case '2':
		RecordControl.Type = RCD_DATA_2;
		break;
	case '3':
		RecordControl.Type = RCD_DATA_3;
		break;
	case '7':
		RecordControl.Type = RCD_END_3;
		break;
	case '8':
		RecordControl.Type = RCD_END_2;
		break;
	case '9':
		RecordControl.Type = RCD_END_1;
		break;
	}

	digit_byte = AsciiToDigit(record_data[2]);
	digit_byte <<= 4;
	digit_byte |= AsciiToDigit(record_data[3]);
	switch (RecordControl.Type) {
	case RCD_HEADER:
	case RCD_DATA_1:
	case RCD_END_1:
		digit_byte -= 3;	/* address(2byte) + Sum(1byte) */
		break;
	case RCD_DATA_2:
	case RCD_END_2:
		digit_byte -= 4;	/* address(3byte) + Sum(1byte) */
		break;
	case RCD_DATA_3:
	case RCD_END_3:
		digit_byte -= 5;	/* address(4byte) + Sum(1byte) */
		break;
	}
	RecordControl.ByteCount = digit_byte;

	switch (RecordControl.Type) {
	case RCD_HEADER:
	case RCD_DATA_1:
	case RCD_END_1:
		digit_long =  (unsigned long)AsciiToDigit(record_data[4]) * (unsigned long)0x1000;
		digit_long += (unsigned long)AsciiToDigit(record_data[5]) * (unsigned long)0x100;
		digit_long += (unsigned long)AsciiToDigit(record_data[6]) * (unsigned long)0x10;
		digit_long += (unsigned long)AsciiToDigit(record_data[7]) * (unsigned long)0x01;
		position = 8;
		break;
	case RCD_DATA_2:
	case RCD_END_2:
		digit_long =  (unsigned long)AsciiToDigit(record_data[4]) * (unsigned long)0x100000;
		digit_long += (unsigned long)AsciiToDigit(record_data[5]) * (unsigned long)0x10000;
		digit_long += (unsigned long)AsciiToDigit(record_data[6]) * (unsigned long)0x1000;
		digit_long += (unsigned long)AsciiToDigit(record_data[7]) * (unsigned long)0x100;
		digit_long += (unsigned long)AsciiToDigit(record_data[8]) * (unsigned long)0x10;
		digit_long += (unsigned long)AsciiToDigit(record_data[9]) * (unsigned long)0x01;
		position = 10;
		break;
	case RCD_DATA_3:
	case RCD_END_3:
		digit_long =  (unsigned long)AsciiToDigit(record_data[4]) * (unsigned long)0x10000000;
		digit_long += (unsigned long)AsciiToDigit(record_data[5]) * (unsigned long)0x1000000;
		digit_long += (unsigned long)AsciiToDigit(record_data[6]) * (unsigned long)0x100000;
		digit_long += (unsigned long)AsciiToDigit(record_data[7]) * (unsigned long)0x10000;
		digit_long += (unsigned long)AsciiToDigit(record_data[8]) * (unsigned long)0x1000;
		digit_long += (unsigned long)AsciiToDigit(record_data[9]) * (unsigned long)0x100;
		digit_long += (unsigned long)AsciiToDigit(record_data[10]) * (unsigned long)0x10;
		digit_long += (unsigned long)AsciiToDigit(record_data[11]) * (unsigned long)0x01;
		position = 12;
		break;
	}
	RecordControl.Address = digit_long;

	for (digit_count = 0; digit_count < RecordControl.ByteCount; digit_count++) {
		ascii_count = digit_count * 2;
		digit_byte = AsciiToDigit(record_data[position + ascii_count]);
		digit_byte <<= 4;
		digit_byte |= AsciiToDigit(record_data[position + ascii_count + 1]);
		RecordControl.Data[digit_count] = digit_byte;
	}

	/*
	RecordControl.Sum = record_data[position + count];
	*/
}

/*************************************************************************
	module		:[ƒAƒXƒL[‚ğ”’l‚É•ÏŠ·‚·‚é]
	function	:[]
	common		:[]
	condition	:[]
	comment		:[
		mot2binr.c ‚æ‚èƒRƒs[
	]
	return		:[‚È‚µ]
	machine		:[]
	language	:[MS-C(Ver.6.0)]
	keyword		:[X]
	date		:[1998/03/20]
	author		:[–ì£•qO]
*************************************************************************/
unsigned char AsciiToDigit(unsigned char ascii)
{
	switch (ascii) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return(ascii - 48);		/* 48(0x30) '0' */
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
		return(ascii - 87);		/* x - 'a':97(0x61) + 10 */
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
		return(ascii - 55);		/* x - 'A':65(0x41) + 10 */
	default :
		printf("ascii :%x\n",ascii);
		ErrorExit(3);
	}
}

/*************************************************************************
	module		:[ƒGƒ‰[I—¹]
	function	:[]
	common		:[]
	condition	:[]
	comment		:[]
	return		:[‚È‚µ]
	machine		:[]
	language	:[MS-C(Ver.6.0)]
	keyword		:[X]
	date		:[1998/03/20]
	author		:[–ì£•qO]
*************************************************************************/
void ErrorExit(unsigned char error)
{
	switch (error) {
	case 0:
		printf("ƒtƒ@ƒCƒ‹‚ªŒ©‚Â‚©‚è‚Ü‚¹‚ñ\n");
		break;
	case 1:
		printf("ƒŒƒR[ƒhí•ÊƒGƒ‰[\n");
		break;
	case 2:
		printf("ƒŒƒR[ƒhæ“ªƒGƒ‰[\n");
		break;
	case 3:
		printf("ƒoƒCƒiƒŠ•ÏŠ·ƒGƒ‰[\n");
		break;
	case 4:
#if (0)
		printf("Usage:>makebin [‹@í][•ÏŠ·Œ³ƒtƒ@ƒCƒ‹–¼][•ÏŠ·æƒtƒ@ƒCƒ‹–¼]\n");
		printf("‹@í 0:POPLAR_L 1:POPLAR_N 2:POPLAR_B 3:POPLAR_H 4:ANZU_L\n");
#endif
		printf("Usage:>makebin [‹@í][ROM´Ø±±ÄŞÚ½][Û°ÀŞ°±ÄŞÚ½][“ü—ÍÌ§²Ù][o—ÍÌ§²Ù]\n");
		printf("‹@í 0:POPLAR_L 1:POPLAR_N 2:POPLAR_B 3:POPLAR_H 4:ANZU_L\n");
		exit(1);
	}

#if (0)
	printf("%Type      :%d\n",RecordControl.Type);
	printf("%ByteCount :%d\n",RecordControl.ByteCount);
	printf("%Address   :%lx\n",RecordControl.Address);
	printf("%Data[0]   :%x\n",RecordControl.Data[0]);
	printf("%Data[1]   :%x\n",RecordControl.Data[1]);
	printf("%Data[2]   :%x\n",RecordControl.Data[2]);
	printf("%Data[3]   :%x\n",RecordControl.Data[3]);
	printf("%Data[4]   :%x\n",RecordControl.Data[4]);
	printf("%Data[5]   :%x\n",RecordControl.Data[5]);
	printf("%Data[6]   :%x\n",RecordControl.Data[6]);
	printf("%Data[7]   :%x\n",RecordControl.Data[7]);
	printf("%Data[8]   :%x\n",RecordControl.Data[8]);
	printf("%Data[9]   :%x\n",RecordControl.Data[9]);
	printf("%Data[10]  :%x\n",RecordControl.Data[10]);
	printf("%Data[11]  :%x\n",RecordControl.Data[11]);
	printf("%Data[12]  :%x\n",RecordControl.Data[12]);
	printf("%Data[13]  :%x\n",RecordControl.Data[13]);
	printf("%Data[14]  :%x\n",RecordControl.Data[14]);
	printf("%Data[15]  :%x\n",RecordControl.Data[15]);
	printf("%Sum       :%x\n",RecordControl.Sum);
#endif

	fclose(ReadFileHandle);
	fclose(WriteFileHandle);
	exit(1);
}
