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
/* dbg_level */
int do_set_dbg_lv(int argc, char *argv[], void *p);
int do_set_dbg_lv_act(int argc, char *argv[], void *p);
int do_set_dbg_lv_omci(int argc, char *argv[], void *p);
int do_set_dbg_lv_oam(int argc, char *argv[], void *p);
int do_set_dbg_lv_int(int argc, char *argv[], void *p);
int do_set_dbg_lv_trace(int argc, char *argv[], void *p);
int do_set_dbg_lv_warning(int argc, char *argv[], void *p);
int do_set_dbg_lv_content(int argc, char *argv[], void *p);
int do_set_dbg_lv_debug(int argc, char *argv[], void *p);
int do_set_dbg_lv_err(int argc, char *argv[], void *p);
/* eqd_offset */
int do_set_eqd_off(int argc, char *argv[], void *p);
int do_set_eqd_off_o4(int argc, char *argv[], void *p);
int do_set_eqd_off_o5(int argc, char *argv[], void *p);
int do_set_eqd_off_flag(int argc, char *argv[], void *p);
/* Tod */
int do_set_tod(int argc, char *argv[], void *p);
int do_set_tod_switch_time(int argc, char *argv[], void *p);
int do_set_tod_new_time(int argc, char *argv[], void *p);
/* act timer */
int do_set_act_timer(int argc, char *argv[], void *p);
int do_set_act_timer_to1(int argc, char *argv[], void *p);
int do_set_act_timer_to2(int argc, char *argv[], void *p);
/* dying gasp */
int do_set_dying_gasp(int argc, char *argv[], void *p);
int do_set_dying_gasp_mode(int argc, char *argv[], void *p);
int do_set_dying_gasp_num(int argc, char *argv[], void *p);
/* sniffer */
int do_set_sniffer(int argc, char *argv[], void *p);
int do_set_sniffer_gtc(int argc, char *argv[], void *p);
/* filter */
int do_set_filter(int argc, char *argv[], void *p);
int do_set_ext_bst_len_ploamd_filter(int argc, char *argv[], void *p);
int do_set_up_overhead_ploamd_filter(int argc, char *argv[], void *p);
/* dba backdoor */
int do_set_dba_backdoor(int argc, char *argv[], void *p);
int do_set_dba_backdoor_total(int argc, char *argv[], void *p);
int do_set_dba_backdoor_green(int argc, char *argv[], void *p);
int do_set_dba_backdoor_yellow(int argc, char *argv[], void *p);
/* dba slight modify */
int do_set_dba_slight_modify(int argc, char *argv[], void *p);
int do_set_dba_slight_modify_total(int argc, char *argv[], void *p);
int do_set_dba_slight_modify_green(int argc, char *argv[], void *p);
int do_set_dba_slight_modify_yellow(int argc, char *argv[], void *p);
/* test */
int do_set_test(int argc, char *argv[], void *p);
int do_set_test_slp_req_ploamu(int argc, char *argv[], void *p);
int do_set_test_rei_ploamu(int argc, char *argv[], void *p);
int do_set_test_dying_gasp_ploamu(int argc, char *argv[], void *p);
int do_set_test_tod(int argc, char *argv[], void *p);
int do_set_test_aes_key_switch_by_sw(int argc, char *argv[], void *p);
int do_set_test_sw_reset(int argc, char *argv[], void *p);
int do_set_test_sw_resync(int argc, char *argv[], void *p);
/* others */
int do_set_cnt_type(int argc, char *argv[], void *p);
int do_set_rsp_time(int argc, char *argv[], void *p);
int do_set_itl_dly_fine_tune(int argc, char *argv[], void *p);
int do_set_burst_mode_overhead(int argc, char *argv[], void *p);
int do_set_clr_cnt(int argc, char *argv[], void *p);
int do_set_key_switch_time(int argc, char *argv[], void *p);
int do_set_block_size(int argc, char *argv[], void *p);
int do_set_up_traffic(int argc, char *argv[], void *p);
int do_set_o3_o4_ploam(int argc, char *argv[], void *p);

/************************************************************************
*                  P U B L I C   D A T A
************************************************************************/

