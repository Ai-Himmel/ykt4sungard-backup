#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef WIN32

#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#ifndef LINUX
#include <net/if_dl.h>
#endif
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <asm/types.h>
#include <linux/netlink.h>

#include "iptool.h"





static void err_sys(const char *msg)
{
	fprintf(stderr,"%s\n",msg);
}

char * sock_ntop(const struct sockaddr *sa,socklen_t salen)
{
	char portstr[8];
	static char str[128];

	switch(sa->sa_family)
	{
	case AF_INET:
		{
			struct sockaddr_in *sin = (struct sockaddr_in *)sa;
			if(inet_ntop(AF_INET,&sin->sin_addr, str, sizeof(str)) == NULL)
				return NULL;
			if(ntohs(sin->sin_port) != 0)
			{
				snprintf(portstr,sizeof(portstr),":%d",ntohs(sin->sin_port));
				strcat(str,portstr);
			}
			return str;
		}
	default:
		return NULL;
	}
	return NULL;
}

struct ifi_info *get_ifi_info(int family,int doaliases)
{
	struct ifi_info *ifi, *ifihead, **ifipnext;
	int sockfd, len, lastlen, flags, myflags, idx = 0, hlen = 0;
	char *ptr, *buf, lastname[IFNAMSIZ], *cptr, *haddr, *sdlname;

	struct ifconf ifc;
	struct ifreq *ifr, ifrcopy;
	struct sockaddr_in *sinptr;
	struct sockaddr_in6 *sin6ptr;

	sockfd = socket(AF_INET,SOCK_DGRAM, 0);
	lastlen = 0;
	len = 100 * sizeof(struct ifreq);
	for( ; ; )
	{
		buf = (char*)malloc(len);
		ifc.ifc_len = len;
		ifc.ifc_buf = buf;
		if( ioctl(sockfd, SIOCGIFCONF, &ifc) < 0 )
		{
			if(errno != EINVAL || lastlen != 0)
				err_sys("ioctl error!");
		}
		else
		{
			if(ifc.ifc_len == lastlen)
				break;
			lastlen = ifc.ifc_len;
		}
		len += 10 * sizeof(struct ifreq);
		free(buf);
	}

	ifihead = NULL;
	ifipnext = &ifihead;
	lastname[0] = 0;
	sdlname = NULL;

