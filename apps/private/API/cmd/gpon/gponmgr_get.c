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

#include "gponmgr_get.h"

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
extern int api_lib_help(int argc, char *argv[], void *p);

/************************************************************************
*                  F U N C T I O N   D E F I N I T I O N S
************************************************************************/
int do_get_info(int argc, char *argv[], void *p);
int do_get_4B_align(int argc, char *argv[], void *p);

/************************************************************************
*                  P U B L I C   D A T A
************************************************************************/

/************************************************************************
*                  P R I V A T E   D A T A
************************************************************************/
const cmds_t gponmgr_get_command[] = {
/*	name,			func,								flags,	argcmin,	argc_errmsg */
	{"info",				do_get_info,				0,		0,			"Get the GPON detail information"},
	{"4B_align",			do_get_4B_align,			0,		0,			"Get status of tx data length aligned multiple of 4"},
	/* Cmd should be added before this line!  */
	{"help",				api_lib_help,				0,		0,			"Show gponmgr get usage."},
	{NULL, NULL, 0, 0, NULL}
};

/************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
************************************************************************/

/******************************************************************************
 Descriptor:	It's used to get gpon detail information.
 Input Args:	see gponmgr_get_command.
 Ret Value:	none.
******************************************************************************/
int do_get_info(int argc, char *argv[], void *p)
{
	int i;
	struct XMCS_GponOnuInfo_S gponOnuInfo;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	memset(&gponOnuInfo, 0, sizeof(gponOnuInfo)) ;
	if(gponmgr_lib_get_info(&gponOnuInfo) == GPONMGR_FAIL) {
		printf("Exec. Failed: Get the 'info' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("ONU Info:\n") ;
	printf(" ONU ID:    %d\n", gponOnuInfo.onuId) ;
	printf(" ONU State: O%d\n", gponOnuInfo.state) ;
	printf(" SN:        ") ;
	for(i=0 ; i < 4 ; i++) {
		printf("%c", gponOnuInfo.sn[i]) ;
	}
	for(i=4 ; i < 8 ; i++) {
		printf("%.2x", gponOnuInfo.sn[i]) ;
	}
	printf("\n PASSWD:\n") ;
	printf("  ASCII:    %s\n", gponOnuInfo.passwd) ;
	printf("  HEX:      ") ;
	for(i=0 ; i < GPON_PASSWD_LENS ; i++) {
		printf("%.2x", gponOnuInfo.passwd[i]) ;
	}
	printf("\n Key Idx:   %d\n", gponOnuInfo.keyIdx) ;
	printf(" Key:       ") ;
	for(i=0 ; i < 16 ; i++) {
		printf("%.2x", gponOnuInfo.key[i]) ;
	}
	printf("\n O1 Timer:  %d ms\n", gponOnuInfo.actTo1Timer) ;
	printf(" O2 Timer:  %d ms\n", gponOnuInfo.actTo2Timer) ;
	printf(" OMCC ID:   %d\n", gponOnuInfo.omcc) ;

	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to get status of tx data length aligned multiple of 4.
 Input Args:	see gponmgr_get_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_get_4B_align(int argc, char *argv[], void *p)
{
	XPON_Mode_t enable;
	
#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(gponmgr_lib_get_tx_4bytes_align(&enable) == GPONMGR_FAIL) {
		printf("Exec. Failed: Get the '4B_align' command failed\n") ;
		return GPONMGR_FAIL;
	}

	printf("4bytes alignment:%s\n", (enable== XPON_ENABLE) ? "enable" : "disable");

	return GPONMGR_SUCCESS;
}

