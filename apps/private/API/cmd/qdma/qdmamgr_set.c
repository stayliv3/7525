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

#include "qdmamgr_set.h"

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
/* qos */
int do_set_qos(int argc, char* argv[], void *p);
int do_set_qos_config(int argc, char *argv[], void *p);
/* others */
int do_set_txq_cngst(int argc, char* argv[], void *p);
int do_set_txq_cngst_dei_en(int argc, char *argv[], void *p);

/************************************************************************
*                  P U B L I C   D A T A
************************************************************************/

/************************************************************************
*                  P R I V A T E   D A T A
************************************************************************/
const cmds_t qdmamgr_set_command[] = {
/*	name,					func,						flags,	argcmin,		argc_errmsg */
	{"qos",					do_set_qos,					0,		1,			"Set the QDMA qos config information"},
	{"txq_cngst",			do_set_txq_cngst,			0,		1,			"Set the QDMA txq cngst information"},
	/* Cmd should be added before this line!  */
	{"help",				api_lib_help,				0,		0,			"Show qdmamgr set usage."},
	{NULL, NULL, 0, 0, NULL}
};

const cmds_t qos_set_command[] = {
/*	name,					func,						flags,	argcmin,		argc_errmsg */
	{"config",				do_set_qos_config,			0,		2,			"Set the QDMA qos config <weightBase, weightScale>"},
	/* Cmd should be added before this line!  */
	{"help",				api_lib_help,				0,		0,			"Show qdmamgr set usage."},
	{NULL, NULL, 0, 0, NULL}
};

const cmds_t txqcngst_set_command[] = {
/*	name,					func,						flags,	argcmin,		argc_errmsg */
	{"dei_en",				do_set_txq_cngst_dei_en,	0,		1,			"Set the QDMA txq_cngst dei_en <enable/disable>"},
	/* Cmd should be added before this line!  */
	{"help",				api_lib_help,				0,		0,			"Show qdmamgr set usage."},
	{NULL, NULL, 0, 0, NULL}
};


/************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
************************************************************************/

/******************************************************************************
 Descriptor:	It's used to set qdma qos status.
 Input Args:	see qdmamgr_set_command.
 Ret Value: 	none.
******************************************************************************/
int do_set_qos(int argc, char* argv[], void *p)
{
#if API_CMD_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return subcmd(qos_set_command, argc, argv, (void *)qos_set_command);
}

/******************************************************************************
 Descriptor:	It's used to set qdma txq cngst status.
 Input Args:	see qdmamgr_set_command.
 Ret Value: none.
******************************************************************************/
int do_set_txq_cngst(int argc, char* argv[], void *p)
{
#if API_CMD_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return subcmd(txqcngst_set_command, argc, argv, (void *)txqcngst_set_command);
}

/******************************************************************************
 Descriptor:	It's used to set qdma qos config value.
 Input Args:	see qos_set_command.
 Ret Value: none.
******************************************************************************/
int do_set_qos_config(int argc, char *argv[], void *p)
{
	//QDMA_TxQosWeightType_t weightBase;
	//QDMA_TxQosWeightScale_t weightScale;
	uint weightBase;
	uint weightScale;
#if API_CMD_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	weightBase = (uint)strtoul(argv[1], NULL, 10) ;
	weightScale = (uint)strtoul(argv[2], NULL, 10) ;
	//if((weightBase >= QDMA_TXQOS_WEIGHT_MAX) || (weightScale >= QDMA_TXQOS_WEIGHT_SCALE_MAX)) {
	if((weightBase >= 2) || (weightScale >= 2)) {
		printf("Error: weightBase:%d, weightScale:%d, exceed the scope.\n", weightBase, weightScale) ;
		return QDMAMGR_FAIL;
	}

	if(qdmamgr_lib_set_qos_config(weightBase, weightScale) == QDMAMGR_FAIL) {
		printf("Exec. Failed: Set the 'qos config' command failed\n") ;
		return QDMAMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
}

/******************************************************************************
 Descriptor:	It's used to set qdma txq cngst dei enable or not.
 Input Args:	see txqcngst_set_command.
 Ret Value: none.
******************************************************************************/
int do_set_txq_cngst_dei_en(int argc, char *argv[], void *p)
{
#if API_CMD_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif
	return 0;
}