/************************************************************************
*                  P R I V A T E   D A T A
************************************************************************/
const cmds_t gponmgr_set_command[] = {
/*	name,					func,						flags,	argcmin,	argc_errmsg */
	{"dbg_lv",				do_set_dbg_lv,				0,		1,			"Set the GPON MAC debug level"},
	{"eqd_off",				do_set_eqd_off,				0,		1,			"Set the EqD offset at O4 or O5 state <o4, o5 or flag>"},
	{"cnt_type",			do_set_cnt_type,			0,		1,			"Set GPON MAC counter type <gem or ethernet>"},
	{"rsp_time",			do_set_rsp_time,			0,		1,			"Set GPON response time <4 hexadecimal>"},
	{"itl_dly_ftune",		do_set_itl_dly_fine_tune,	0,		1,			"Set the GPON MAC internal delay fine tune(BFB64028[15:8]) <0~255>"},
	{"bst_m_ovhead",		do_set_burst_mode_overhead,	0,		1,			"Set the GPON MAC burst mode overhead length supports more than 128 bytes<enable, disable>"},
	{"clr_cnt",				do_set_clr_cnt,				0,		1,			"clear GPON MAC counter <sw, hw or all>"},
	{"key_sw_time",			do_set_key_switch_time,		0,		1,			"Set when to begin using the new encryption key <8 hexadecimal digits>"},
	{"tod",					do_set_tod,					0,		1,			"Set the GPON ToD parameters <switch time:8 hexadecimal> <sec> <nanosec>"},
	{"act_timer",			do_set_act_timer,			0,		1,			"Set the ONU activation timer"},
	{"block_size",			do_set_block_size,			0,		1,			"Set the GPON DBA block size <1~9999>"},
	{"dying_gasp",			do_set_dying_gasp,			0,		1,			"Set the GPON Dying Gasp parameters"},
	{"up_traffic",			do_set_up_traffic,			0,		1,			"Set the software upstream traffic <enable or disable>"},
	{"sniffer",				do_set_sniffer,				0,		1,			"Set the sniffer configure"},
	{"filter",				do_set_filter,				0,		1,			"Set the filter configure"},
	{"dbru_fix",			do_set_dba_backdoor,		0,		1,			"Set the dba backdoor configure"},
	{"dbru_offset",			do_set_dba_slight_modify,	0,		1,			"Set the dba slight modify configure"},
	{"o3_o4_ploam",			do_set_o3_o4_ploam,			0,		1,			"Set the o3 and o4 ploam control <hw | sw>"},
	{"test",				do_set_test,				0,		1,			"Test commands"},
	/* Cmd should be added before this line!  */
	{"help",				api_lib_help,				0,		0,			"Show gponmgr set usage."},
	{NULL, NULL, 0, 0, NULL}
};

const cmds_t gponmgr_set_dbg_level_command[] = {
/*	name,		func,					flags,	argcmin,	argc_errmsg */
	{"act",		do_set_dbg_lv_act,		0,		1,			"Set the GPON MAC act debug <enable or disable>"},
	{"omci",	do_set_dbg_lv_omci,		0,		1,			"Set the GPON MAC omci debug <enable or disable>"},
	{"oam",		do_set_dbg_lv_oam,		0,		1,			"Set the GPON MAC oam debug <enable or disable>"},
	{"int",		do_set_dbg_lv_int,		0,		1,			"Set the GPON MAC int debug <enable or disable>"},
	{"trace",	do_set_dbg_lv_trace,	0,		1,			"Set the GPON MAC trace debug <enable or disable>"},
	{"warning",	do_set_dbg_lv_warning,	0,		1,			"Set the GPON MAC warning debug <enable or disable>"},
	{"content",	do_set_dbg_lv_content,	0,		1,			"Set the GPON MAC content debug <enable or disable>"},
	{"debug",	do_set_dbg_lv_debug,	0,		1,			"Set the GPON MAC debug debug <enable or disable>"},
	{"err",		do_set_dbg_lv_err,		0,		1,			"Set the GPON MAC err debug <enable or disable>"},
	/* Cmd should be added before this line!  */
	{"help",	api_lib_help,			0,		0,			"Show gponmgr set dbg level usage."},
	{NULL, NULL, 0, 0, NULL}
};

const cmds_t gponmgr_set_eqd_offset_command[] = {
/*	name,		func,					flags,	argcmin,	argc_errmsg */
	{"o4",		do_set_eqd_off_o4,		0,		1,			"Set the EqD offset at o4 state <0~255>"},
	{"o5",		do_set_eqd_off_o5,		0,		1,			"Set the EqD offset at o5 state <0~255>"},
	{"flag",	do_set_eqd_off_flag,	0,		1,			"Set the EqD offset flag <+ or ->"},
	/* Cmd should be added before this line!  */
	{"help",	api_lib_help,			0,		0,			"Show gponmgr set eqd offset usage."},
	{NULL, NULL, 0, 0, NULL}
};

