#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_

#pragma once
#define SPLIT_VL1 "?"
#define SPLIT_VL2 "$"
#define SPLIT_VL3 "&"


#define RESPONESMARK1 "0000"
#define RESPONESMARK2 "0001"
#define RESPONESMARK3 "0002"
#define RESPONESMARK4 "6666"
#define RESPONESMARK5 "7777"
#define RESPONESMARK6 "7778"

#define  PACKETSTR(packet_str, des_str, split_vl) \
		{ \
		if (strlen(des_str)) { strcat(packet_str, des_str); strcat(packet_str, split_vl); } \
		}

#define  PACKETSTREXT(packet_str, prefix_str, des_str, split_vl) \
		{ \
		if (strlen(des_str)) { strcat(packet_str, prefix_str); strcat(packet_str, des_str); strcat(packet_str, split_vl); } \
		}

struct ConfStruct  
{
	char conf_id[20];
	char conf_name[256];
};

static ConfStruct conf_struct[50];

#endif