	for( ptr = buf; ptr < buf + ifc.ifc_len;)
	{
		ifr = (struct ifreq*)ptr;
#ifdef HAVE_SOCKADDR_SA_LEN
		len = max(sizeof(struct sockaddr),ifr->ifr_addr.sa_len);
#else
		switch(ifr->ifr_addr.sa_family)
		{
#	ifdef IPV6
		case AF_INET6:
			len = sizeof(struct sockaddr_in6);
			break;
#	endif
		case AF_INET:
		default:
			len = sizeof(struct sockaddr_in);
			break;
		}
#endif 
		ptr += sizeof(ifr->ifr_name) + len;

#ifdef HAVE_SOCKADDR_DL_STRUCT
		if( ifr->ifr_addr.sa_family == AF_LINK)
		{
			struct sockaddr_dl *sdl = (struct sockaddr_dl*) &ifr_>ifr_addr;
			sdlname = ifr->ifr_name;
			idx = sdl->sdl_index;
			haddr = sdl->sdl_data + sdl->sdl_nlen;
			hlen = sdl->sdl_alen;
		}
#endif
		if(ifr->ifr_addr.sa_family != family)
			continue;

		myflags = 0;

		if( (cptr = strchr(ifr->ifr_name,':')) != NULL )
			*cptr = 0;

		if(strncmp(lastname, ifr->ifr_name, IFNAMSIZ) == 0)
		{
			if(doaliases == 0)
				continue;

			myflags = IFI_ALIAS;
		}

		memcpy(lastname,ifr->ifr_name, IFNAMSIZ);
		ifrcopy = *ifr;
		ioctl(sockfd, SIOCGIFFLAGS, &ifrcopy);
		flags = ifrcopy.ifr_flags;

		if((flags & IFF_UP) == 0)
			continue;

		ifi = (struct ifi_info *)calloc(1,sizeof(struct ifi_info));
		*ifipnext = ifi;
		ifipnext = &ifi->ifi_next;

		ifi->ifi_flags = flags;
		ifi->ifi_myflags = myflags;

#if defined(SIOCGIFMTU) && defined(HAVE_STRUCT_IFREQ_IFR_MTU)
		ioctl(sockfd,SIOCGIFMTU,&ifrcopy);
		ifi->ifi_mtu = ifrcopy.ifr_mtu;
#else
		ifrcopy.ifr_mtu = 0;
#endif
		memcpy(ifi->ifi_name,ifr->ifr_name, IFI_NAME);
		ifi->ifi_name[IFI_NAME - 1] = '\0';

		if( sdlname == NULL || strcmp(sdlname,ifr->ifr_name) != 0)
			idx = hlen = 0;

		ifi->ifi_index = idx;
#ifdef LINUX
		ioctl(sockfd,SIOCGIFHWADDR,&ifrcopy);
		haddr = (char*)ifrcopy.ifr_hwaddr.sa_data;
		hlen = 6;//ifrcopy.ifr_hwaddr.sa_data

#endif
		ifi->ifi_hlen = hlen;

		if(ifi->ifi_hlen > IFI_HADDR)
			ifi->ifi_hlen = IFI_HADDR;

		if(hlen)
			memcpy(ifi->ifi_haddr,haddr,ifi->ifi_hlen);

		switch(ifr->ifr_addr.sa_family)
		{
		case AF_INET:
			sinptr = (struct sockaddr_in *) &ifr->ifr_addr;
			ifi->ifi_addr = (struct sockaddr*)calloc(1,sizeof(struct sockaddr_in));
			memcpy((void*)ifi->ifi_addr, (const void*)sinptr, sizeof(struct sockaddr_in));

#ifdef SIOCGIFBRDADDR
			if(flags & IFF_BROADCAST)
			{
				ioctl(sockfd, SIOCGIFBRDADDR, &ifrcopy);
				sinptr = (struct sockaddr_in *)&ifrcopy.ifr_broadaddr;
				ifi->ifi_brdaddr = (struct sockaddr *)calloc(1,sizeof(struct sockaddr_in));
				memcpy(ifi->ifi_brdaddr, sinptr, sizeof(struct sockaddr_in));
			}
#endif

#ifdef SIOCGIFDSTADDR
			if(flags & IFF_POINTOPOINT)
			{
				ioctl(sockfd, SIOCGIFDSTADDR, &ifrcopy);
				sinptr = (struct sockaddr_in *) &ifrcopy.ifr_dstaddr;
				ifi->ifi_dstaddr = (struct sockaddr *)calloc(1, sizeof(struct sockaddr_in));
				memcpy(ifi->ifi_dstaddr, sinptr, sizeof(struct sockaddr_in));
			}
#endif 

		case AF_INET6:
			sin6ptr = (struct sockaddr_in6 *)&ifr->ifr_addr;
			ifi->ifi_addr = (struct sockaddr *)calloc(1,sizeof(struct sockaddr_in6));
			memcpy(ifi->ifi_addr, sin6ptr, sizeof(struct sockaddr_in6));

#ifdef  SIOCGIFDSTADDR
			if(flags & IFF_POINTOPOINT)
			{
				ioctl(sockfd, SIOCGIFDSTADDR, &ifrcopy);
				sin6ptr = (struct sockaddr_in6 *) &ifrcopy.ifr_dstaddr;
				ifi->ifi_dstaddr = (struct sockaddr *)calloc(1,sizeof(struct sockaddr_in6));
				memcpy(ifi->ifi_dstaddr, sin6ptr, sizeof(struct sockaddr_in6));
			}
#endif
			break;
		default:
			break;
		}

	}
	free(buf);
	return (ifihead);

}

void free_ifi_info(struct ifi_info *ifihead)
{
	struct ifi_info *ifi, *ifinext;

	for(ifi = ifihead; ifi != NULL; ifi = ifinext)
	{
		if( ifi->ifi_addr != NULL)
			free(ifi->ifi_addr);
		if(ifi->ifi_brdaddr != NULL)
			free(ifi->ifi_brdaddr);
		if(ifi->ifi_dstaddr != NULL)
			free(ifi->ifi_dstaddr);
		ifinext = ifi->ifi_next;
		free(ifi);
	}
}

#endif

