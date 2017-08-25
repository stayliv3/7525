/***************************************************************
Copyright Statement:

This software/firmware and related documentation (EcoNet Software) 
are protected under relevant copyright laws. The information contained herein 
is confidential and proprietary to EcoNet (HK) Limited (EcoNet) and/or 
its licensors. Without the prior written permission of EcoNet and/or its licensors, 
any reproduction, modification, use or disclosure of EcoNet Software, and 
information contained herein, in whole or in part, shall be strictly prohibited.

EcoNet (HK) Limited  EcoNet. ALL RIGHTS RESERVED.

BY OPENING OR USING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY 
ACKNOWLEDGES AND AGREES THAT THE SOFTWARE/FIRMWARE AND ITS 
DOCUMENTATIONS (ECONET SOFTWARE) RECEIVED FROM ECONET 
AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON AN AS IS 
BASIS ONLY. ECONET EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, 
WHETHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, 
OR NON-INFRINGEMENT. NOR DOES ECONET PROVIDE ANY WARRANTY 
WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTIES WHICH 
MAY BE USED BY, INCORPORATED IN, OR SUPPLIED WITH THE ECONET SOFTWARE. 
RECEIVER AGREES TO LOOK ONLY TO SUCH THIRD PARTIES FOR ANY AND ALL 
WARRANTY CLAIMS RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES 
THAT IT IS RECEIVERS SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD 
PARTY ALL PROPER LICENSES CONTAINED IN ECONET SOFTWARE.

ECONET SHALL NOT BE RESPONSIBLE FOR ANY ECONET SOFTWARE RELEASES 
MADE TO RECEIVERS SPECIFICATION OR CONFORMING TO A PARTICULAR 
STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND 
ECONET'S ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE ECONET 
SOFTWARE RELEASED HEREUNDER SHALL BE, AT ECONET'S SOLE OPTION, TO 
REVISE OR REPLACE THE ECONET SOFTWARE AT ISSUE OR REFUND ANY SOFTWARE 
LICENSE FEES OR SERVICE CHARGES PAID BY RECEIVER TO ECONET FOR SUCH 
ECONET SOFTWARE.
***************************************************************/

/************************************************************************
*                  I N C L U D E S
************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <asm/tc3162/cmdparse.h>
#include <libapi_lib_gponmgr.h>
#include <gpon/gpon_const.h>

#include "gponmgr_set.h"

/************************************************************************
*                  D E F I N E S   &   C O N S T A N T S
************************************************************************/

/************************************************************************
*                  M A C R O S
************************************************************************/

/************************************************************************
*                  D A T A	 T Y P E S
************************************************************************/

/************************************************************************
*                  E X T E R N A L	 D A T A   D E C L A R A T I O N S
************************************************************************/
extern int subcmd(const cmds_t tab[], int argc, char *argv[], void *p);
extern int api_lib_help(int argc, char *argv[], void *p);

/************************************************************************
*                  F U N C T I O N   D E F I N I T I O N S
************************************************************************/
/* passwd */
int do_set_passwd(int argc, char *argv[], void *p);
int do_set_passwd_ascii(int argc, char *argv[], void *p);
int do_set_passwd_hex(int argc, char *argv[], void *p);
/* others */
int do_set_sn(int argc, char *argv[], void *p);
int do_set_encrypt_key(int argc, char *argv[], void *p);
int do_set_4B_align(int argc, char *argv[], void *p);

/************************************************************************
*                  P U B L I C   D A T A
************************************************************************/

/************************************************************************
*                  P R I V A T E   D A T A
************************************************************************/
const cmds_t gponmgr_set_command[] = {
/*	name,					func,						flags,	argcmin,	argc_errmsg */
	{"sn",					do_set_sn,					0,		2,			"Set GPON serial number <vendor id> <VSSD>"},
	{"passwd",				do_set_passwd,				0,		1,			"Set GPON password <0~10 ASCII words> or <0~20 hexadecimal>"},
	{"encrypt_key",			do_set_encrypt_key,			0,		1,			"Set the encryption key <32 hexadecimal>"},
	{"4B_align",			do_set_4B_align,			0,		1,			"Set tx data length aligned multiple of 4 <enable or disable>"},
	/* Cmd should be added before this line!  */
	{"help",				api_lib_help,				0,		0,			"Show gponmgr set usage."},
	{NULL, NULL, 0, 0, NULL}
};

