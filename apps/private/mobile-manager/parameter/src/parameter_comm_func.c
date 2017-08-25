/*
** $Id: //BBN_Linux/Branch/Branch_for_MT7505_IC_20131122/tclinux_phoenix/apps/private/TR69_64/cwmp/cwmpParameter/Sources/cwmpParameter_table.c#1 $
*/
/************************************************************************
 *
 *	Copyright (C) 2003 Trendchip Technologies, Corp.
 *	All Rights Reserved.
 *
 * Trendchip Confidential; Need to Know only.
 * Protected as an unpublished work.
 *
 * The computer program listings, specifications and documentation
 * herein are the property of Trendchip Technologies, Co. and shall
 * not be reproduced, copied, disclosed, or used in whole or in part
 * for any reason without the prior express written permission of
 * Trendchip Technologeis, Co.
 *
 *************************************************************************/
#include "parameter_comm_func.h"
#include <netdb.h>
#include "threadpool.h"
#include "exec.h"

void fileRead(char *path, char *buf, int size){
	int  fd=0, ret=0;

	memset(buf,0, size);
	fd = open(path,O_RDONLY);
	if(fd == -1){
		return;
	}

	ret = read(fd, buf, size);
	if(ret <= 0){
		close(fd);
		return;
	}

	close(fd);
}/*end fileRead*/

int fileWrite(char *path, char *buf, int size){
	FILE *fp = NULL;
	
	fp = fopen(path, "w");
	if(fp == NULL){
		mobile_printf(MOBILE_ERR,"\n open failed");
		return -1;
	}
	fwrite(buf, sizeof(char), size, fp);
	
	fclose(fp);
}

char* itoa(register int i)
{
	static char a[7]; 
	register char *b = a + sizeof(a) - 1;
	int   sign = (i < 0);

	if (sign)
		i = -i;
	*b = 0;
	do
	{
		*--b = '0' + (i % 10);
		i /= 10;
	}
	while (i);
	if (sign)
		*--b = '-';
	return b;
}

int resolve(char *ipstr, unsigned long *addr, unsigned short *netmask)
{
	unsigned long ipaddr = 0;
	int i, bits;
	unsigned long digit;
	char *index;
	short mask = -1;

	for (i = 0; i < 3; i++) {
		index = strchr(ipstr, '.');
		if (index == NULL) break;
		*index = '\0';
		digit = atoi(ipstr);
		*index = '.';
		if (digit > 255) return -1;
		ipaddr = (ipaddr << 8) | digit;
		ipstr = index + 1;
	}

	index = strchr(ipstr, '/');     /* netmask ? */
	if (index != NULL) {
		mask = atoi(&index[1]);
		if (mask < 0 || mask > 32) return -1;
		*index = '\0';
	}

	digit = atoi(ipstr);
	bits = (4 - i) << 3;
	if (digit > ((1 << bits) - 1)) return -1;
	ipaddr = (ipaddr << bits) | digit;

	digit = ipaddr >> 28;		/* check multicast and reserved IP */
	if (digit >= 14) return -1;
	if (mask < 0) {
		if (digit < 8)
			mask = 8;
		else if (digit < 12)
			mask = 16;
		else if (digit < 14)
			mask = 24;
	}
	else
		*index = '/';

	*addr = ipaddr;
	if (netmask != NULL) *netmask = mask;
	return 0;
}

/*______________________________________________________________________________
**  checkName
**    This function detect if input is a domain name or a IP addr.
**  descriptions:
**  parameters:
**  local:
**  global:
**  return:  0 : this is a domain name
		   1 : this is a IP
**  called by:resolveName()
**  call:
**  revision:
**____________________________________________________________________________*/
uint8 checkName(char *Name)
{
	char c;

	if(Name == NULL)
		return 0;	/* Can't happen */
	
	while((c = *Name++) != '\0'){
		if((!isdigit(c)) && (c != '.') && (c != ':')){
			if(c == '/'){
				return 1;
			}
			return 0;
		}
	}
	return 1;
}

unsigned long resolveName(char *name)
{
	struct hostent *h = NULL;
	struct sockaddr_in addr = {0};
	unsigned long ipAddr = 0;

	if(name == NULL)
		return 0;
	tcdbg_printf("\r\nEnter reslove name: [%s]", name);
	/*add by brian*/
	if(checkName(name))
	{
		resolve((char *)name, &ipAddr, NULL);
		if(ipAddr != 0)
		{
			return ipAddr;
		}
	}

	h = gethostbyname(name);

	if(h != NULL)
	{
		memcpy(&addr.sin_addr, h->h_addr, sizeof(addr.sin_addr));
		tcdbg_printf("\r\nreslove name success: name [%s] IP is [%s]", name, inet_ntoa(addr.sin_addr)); 
	}
	else
	{

		tcdbg_printf("\r\nresolve Name failed!");
	}

	return (unsigned long)addr.sin_addr.s_addr;
}

int isInRouteTable(char *ip, char *dev)
{
	char routePath[] = "/tmp/tmp_ipping_diagnostic_route";
	char cmdbuf[200] = {'\0'}, buf[200] = {'\0'}, tmp[200] = {'\0'};
	char routeInfo[7][16];
	int route_number = 0;
	FILE *fp = NULL;
	enum routeInfo_en{dstIP=0,gw,mask,metric,use,iface,usr_def};

	mobile_printf(MOBILE_DEBUG,"%s, line = %d\n",__FUNCTION__, __LINE__);

	sprintf(cmdbuf, "/sbin/route -n > %s", routePath);
#if EXEC_SYSTEM
	send2Exec(0x30, cmdbuf);
#else
	system(cmdbuf);
#endif	
	memset(routeInfo,0, sizeof(routeInfo));
	fp = fopen(routePath, "r");
	if(fp != NULL)
	{
		while (fgets(buf, sizeof(buf), fp))
		{
			if(route_number > 1)
			{
				sscanf(buf, "%s %s %s %s %s %s %s %s",
					routeInfo[dstIP], routeInfo[gw], routeInfo[mask],
					tmp, routeInfo[metric], tmp,
					routeInfo[use], routeInfo[iface]);
				if(strcmp(routeInfo[dstIP], ip) == 0 && strcmp(routeInfo[iface], dev) == 0){ //is aleardy in route table
					fclose(fp);					
					return 1;	
				}
			}
			route_number++;	
		}
		fclose(fp);
	}
	unlink(routePath);
	return 0;
}
