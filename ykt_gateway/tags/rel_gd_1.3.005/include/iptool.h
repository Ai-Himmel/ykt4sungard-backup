#ifndef _IPTOOL_H_
#define _IPTOOL_H_

#ifdef __cplusplus
extern "C"{
#endif

#ifdef WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <sys/types.h>
#endif

#define IFI_NAME 16
#define IFI_HADDR 8
#define IFI_ALIAS 1

struct ifi_info
{
	char ifi_name[IFI_NAME];
	short ifi_index;
	short ifi_mtu;
	u_char ifi_haddr[IFI_HADDR];
	u_short ifi_hlen;
	short ifi_flags;
	short ifi_myflags;
	struct sockaddr *ifi_addr;
	struct sockaddr *ifi_brdaddr;
	struct sockaddr *ifi_dstaddr;
	struct ifi_info *ifi_next;
};

char * sock_ntop(const struct sockaddr *sa,socklen_t salen);
struct ifi_info *get_ifi_info(int family,int doaliases);
void free_ifi_info(struct ifi_info *ifihead);

#ifdef __cplusplus
}
#endif

#endif // _IPTOOL_H_