const cmds_t gponmgr_set_passwd_command[] = {
/*	name,		func,					flags,	argcmin,	argc_errmsg */
	{"ascii",	do_set_passwd_ascii,	0,		1,			"Set GPON password <0~10 ASCII words>"},
	{"hex",		do_set_passwd_hex,		0,		1,			"Set GPON password <0~20 hexadecimal>"},
	/* Cmd should be added before this line!  */
	{"help",	api_lib_help,			0,		0,			"Show gponmgr get usage."},
	{NULL, NULL, 0, 0, NULL}
};


/************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
************************************************************************/

/******************************************************************************
 Descriptor:	It's used to set GPON serial number.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_sn(int argc, char *argv[], void *p)
{
	char sn[GPON_SN_LENS] ;
	unsigned long vssn;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(strlen(argv[1]) == 4 && strlen(argv[2]) == 8) {
		strncpy(sn, argv[1], 4);
		vssn = strtoul(argv[2], NULL, 16);
		sn[4] = (unchar)(vssn >> 24) ;
		sn[5] = (unchar)(vssn >> 16) ;
		sn[6] = (unchar)(vssn >> 8) ;
		sn[7] = (unchar)(vssn) ;
	} else {
		printf("Input Error: Vendor ID length must be 4, VSSN length must be 8.\n") ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_sn(sn) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'sn' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set GPON password.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_passwd(int argc, char *argv[], void *p)
{
#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return subcmd(gponmgr_set_passwd_command, argc, argv, (void *)gponmgr_set_passwd_command);
}

/******************************************************************************
 Descriptor:	It's used to set GPON password with 0~10 ASCII words.
 Input Args:	see gponmgr_set_passwd_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_passwd_ascii(int argc, char *argv[], void *p)
{
	char passwd[GPON_PASSWD_LENS] ;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	memset(&passwd, 0, sizeof(passwd)) ;
	if(strlen(argv[1]) <= GPON_PASSWD_LENS) {
		strncpy(passwd, argv[1], GPON_PASSWD_LENS);
	} else {
		printf("Input Error: password length must be less than %d ASCII.\n", GPON_PASSWD_LENS) ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_passwd(passwd) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'passwd' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set GPON password with 0~20 hexadecimal.
 Input Args:	see gponmgr_set_passwd_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_passwd_hex(int argc, char *argv[], void *p)
{
	unchar passwd[GPON_PASSWD_LENS] ;
	int len, i;
	char tmp[3];

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	memset(passwd, 0, sizeof(passwd)) ;
	len = strlen(argv[1]);
	/* hexadecimal length is twice as big as ASCII length  */
	if(len <= (GPON_PASSWD_LENS << 1)) {
		tmp[2] = '\0';
		for(i = 0; i < (len >> 1); i++) {
			tmp[0] = argv[1][i * 2];
			tmp[1] = argv[1][i * 2 + 1];
			passwd[i] = (unchar)strtoul(tmp, NULL, 16);
		}
		/* len is odd number */
		if(len % 2) {
			tmp[0] = argv[1][i * 2];
			tmp[1] = '0';
			passwd[i] = (unchar)strtoul(tmp, NULL, 16);
		}
	} else {
		printf("Input Error: password length must be less than %d hexadecimal digits.\n", GPON_PASSWD_LENS << 1) ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_passwd(passwd) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'passwd' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the encryption key.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_encrypt_key(int argc, char *argv[], void *p)
{
	unchar key[16] ;
	char key_tmp[3];
	int i;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(strlen(argv[1]) == 32) {
		key_tmp[2] = '\0';
		for(i = 0; i < 16; i++) {
			key_tmp[0] = argv[1][i * 2];
			key_tmp[1] = argv[1][i * 2 + 1];
			key[i] = strtoul(key_tmp, NULL, 16);
		}
	} else {
		printf("Input Error: encrypt key length must be 32 hexadecimal.\n") ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_encrypt_key(key) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'encrypt_key' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set enable/disable tx data length aligned multiple of 4.
 Input Args:	see gponmgr_set_filter_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_4B_align(int argc, char *argv[], void *p)
{
	XPON_Mode_t enable ;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(strncmp(argv[1], "enable", strlen("enable")) == 0) {
		enable = XPON_ENABLE;
	} else if(strncmp(argv[1], "disable", strlen("disable")) == 0) {
		enable = XPON_DISABLE;
	} else {
		printf("Input Error: must be \"enable\" or \"disable\".\n") ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_tx_4bytes_align(enable) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the '4B_align' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

