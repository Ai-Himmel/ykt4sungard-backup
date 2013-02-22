#ifndef __ISO8583_H_
#define __ISO8583_H_

#include "stdafx.h"
#include "bank.h"

#ifdef __cplusplus
extern "C" {
#endif 

#define XCHANGE_IN 0
#define XCHANGE_OUT 1
#define MSG_LENGTH 4
#define SPLIT_VL1 0x20				// use 0x20 to the end mark, don't come to '\0' when transfering
#define SPLIT_VL2 0x30

#define FIELD1		1
#define FIELD2		2
#define FIELD3		3
#define FIELD4		4
#define FIELD5		5
#define FIELD6		6
#define FIELD7		7
#define FIELD8		8
#define FIELD9		9
#define FIELD10		10
#define FIELD11		11
#define FIELD12		12
#define FIELD13		13
#define FIELD14		14
#define FIELD15		15
#define FIELD16		16
#define FIELD17		17
#define FIELD18		18
#define FIELD19		19
#define FIELD20		20
#define FIELD21		21
#define FIELD22		22
#define FIELD23		23
#define FIELD24		24
#define FIELD25		25
#define FIELD26		26
#define FIELD27		27
#define FIELD28		28
#define FIELD29		29
#define FIELD30		30
#define FIELD31		31
#define FIELD32		32
#define FIELD33		33
#define FIELD34		34
#define FIELD35		35
#define FIELD36		36
#define FIELD37		37
#define FIELD38		38
#define FIELD39		39
#define FIELD40		40
#define FIELD41		41
#define FIELD42		42
#define FIELD43		43
#define FIELD44		44
#define FIELD45		45
#define FIELD46		46
#define FIELD47		47
#define FIELD48		48
#define FIELD49		49
#define FIELD50		50
#define FIELD51		51
#define FIELD52		52
#define FIELD53		53
#define FIELD54		54
#define FIELD55		55
#define FIELD56		56
#define FIELD57		57
#define FIELD58		58
#define FIELD59		59
#define FIELD60		60
#define FIELD61		61
#define FIELD62		62
#define FIELD63		63
#define FIELD64		64
#define FIELD65		65
#define FIELD66		66
#define FIELD67		67
#define FIELD68		68
#define FIELD69		69
#define FIELD70		70
#define FIELD71		71
#define FIELD72		72
#define FIELD73		73
#define FIELD74		74
#define FIELD75		75
#define FIELD76		76
#define FIELD77		77
#define FIELD78		78
#define FIELD79		79
#define FIELD80		80
#define FIELD81		81
#define FIELD82		82
#define FIELD83		83
#define FIELD84		84
#define FIELD85		85
#define FIELD86		86
#define FIELD87		87
#define FIELD88		88
#define FIELD89		89
#define FIELD90		90
#define FIELD91		91
#define FIELD92		92
#define FIELD93		93
#define FIELD94		94
#define FIELD95		95
#define FIELD96		96
#define FIELD97		97
#define FIELD98		98
#define FIELD99		99	
#define FIELD100	100
#define FIELD101	101
#define FIELD102	102
#define FIELD103	103
#define FIELD104	104
#define FIELD105	105
#define FIELD106	106
#define FIELD107	107
#define FIELD108	108
#define FIELD109	109
#define FIELD110	110
#define FIELD111	111
#define FIELD112	112
#define FIELD113	113
#define FIELD114	114
#define FIELD115	115
#define FIELD116	116
#define FIELD117	117
#define FIELD118	118
#define FIELD119	119
#define FIELD120	120
#define FIELD121	121
#define FIELD122	122
#define FIELD123	123
#define FIELD124	124
#define FIELD125	125
#define FIELD126	126
#define FIELD127	127
#define FIELD128	128

// 0 indicate Binary to HEX, 1 indicate HEX to Binary
int TwoAndHex(char *binary_data, unsigned char *hex_data, int flag);
// 0 in, 1 out
int ChangeBitBuf(char asc_bit[128], char bcd_bit[16], int bit_flag);
// 0 indicate Packet to 8583, 1 indicate 8583 to Packet
int ChangePacktTo8583(void *src_packet, ISO8583 *iso_8583_packet, int flag);
// 0 indicate 8583 to buf, 1 indicate buf to 8583
int Change8583ToBuf(ISO8583 *iso_8583_packet, char *buf, int flag);
// get string length when meeting the end mark 'end_chr'
int GetStrLength(char *src_str, char end_chr);

void Set8583BitMap(char bitmap[16], ...);

void Get8583DataLength(char bitmap[16], ISO8583 *iso_8583_packet, int *data_length);

#ifdef __cplusplus
}
#endif // __cplusplus


#endif
