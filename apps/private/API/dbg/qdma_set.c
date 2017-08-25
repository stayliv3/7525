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
#include <libapi_lib_qdmamgr.h>

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
/* tx rate limit */
int do_set_txratelimit(int argc, char *argv[], void *p);
/* cpu counter */
int do_set_cpu_counter(int argc, char *argv[], void *p);
int do_set_cpu_counter_clear(int argc, char *argv[], void *p);
int do_set_cpu_counter_dump(int argc, char *argv[], void *p);

/************************************************************************
*                  P U B L I C   D A T A
************************************************************************/

/************************************************************************
*                  P R I V A T E   D A T A
************************************************************************/
const cmds_t QdmaSetCmds[] = {
/*	name,					func,						flags,	argcmin,		argc_errmsg */
	{"txratelimit",			do_set_txratelimit,			0,		2,			"Set the QDMA tx ratelimit value"},
	{"cpu_counter",			do_set_cpu_counter,			0,		1,			"Set QDMA cpu counter"},
	/* Cmd should be added before this line!  */
	{"help",				api_lib_help,				0,		0,			"Show qdma set usage."},
	{NULL, NULL, 0, 0, NULL}
};

const cmds_t QdmaSetCpuCounterCmds[] = {
/*	name,		func,						flags,	argcmin,		argc_errmsg */
	{"clear",	do_set_cpu_counter_clear,	0,		0,			"Set QDMA clear cpu counters"},
	{"dump",	do_set_cpu_counter_dump,	0,		0,			"Set QDMA dump cpu counters"},
	/* Cmd should be added before this line!  */
	{"help",	api_lib_help,				0,		0,			"Show qdma set cpu counter usage."},
	{NULL, NULL, 0, 0, NULL}
};

/************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
************************************************************************/

/******************************************************************************
 Descriptor:	It's used to set the QDMA MAC debug level.
 Input Args:	see QdmaSetCmds.
 Ret Value:	success: QDMAMGR_SUCCESS
                     fail: QDMAMGR_FAIL
******************************************************************************/
int do_set_txratelimit(int argc, char *argv[], void *p)
{
	uint bucketScale=0, tickSel=0;
	int ret = 0;
#if API_CMD_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	bucketScale = (uint)strtoul(argv[1], NULL, 10) ;
	tickSel = (uint)strtoul(argv[2], NULL, 10) ;
	//if((weightBase >= QDMA_TXQOS_WEIGHT_MAX) || (weightScale >= QDMA_TXQOS_WEIGHT_SCALE_MAX)) {
	if((bucketScale > 0xF) || (tickSel > 0xFFFF)) {
		printf("Error: bucketScale:%d, tickSel:%d, exceed the scope.\n", bucketScale, tickSel) ;
		return QDMAMGR_FAIL;
	}
	if((argc>=100) && (argc<200)) {
		ret = qdmamgr_lan_lib_set_tx_ratelimit(bucketScale, tickSel);
	} else if((argc>=200) && (argc<300)) {
		ret = qdmamgr_wan_lib_set_tx_ratelimit(bucketScale, tickSel);
	} else {
		printf("Exec. Failed: argc is %d\n", argc) ;
		return QDMAMGR_FAIL;
	}

	if(ret == QDMAMGR_FAIL) {
		printf("Exec. Failed: Set the 'tx ratelimit' command failed\n") ;
		return QDMAMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	return 0;
}

/******************************************************************************
 Descriptor:	It's used to set the QDMA MAC debug level.
 Input Args:	see QdmaSetCmds.
 Ret Value:	success: QDMAMGR_SUCCESS
                     fail: QDMAMGR_FAIL
******************************************************************************/
int do_set_cpu_counter(int argc, char *argv[], void *p)
{
#if API_CMD_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return subcmd(QdmaSetCpuCounterCmds, argc, argv, (void *)QdmaSetCpuCounterCmds);
}

/******************************************************************************
 Descriptor:	It's used to set the QDMA MAC debug level.
 Input Args:	see QdmaSetCmds.
 Ret Value:	success: QDMAMGR_SUCCESS
                     fail: QDMAMGR_FAIL
******************************************************************************/
int do_set_cpu_counter_clear(int argc, char *argv[], void *p)
{
#if API_CMD_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return 0;
}

/******************************************************************************
 Descriptor:	It's used to set the QDMA MAC debug level.
 Input Args:	see QdmaSetCmds.
 Ret Value:	success: QDMAMGR_SUCCESS
                     fail: QDMAMGR_FAIL
******************************************************************************/
int do_set_cpu_counter_dump(int argc, char *argv[], void *p)
{
#if API_CMD_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return 0;
}