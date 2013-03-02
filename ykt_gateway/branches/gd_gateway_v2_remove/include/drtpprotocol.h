#ifndef __DRTPPROTOCOL_H
#define __DRTPPROTOCOL_H

#define BUFSIZE 8116

#define SEND_PUBLIC_KEY_CMD			1
#define SEND_KEY_CMD				2
#define ADD_CASTFUNCTION_CMD        3
#define DEL_CASTFUNCTION_CMD        4
#define ADD_FUNC_CMD				5
#define DEL_FUNC_CMD				6
#define ADD_NODE_CMD				7
#define ADD_BRANCHNAME_CMD			8
#define DEL_PATH_CMD		        9

#define SEND_CMD					10
#define POST_CMD					11
#define ATTACH_CMD					12
#define ANSWER_CMD                  13
#define ECHO_ATTACH_CMD             14 
#define QUERY_CMD                   15
#define QUERY_RESULT_CMD			16
#define QUERY_END_CMD				17
#define PING_CMD                    18
#define PING_ANSWER_CMD             19
#define ACK_ANSWER_CMD              20
#define CHECK_VER_CMD               21

#define ADD_CASTSLOT_CMD			22
#define DEL_CASTSLOT_CMD			23
#define ADD_SLOT_CMD				24
#define V_LINK_CMD					25
#define V_BIND_CMD					26
#define V_CALL_CMD					27
#define V_UNBIND_CMD				28
#define CLOSE_CONNECT_CMD			29
#define PING_BIND_CMD				30
#define CAST_R_CMD					31
#define CAST_A_CMD					32
#define CHECK_CONNECT_CMD			33

#define ACK_NO                      0
#define ACK_BEGIN                   1
#define ACK_END                     2
#define ACK_SRV                     3

#define BEATHEARTTICK               5
#ifndef WIN32
#	ifndef __GNUC__
#		define __PACKED__
#		pragma options align=packed
#	else
#		define __PACKED__	__attribute__ ((packed))
#		pragma pack(push,1)
#	endif
#else
#	define __PACKED__
#	pragma pack(push,1)
#endif

typedef struct tag_NODE
{
	int branch;
	int hi;
	int low;
}__PACKED__ NODE;

typedef struct tag_VDATA
{
	short length;
	short zip;
	char  buffer[8188];
}__PACKED__ VDATA;

typedef struct tag_HEAD
{
	char tty;
	char zip;
	short cmd;
	int crc;
	int serialno;
	int primary;
	int length;
	int function;
	NODE destnode;
	int destsocket;
	int desttimestamp;
	NODE sourcenode;
	int sourcesocket;
	int sourcetimestamp;
	int hook;
	int sendserialno;
	int ackmode;
}__PACKED__ HEAD,*PHEAD;

typedef struct tag_SENDPUBLICKEY
{
	int publickeylength;
	char publickey[256];
}__PACKED__ SENDPUBLICKEY;

typedef struct tag_SENDKEY
{
	int keylen;
	int crypt;
	char key[256];
	int beatheart;
	int zip;
	int beatheartcount;
}__PACKED__ SENDKEY;

typedef struct tag_ADD_FUNCTION
{
	int function;
}__PACKED__ ADD_FUNCTION;

typedef struct tag_ADD_SLOT
{
	int slot;
}__PACKED__ ADD_SLOT;

typedef struct tag_ADD_NODE
{
	NODE node;
	int nodecount;
	char path;
}__PACKED__ ADD_NODE;

typedef struct tag_DEL_FUNCTION
{
	int function;
}__PACKED__ DEL_FUNCTION;

typedef struct tag_DEL_PATH
{
	char pathcell[54];
	char path;
}__PACKED__ DEL_PATH;

typedef struct tag_ANSWER
{
	int errcode;
	char message[300];
}__PACKED__ ANSWER;

typedef struct tag_CASTFUNCTION
{
	int function;
	int timestamp;
	NODE node;
	int nodecount;
	char path;
}__PACKED__ CASTFUNCTION;

typedef struct tag_CASTSLOT
{
	int slot;
	int timestamp;
	NODE node;
	int nodecount;
	char path;
}__PACKED__ CASTSLOT;

typedef struct tag_ADD_BRANCHNAME
{
	int branchname;
	int branch;
	char path;
}__PACKED__ ADD_BRANCHNAME;

typedef struct tag_QUERY_REQUEST
{
	int cmd;
}__PACKED__ QUERY_REQUEST;

typedef struct tag_check_ver
{
	char version[20];
	int  bandwidth;
	int  bonenode;
}__PACKED__ TAG_CHECK_VER;

typedef struct tag_v_link
{
	int branchno;
	int slot;
	int publickeylength;
	char publickey[256];
}__PACKED__ TAG_V_LINK;

typedef struct tag_v_call
{
	int index;
	int timestamp;
	int mainsocket;
	int mtimestamp;
}__PACKED__ TAG_V_CALL;

typedef struct tag_v_bind
{
	int index;
	int timestamp;
	int mainsocket;
	int mtimestamp;
}__PACKED__ TAG_V_BIND;

typedef struct tag_v_unbind
{
	int index;
	int timestamp;
}__PACKED__ TAG_V_UNBIND;

typedef struct tag_ping_bind
{
	int ssocket;
	int stimestamp;
}__PACKED__ TAG_PING_BIND;

typedef struct tag_BODY
{
	union 
	{
		char buffer[BUFSIZE];
		SENDPUBLICKEY sendpublickey;
		SENDKEY sendkey;
		ADD_FUNCTION add_function;
		ADD_SLOT add_slot;
		ADD_NODE add_node;
		DEL_FUNCTION del_function;
		DEL_PATH del_path;
		CASTFUNCTION castfunction;
		CASTSLOT castslot;
		ANSWER answer;
		ADD_BRANCHNAME add_branchname;
		QUERY_REQUEST query_request;
		TAG_CHECK_VER check_ver;
		TAG_V_CALL v_call;
		TAG_V_BIND v_bind;
		TAG_V_LINK v_link;
		TAG_V_UNBIND v_unbind;
		TAG_PING_BIND ping_bind;
	}data;
}__PACKED__ BODY,*PBODY;

typedef struct tag_COMMSTRU
{
	HEAD head;
	BODY body;
}__PACKED__ COMMSTRU,*PCOMMSTRU;

typedef struct tag_RECVMESSAGE
{
	int socket;
	int msgtype;
	int index;
	int connecttime;
	PCOMMSTRU message;
}__PACKED__ RECVMESSAGE,*PRECVMESSAGE;

typedef struct tag_SENDMESSAGE
{
	bool resend;
	int length;
	int offset;
	int direct;
	int answer;
	int sourcesocket;
	int sourcestamp;
	int sourcechecked;
	int sourceindex;
	int sourcecrypto;
	char sourcekey[30];
	int destsocket;
	int deststamp;
	int destchecked;
	int destindex;
	int destcrypto;
	char destkey[30];
	PCOMMSTRU message;
}__PACKED__ SENDMESSAGE,*PSENDMESSAGE;

#define MSG_ACCEPT   1
#define MSG_READ     2
#define MSG_CLOSE    3
#define MSG_CONNECT  4
#define MSG_DATA     5
#define MSG_PING	 6
#define MSG_VCONNECT 7

#ifndef WIN32
#	ifndef __GNUC__
#		pragma options align=reset
#	else
#		pragma pack(pop)
#	endif
#else
#	pragma pack(pop)
#endif

#endif