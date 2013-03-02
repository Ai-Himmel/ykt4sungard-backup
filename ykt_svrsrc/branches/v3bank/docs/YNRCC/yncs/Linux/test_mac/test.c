#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Caculate_Session_MAC(char *account, char *prs_first, char *prs_next, char *string, char *mac);
void Caculate_FS_MAC(char *string, char *file, char *key, char *mac);
void Caculate_String_MAC(char *string, char *key, char *mac);
char* MDFile (char *filename);

int main()
{
	char *zh="6223690340796297";
	char *prs_first="0H0IC61E";
	char *prs_next="KB3J1A6H31NI120E8J1OP0E3";
	char *string="0200|6223690340796297|300000|0401134345|002650|8220|00|99992900|99990000|12345678|822010689000001|";
	char *file="test.txt";
	char mac[9];
	char key[33];

	memset(mac, 0x00, sizeof(mac));
	Caculate_Session_MAC(zh, prs_first, prs_next, string, mac);
	printf("session_mac=[%s]\n", mac);

	memset(mac, 0x00, sizeof(mac));
	memset(key, 0x00, sizeof(key));
	Caculate_String_MAC(string, key, mac);
	printf("key=[%s]\n", key);
	printf("string_mac=[%s]\n", mac);

	memset(mac, 0x00, sizeof(mac));
	memset(key, 0x00, sizeof(key));
	Caculate_FS_MAC(string, file, key, mac);
	printf("key=[%s]\n", key);
	printf("fs_mac=[%s]\n", mac);

	exit(0);
}
