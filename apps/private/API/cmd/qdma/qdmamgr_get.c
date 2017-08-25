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

#include "qdmamgr_get.h"

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

int do_get_qos(int argc, char* argv[], void *p);
int do_get_txq_cngst(int argc, char* argv[], void *p);
int do_get_qos_config(int argc, char *argv[], void *p);
int do_get_txq_cngst_dei_en(int argc, char *argv[], void *p);


/************************************************************************
*                  P U B L I C   D A T A
************************************************************************/

/************************************************************************
*                  P R I V A T E   D A T A
************************************************************************/
const cmds_t qdmamgr_get_command[] = {
/*	name,					func,						flags,	argcmin,		argc_errmsg */
	{"qos",					do_get_qos,					0,		0,			"Get the QDMA qos information"},
	{"txq_cngst",			do_get_txq_cngst,			0,		0,			"Get the QDMA txq cngst information"},
	/* Cmd should be added before this line!  */
	{"help",				api_lib_help,				0,		0,			"Show qdmamgr get usage."},
	{NULL, NULL, 0, 0, NULL}
};

const cmds_t qos_get_command[] = {
/*	name,					func,						flags,	argcmin,		argc_errmsg */
	{"config",				do_get_qos_config,			0,		0,			"Get the QDMA qos config value"},
	/* Cmd should be added before this line!  */
	{"help",				api_lib_help,				0,		0,			"Show qdmamgr get usage."},
	{NULL, NULL, 0, 0, NULL}
};

const cmds_t txqcngst_get_command[] = {
/*	name,					func,						flags,	argcmin,		argc_errmsg */
	{"dei_en",				do_get_txq_cngst_dei_en,	0,		0,			"Get the QDMA txq cngst dei enable or not"},
	/* Cmd should be added before this line!  */
	{"help",				api_lib_help,				0,		0,			"Show qdmamgr get usage."},
	{NULL, NULL, 0, 0, NULL}
};

/************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
************************************************************************/

/******************************************************************************
 Descriptor:	It's used to get qdma qos status.
 Input Args:	see qdmamgr_get_command.
 Ret Value:	success: QDMAMGR_SUCCESS
                     fail: QDMAMGR_FAIL
******************************************************************************/
int do_get_qos(int argc, char* argv[], void *p)
{
#if API_CMD_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return subcmd(qos_get_command, argc, argv, (void *)qos_get_command);
}

/******************************************************************************
 Descriptor:	It's used to get qdma txq cngst status.
 Input Args:	see qdmamgr_get_command.
 Ret Value:	success: QDMAMGR_SUCCESS
                     fail: QDMAMGR_FAIL
******************************************************************************/
int do_get_txq_cngst(int argc, char* argv[], void *p)
{
#if API_CMD_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return subcmd(txqcngst_get_command, argc, argv, (void *)txqcngst_get_command);
}

/******************************************************************************
 Descriptor:	It's used to get qdma qos config value.
 Input Args:	see qos_get_command.
 Ret Value:	success: QDMAMGR_SUCCESS
                     fail: QDMAMGR_FAIL
******************************************************************************/
int do_get_qos_config(int argc, char *argv[], void *p)
{
	//QDMA_TxQosWeightType_t weightBase;
	//QDMA_TxQosWeightScale_t weightScale;
	uint weightBase;
	uint weightScale;
#if API_CMD_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif
	if(qdmamgr_lib_get_qos_config(&weightBase, &weightScale) == QDMAMGR_FAIL) {
		printf("Exec. Failed: Set the 'qos config' command failed\n") ;
		return QDMAMGR_FAIL;
	}

	printf("weightBase is %d, weightScale is %d\n", weightBase, weightScale);
	return QDMAMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to get qdma txq cngst dei enable or not.
 Input Args:	see txqcngst_get_command.
 Ret Value:	success: QDMAMGR_SUCCESS
                     fail: QDMAMGR_FAIL
******************************************************************************/
int do_get_txq_cngst_dei_en(int argc, char *argv[], void *p)
{
#if API_CMD_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif
	return 0;
}