const cmds_t gponmgr_set_tod_command[] = {
/*	name,			func,					flags,	argcmin,	argc_errmsg */
	{"switch_time",	do_set_tod_switch_time,	0,		1,			"Set the GPON ToD switch time <8 hexadecimal digits>"},
	{"new_time",	do_set_tod_new_time,	0,		1,			"Set the GPON ToD new time <sec> <nanosec>"},
	/* Cmd should be added before this line!  */
	{"help",		api_lib_help,			0,		0,			"Show gponmgr set eqd offset usage."},
	{NULL, NULL, 0, 0, NULL}
};

const cmds_t gponmgr_set_act_timer_command[] = {
/*	name,		func,					flags,	argcmin,	argc_errmsg */
	{"to1",		do_set_act_timer_to1,	0,		1,			"Set the ONU activation to1 time (ms)"},
	{"to2",		do_set_act_timer_to2,	0,		1,			"Set the ONU activation to2 time (ms)"},
	/* Cmd should be added before this line!  */
	{"help",	api_lib_help,			0,		0,			"Show gponmgr set eqd offset usage."},
	{NULL, NULL, 0, 0, NULL}
};

const cmds_t gponmgr_set_dying_gasp_command[] = {
/*	name,			func,						flags,	argcmin,	argc_errmsg */
	{"mode",		do_set_dying_gasp_mode,		0,		1,			"Set the GPON Dying Gasp mode <sw | hw>"},
	{"num",			do_set_dying_gasp_num,		0,		1,			"Set the GPON Dying Gasp number <0~15>"},
	/* Cmd should be added before this line!  */
	{"help",		api_lib_help,				0,		0,			"Show gponmgr get usage."},
	{NULL, NULL, 0, 0, NULL}
};

const cmds_t gponmgr_set_sniffer_command[] = {
/*	name,		func,				flags,	argcmin,	argc_errmsg */
	{"gtc",		do_set_sniffer_gtc,	0,		1,			"Set the GPON sniffer mode <enable> <lan port 0~3>"},
	/* Cmd should be added before this line!  */
	{"help",	api_lib_help,		0,		0,			"Show gponmgr get usage."},
	{NULL, NULL, 0, 0, NULL}
};

const cmds_t gponmgr_set_test_command[] = {
/*	name,					func,								flags,	argcmin,	argc_errmsg */
	{"slp_req_ploamu",		do_set_test_slp_req_ploamu,			0,		1,			"Send sleep mode request PLOAMu <doze | sleep | wsleep>"},
	{"rei_ploamu",			do_set_test_rei_ploamu,				0,		1,			"Send REI PLOAMu <error counter>"},
	{"dying_gasp_ploamu",	do_set_test_dying_gasp_ploamu,		0,		0,			"Send Dying Gasp PLOAMu"},
	{"tod",					do_set_test_tod,					0,		1,			"Test ToD"},
	{"sw_reset",			do_set_test_sw_reset,				0,		0,			"Test software reset exclude reg module"},
	{"sw_resync",			do_set_test_sw_resync,				0,		0,			"Test software resync"},
	{"key_sw_by_sw",		do_set_test_aes_key_switch_by_sw,	0,		0,			"Test AES key switch by software"},
	/* Cmd should be added before this line!  */
	{"help",				api_lib_help,						0,		0,			"Show gponmgr get usage."},
	{NULL, NULL, 0, 0, NULL}
};

const cmds_t gponmgr_set_filter_command[] = {
/*	name,			func,								flags,	argcmin,	argc_errmsg */
	{"ext_bst_len",	do_set_ext_bst_len_ploamd_filter,	0,		1,			"Set filter ext bst len ploam <enable or disable>"},
	{"up_ovhead",	do_set_up_overhead_ploamd_filter,	0,		1,			"Set filter up overhead ploam <enable or disable>"},
	/* Cmd should be added before this line!  */
	{"help",		api_lib_help,						0,		0,			"Show gponmgr get usage."},
	{NULL, NULL, 0, 0, NULL}
};

const cmds_t gponmgr_set_dba_backdoor_command[] = {
/*	name,			func,					flags,	argcmin,	argc_errmsg */
	{"total",	do_set_dba_backdoor_total,	0,		1,			"Set total buffer size <0 ~ 2^31-1>"},
	{"green",	do_set_dba_backdoor_green,	0,		1,			"Set green buffer size <0 ~ 2^31-1>"},
	{"yellow",	do_set_dba_backdoor_yellow,	0,		1,			"Set yellow buffer size <0 ~ 2^31-1>"},
	/* Cmd should be added before this line!  */
	{"help",	api_lib_help,				0,		0,			"Show gponmgr get usage."},
	{NULL, NULL, 0, 0, NULL}
};

const cmds_t gponmgr_set_dba_slight_modify_command[] = {
/*	name,			func,						flags,	argcmin,	argc_errmsg */
	{"total",	do_set_dba_slight_modify_total,	0,		1,			"Set total buffer size <0 ~ 2^16-1>"},
	{"green",	do_set_dba_slight_modify_green,	0,		1,			"Set green buffer size <0 ~ 2^16-1>"},
	{"yellow",	do_set_dba_slight_modify_yellow,0,		1,			"Set yellow buffer size <0 ~ 2^16-1>"},
	/* Cmd should be added before this line!  */
	{"help",	api_lib_help,					0,		0,			"Show gponmgr get usage."},
	{NULL, NULL, 0, 0, NULL}
};

/************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
************************************************************************/

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC debug level.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dbg_lv(int argc, char *argv[], void *p)
{
#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return subcmd(gponmgr_set_dbg_level_command, argc, argv, (void *)gponmgr_set_dbg_level_command);
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC act debug level.
 Input Args:	see gponmgr_set_dbg_level_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dbg_lv_act(int argc, char *argv[], void *p)
{
	XPON_Mode_t enable;

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

	if(gponmgr_lib_set_dbg_level_act(enable) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dbg_level' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC omci debug level.
 Input Args:	see gponmgr_set_dbg_level_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dbg_lv_omci(int argc, char *argv[], void *p)
{
	XPON_Mode_t enable;

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

	if(gponmgr_lib_set_dbg_level_omci(enable) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dbg_level' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC oam debug level.
 Input Args:	see gponmgr_set_dbg_level_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dbg_lv_oam(int argc, char *argv[], void *p)
{
	XPON_Mode_t enable;

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

	if(gponmgr_lib_set_dbg_level_oam(enable) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dbg_level' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC int debug level.
 Input Args:	see gponmgr_set_dbg_level_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dbg_lv_int(int argc, char *argv[], void *p)
{
	XPON_Mode_t enable;

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

	if(gponmgr_lib_set_dbg_level_int(enable) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dbg_level' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC trace debug level.
 Input Args:	see gponmgr_set_dbg_level_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dbg_lv_trace(int argc, char *argv[], void *p)
{
	XPON_Mode_t enable;

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

	if(gponmgr_lib_set_dbg_level_trace(enable) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dbg_level' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC warning debug level.
 Input Args:	see gponmgr_set_dbg_level_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dbg_lv_warning(int argc, char *argv[], void *p)
{
	XPON_Mode_t enable;

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

	if(gponmgr_lib_set_dbg_level_warning(enable) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dbg_level' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC content debug level.
 Input Args:	see gponmgr_set_dbg_level_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dbg_lv_content(int argc, char *argv[], void *p)
{
	XPON_Mode_t enable;

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

	if(gponmgr_lib_set_dbg_level_content(enable) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dbg_level' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC debug debug level.
 Input Args:	see gponmgr_set_dbg_level_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dbg_lv_debug(int argc, char *argv[], void *p)
{
	XPON_Mode_t enable;

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

	if(gponmgr_lib_set_dbg_level_debug(enable) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dbg_level' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC err debug level.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dbg_lv_err(int argc, char *argv[], void *p)
{
	XPON_Mode_t enable;

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

	if(gponmgr_lib_set_dbg_level_err(enable) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dbg_level' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the EqD offset at O4 or O5 state.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_eqd_off(int argc, char *argv[], void *p)
{
#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return subcmd(gponmgr_set_eqd_offset_command, argc, argv, (void *)gponmgr_set_eqd_offset_command);
}

/******************************************************************************
 Descriptor:	It's used to set the EqD offset at O4 state.
 Input Args:	see gponmgr_set_eqd_offset_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_eqd_off_o4(int argc, char *argv[], void *p)
{
	long eqdO4Offset;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	eqdO4Offset = strtol(argv[1], NULL, 0);
	if(eqdO4Offset > 255) {
		printf("Input Error: eqd offset must be 0 ~ 255.\n") ;
		return GPONMGR_FAIL;
	}
	
	if(gponmgr_lib_set_eqd_offset_o4((unchar)eqdO4Offset) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'eqd_off o4' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the EqD offset at O5 state.
 Input Args:	see gponmgr_set_eqd_offset_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_eqd_off_o5(int argc, char *argv[], void *p)
{
	long eqdO5Offset;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	eqdO5Offset = strtol(argv[1], NULL, 0);
	if(eqdO5Offset > 255) {
		printf("Input Error: eqd offset must be 0 ~ 255.\n") ;
		return GPONMGR_FAIL;
	}
	
	if(gponmgr_lib_set_eqd_offset_o5((unchar)eqdO5Offset) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'eqd_off o5' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the EqD offset flag.
 Input Args:	see gponmgr_set_eqd_offset_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_eqd_off_flag(int argc, char *argv[], void *p)
{
	char gponEqdOffsetflag ;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if((argv[1][0] == '+') || (argv[1][0] == '-')) {
		gponEqdOffsetflag = argv[1][0];
	} else {
		printf("Input Error: eqd offset flag must be '+' or '-'.\n") ;
		return GPONMGR_FAIL;
	}
		
	if(gponmgr_lib_set_eqd_offset_flag(gponEqdOffsetflag) == GPONMGR_FAIL) {
		printf("Exec. Failed: Get the 'eqd_off flag' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set GPON MAC counter type.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_cnt_type(int argc, char *argv[], void *p)
{
	GPON_COUNTER_TYPE_t type ;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(strncmp(argv[1], "gem", strlen("gem")) == 0) {
		type = GPON_COUNTER_TYPE_GEM;
	} else if(strncmp(argv[1], "ethernet", strlen("ethernet")) == 0) {
		type = GPON_COUNTER_TYPE_ETHERNET;
	} else {
		printf("Input Error: must be \"gem\" or \"ethernet\".\n") ;
		return GPONMGR_FAIL;
	}
		
	if(gponmgr_lib_set_counter_type(type) == GPONMGR_FAIL) {
		printf("Exec. Failed: Get the 'cnt_type' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set GPON response time.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_rsp_time(int argc, char *argv[], void *p)
{
	long time ;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	time = strtol(argv[1], NULL, 16);
	if(time > 0xFFFF) {
		printf("Input Error: rsp time must be 0 ~ (2^16 - 1).\n") ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_response_time((ushort)time) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'rsp_time flag' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC internal delay fine tune(BFB64028[15:8]).
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_itl_dly_fine_tune(int argc, char *argv[], void *p)
{
	long delay ;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	delay = strtol(argv[1], NULL, 16);
	if(delay > ((1 << 8) - 1)) {
		printf("Input Error: eqd offset must be 0 ~ 255.\n") ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_internal_delay_fine_tune((ushort)delay) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'do_set_itl_dly_fine_tune delay' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC whether burst mode overhead length supports 
                 more than 128 bytes or not.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_burst_mode_overhead(int argc, char *argv[], void *p)
{
	GPON_BURST_MODE_OVERHEAD_LEN_T type ;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(strncmp(argv[1], "enable", strlen("enable")) == 0) {
		type = GPON_BURST_MODE_OVERHEAD_LEN_MORE_THAN_128;
	} else if(strncmp(argv[1], "disable", strlen("disable")) == 0) {
		type = GPON_BURST_MODE_OVERHEAD_LEN_DEFAULT;
	} else {
		printf("Input Error: must be \"enable\" or \"disable\".\n") ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_burst_mode_overhead(type) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'burst_mode_overhead type' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to clear GPON MAC counter.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_clr_cnt(int argc, char *argv[], void *p)
{
	GPON_SW_HW_SELECT_T clear ;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(strncmp(argv[1], "sw", strlen("sw")) == 0) {
		clear = GPON_SW;
	} else if(strncmp(argv[1], "hw", strlen("hw")) == 0) {
		clear = GPON_HW;
	} else if(strncmp(argv[1], "all", strlen("all")) == 0) {
		clear = GPON_SW_HW;
	} else {
		printf("Input Error: must be \"sw\", \"hw\" or \"all\".\n") ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_clear_counter(clear) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'clr_cnt type' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set when to begin using the new encryption key.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_key_switch_time(int argc, char *argv[], void *p)
{
	uint spf ;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(strlen(argv[1]) == 8) {
		spf = (uint)strtoul(argv[1], NULL, 16);
	} else {
		printf("Input Error: key switch time length must be 8 hexadecimal.\n") ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_key_switch_time(spf) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'key_switch_time' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the GPON ToD parameters.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_tod(int argc, char *argv[], void *p)
{
#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return subcmd(gponmgr_set_tod_command, argc, argv, (void *)gponmgr_set_tod_command);
}

/******************************************************************************
 Descriptor:	It's used to set the GPON ToD switch time.
 Input Args:	see gponmgr_set_tod_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_tod_switch_time(int argc, char *argv[], void *p)
{
	struct XMCS_GponTodCfg_S gponTodCfg ;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(strlen(argv[1]) > 8) {
		printf("Input Error: switch_time length must be less than 8.\n") ;
		return GPONMGR_FAIL;
	}

	memset(&gponTodCfg, 0, sizeof(gponTodCfg)) ;
	gponTodCfg.superframe = (uint)strtoul(argv[1], NULL, 16) ;

	if(gponmgr_lib_set_tod_switch_time(&gponTodCfg) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'tod switch_time' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the GPON ToD new time.
 Input Args:	see gponmgr_set_tod_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_tod_new_time(int argc, char *argv[], void *p)
{
	struct XMCS_GponTodCfg_S gponTodCfg ;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	memset(&gponTodCfg, 0, sizeof(gponTodCfg)) ;
	gponTodCfg.sec = (uint)strtoul(argv[1], NULL, 10) ;
	gponTodCfg.nanosec = (uint)strtoul(argv[2], NULL, 10) ;

	if(gponmgr_lib_set_tod_new_time(&gponTodCfg) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'tod new_time' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the ONU activation timer.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_act_timer(int argc, char *argv[], void *p)
{
#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return subcmd(gponmgr_set_act_timer_command, argc, argv, (void *)gponmgr_set_act_timer_command);
}

/******************************************************************************
 Descriptor:	It's used to set the ONU activation to1 timer.
 Input Args:	see gponmgr_set_act_timer_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_act_timer_to1(int argc, char *argv[], void *p)
{
	uint to1Timer;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	to1Timer = (uint)strtoul(argv[1], NULL, 10) ;
	if(gponmgr_lib_set_act_timer_to1(to1Timer) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'act_timer to1' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the ONU activation to2 timer.
 Input Args:	see gponmgr_set_act_timer_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_act_timer_to2(int argc, char *argv[], void *p)
{
	uint to2Timer;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	to2Timer = (uint)strtoul(argv[1], NULL, 10) ;
	if(gponmgr_lib_set_act_timer_to2(to2Timer) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'act_timer to2' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the GPON DBA block size.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_block_size(int argc, char *argv[], void *p)
{
	ushort blockSize;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(strlen(argv[1]) > 4) {
		printf("Input Error: block_size length must be less than 4.\n") ;
		return GPONMGR_FAIL;
	}

	blockSize = (uint)strtoul(argv[1], NULL, 10) ;
	if(blockSize < 1 || blockSize > 9999) {
		printf("Input Error: block_size must be 1 ~ 9999.\n") ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_dba_block_size(blockSize) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'block_size' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the GPON Dying Gasp parameters.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dying_gasp(int argc, char *argv[], void *p)
{
#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return subcmd(gponmgr_set_dying_gasp_command, argc, argv, (void *)gponmgr_set_dying_gasp_command);
}

/******************************************************************************
 Descriptor:	It's used to set the GPON Dying Gasp mode.
 Input Args:	see gponmgr_set_dying_gasp_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dying_gasp_mode(int argc, char *argv[], void *p)
{
	GPON_SW_HW_SELECT_T mode;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(strncmp(argv[1], "sw", strlen("sw")) == 0) {
		mode = GPON_SW;
	} else if(strncmp(argv[1], "hw", strlen("hw")) == 0) {
		mode = GPON_HW;
	} else {
		printf("Input Error: mode must be \"sw\" or \"hw\".\n") ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_dying_gasp_mode(mode) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dying_gasp mode' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;

	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the GPON Dying Gasp number.
 Input Args:	see gponmgr_set_dying_gasp_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dying_gasp_num(int argc, char *argv[], void *p)
{
	uint num;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	num = (uint)strtoul(argv[1], NULL, 10) ;
	if(num > 15) {
		printf("Input Error: mode must be 0~15.\n") ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_dying_gasp_num(num) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dying_gasp num' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;

	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC whether burst mode overhead length supports 
                 more than 128 bytes or not.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_up_traffic(int argc, char *argv[], void *p)
{
	XPON_Mode_t mode;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(strncmp(argv[1], "enable", strlen("enable")) == 0) {
		mode = XPON_ENABLE;
	} else if(strncmp(argv[1], "disable", strlen("disable")) == 0) {
		mode = XPON_DISABLE;
	} else {
		printf("Input Error: must be \"enable\" or \"disable\".\n") ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_up_traffic(mode) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'up_traffic type' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set sniffer configure.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_sniffer(int argc, char *argv[], void *p)
{
#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return subcmd(gponmgr_set_sniffer_command, argc, argv, (void *)gponmgr_set_sniffer_command);
}

/******************************************************************************
 Descriptor:	It's used to set sniffer mode configure.
 Input Args:	see gponmgr_set_sniffer_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_sniffer_gtc(int argc, char *argv[], void *p)
{
	GPON_DEV_SNIFFER_MODE_T sniffer;
	uint lan_port;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	memset(&sniffer, 0, sizeof(sniffer)) ;
	if(strncmp(argv[1], "enable", strlen("enable")) == 0) {
		sniffer.enable= XPON_ENABLE;

		lan_port = (uint)strtoul(argv[2], NULL, 10) ;
		switch(lan_port) {
			case 0:
				sniffer.lan_port = SNIFFER_MODE_LAN0;
				break;
			case 1:
				sniffer.lan_port = SNIFFER_MODE_LAN1;
				break;
			case 2:
				sniffer.lan_port = SNIFFER_MODE_LAN2;
				break;
			case 3:
				sniffer.lan_port = SNIFFER_MODE_LAN3;
				break;
			default:
				printf("Input Error: mode must be 0~3.\n") ;
				return GPONMGR_FAIL;
		}
	} else if(strncmp(argv[1], "disable", strlen("disable")) == 0) {
		sniffer.enable = XPON_DISABLE;
	} else {
		printf("Input Error: mode must be \"enable\" or \"disable\".\n") ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_sniffer_gtc(&sniffer) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'sniffer gtc' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;

	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set filter.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_filter(int argc, char *argv[], void *p)
{
#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return subcmd(gponmgr_set_filter_command, argc, argv, (void *)gponmgr_set_filter_command);
}

/******************************************************************************
 Descriptor:	It's used to set enable/disable filter extented burst length PLOAM at O5 state.
 Input Args:	see gponmgr_set_filter_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_ext_bst_len_ploamd_filter(int argc, char *argv[], void *p)
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

	if(gponmgr_lib_set_ext_bst_len_ploamd_filter(enable) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'filter ext_bst_len' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set enable/disable filter Upstream Overhead PLOAM at O5 state.
 Input Args:	see gponmgr_set_filter_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_up_overhead_ploamd_filter(int argc, char *argv[], void *p)
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

	if(gponmgr_lib_set_up_overhead_ploamd_filter(enable) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'filter up_ovhead' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set dba backdoor enable/disable.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dba_backdoor(int argc, char *argv[], void *p)
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
		return subcmd(gponmgr_set_dba_backdoor_command, argc, argv, (void *)gponmgr_set_dba_backdoor_command);
	}

	if(gponmgr_lib_set_dba_backdoor(enable) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dbru_fix' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set dba backdoor total size.
 Input Args:	see gponmgr_set_dba_backdoor_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dba_backdoor_total(int argc, char *argv[], void *p)
{
	uint total_size;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	total_size = (uint)strtoul(argv[1], NULL, 10) ;
	if(gponmgr_lib_set_dba_backdoor_total(total_size) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dbru_fix total' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set dba backdoor green size.
 Input Args:	see gponmgr_set_dba_backdoor_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dba_backdoor_green(int argc, char *argv[], void *p)
{
	uint green_size;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	green_size = (uint)strtoul(argv[1], NULL, 10) ;
	if(gponmgr_lib_set_dba_backdoor_green(green_size) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dbru_fix green' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set dba backdoor yellow size.
 Input Args:	see gponmgr_set_dba_backdoor_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dba_backdoor_yellow(int argc, char *argv[], void *p)
{
	uint yellow_size;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	yellow_size = (uint)strtoul(argv[1], NULL, 10) ;
	if(gponmgr_lib_set_dba_backdoor_yellow(yellow_size) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dbru_fix yellow' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set dba slight modify enable/disable.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dba_slight_modify(int argc, char *argv[], void *p)
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
		return subcmd(gponmgr_set_dba_slight_modify_command, argc, argv, (void *)gponmgr_set_dba_slight_modify_command);
	}

	if(gponmgr_lib_set_dba_slight_modify(enable) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dbru_offset' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set dba slight modify total size.
 Input Args:	see gponmgr_set_dba_slight_modify_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dba_slight_modify_total(int argc, char *argv[], void *p)
{
	uint total_size;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	total_size = (uint)strtoul(argv[1], NULL, 10) ;
	if(total_size > 0xFFFF) {
		printf("Input Error: total_size must be 0 ~ 2^16-1.\n") ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_dba_slight_modify_total((ushort)total_size) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dbru_offset total' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set dba slight modify green size.
 Input Args:	see gponmgr_set_dba_slight_modify_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dba_slight_modify_green(int argc, char *argv[], void *p)
{
	uint green_size;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	green_size = (uint)strtoul(argv[1], NULL, 10) ;
	if(green_size > 0xFFFF) {
		printf("Input Error: green_size must be 0 ~ 2^16-1.\n") ;
		return GPONMGR_FAIL;
	}
	
	if(gponmgr_lib_set_dba_slight_modify_green((ushort)green_size) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dbru_offset green' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set dba slight modify yellow size.
 Input Args:	see gponmgr_set_dba_slight_modify_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_dba_slight_modify_yellow(int argc, char *argv[], void *p)
{
	uint yellow_size;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	yellow_size = (uint)strtoul(argv[1], NULL, 10) ;
	if(yellow_size > 0xFFFF) {
		printf("Input Error: yellow_size must be 0 ~ 2^16-1.\n") ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_dba_slight_modify_yellow((ushort)yellow_size) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'dbru_offset yellow' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;
	
	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to set o3 and o4 ploam control.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_o3_o4_ploam(int argc, char *argv[], void *p)
{
	GPON_SW_HW_SELECT_T mode;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(strncmp(argv[1], "sw", strlen("sw")) == 0) {
		mode = GPON_SW;
	} else if(strncmp(argv[1], "hw", strlen("hw")) == 0) {
		mode = GPON_HW;
	} else {
		printf("Input Error: mode must be \"sw\" or \"hw\".\n") ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_set_o3_o4_ploam_ctrl(mode) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'o3_o4_ploam' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;

	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to test.
 Input Args:	see gponmgr_set_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_test(int argc, char *argv[], void *p)
{
#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return subcmd(gponmgr_set_test_command, argc, argv, (void *)gponmgr_set_test_command);
}

/******************************************************************************
 Descriptor:	It's used to send ploam sleep request.
 Input Args:	see gponmgr_set_test_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_test_slp_req_ploamu(int argc, char *argv[], void *p)
{
	GPON_PLOAMu_SLEEP_MODE_t mode;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(strncmp(argv[1], "doze", strlen("doze")) == 0) {
		mode = Doze;
	} else if(strncmp(argv[1], "sleep", strlen("sleep")) == 0) {
		mode = Sleep;
	} else if(strncmp(argv[1], "wsleep", strlen("wsleep")) == 0) {
		mode = WSleep;
	} else {
		printf("Input Error: mode must be \"doze\", \"sleep\" or \"wsleep\".\n") ;
		return GPONMGR_FAIL;
	}

	if(gponmgr_lib_test_send_ploam_sleep_request(mode) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'test slp_req_ploamu' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;

	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to send ploam rei.
 Input Args:	see gponmgr_set_test_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_test_rei_ploamu(int argc, char *argv[], void *p)
{
	uint counter;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	counter = (uint)strtoul(argv[1], NULL, 10) ;
	if(gponmgr_lib_test_send_ploam_rei(counter) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'test rei_ploamu' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;

	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to send ploam Dying Gasp.
 Input Args:	see gponmgr_set_test_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_test_dying_gasp_ploamu(int argc, char *argv[], void *p)
{
#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(gponmgr_lib_test_send_ploam_dying_gasp() == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'test dying_gasp_ploamu' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;

	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to test ToD function.
                 The ToD interrupt will occur after newTime seconds.
 Input Args:	see gponmgr_set_test_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_test_tod(int argc, char *argv[], void *p)
{
	uint newTime;

#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	newTime = (uint)strtoul(argv[1], NULL, 10) ;
	if(gponmgr_lib_test_tod(newTime) == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'test tod' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;

	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to send ploam Dying Gasp.
 Input Args:	see gponmgr_set_test_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_test_aes_key_switch_by_sw(int argc, char *argv[], void *p)
{
#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(gponmgr_lib_test_aes_key_switch_by_sw() == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'test key_sw_by_sw' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;

	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to software reset GPON MAC exclude reg module.
 Input Args:	see gponmgr_set_test_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_test_sw_reset(int argc, char *argv[], void *p)
{
#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(gponmgr_lib_test_sw_reset() == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'test sw_reset' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;

	return GPONMGR_SUCCESS;
}

/******************************************************************************
 Descriptor:	It's used to software resync.
 Input Args:	see gponmgr_set_test_command.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int do_set_test_sw_resync(int argc, char *argv[], void *p)
{
#if API_CMD_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if(gponmgr_lib_test_sw_resync() == GPONMGR_FAIL) {
		printf("Exec. Failed: Set the 'test sw_resync' command failed\n") ;
		return GPONMGR_FAIL;
	}
	
	printf("Exec. Successful\n") ;

	return GPONMGR_SUCCESS;
}

