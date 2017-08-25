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
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "libapi_lib_gponmgr.h"

#include <xmcs/xmcs_gpon.h>
#include <xmcs/xmcs_if.h>

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

/************************************************************************
*                  F U N C T I O N   D E F I N I T I O N S
************************************************************************/

/************************************************************************
*                  P U B L I C   D A T A
************************************************************************/

/************************************************************************
*                  P R I V A T E   D A T A
************************************************************************/

/************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
************************************************************************/

/******************************************************************************
 Descriptor:	It's used to ioctl to gpon device.
 Input Args:	cmd: ioctl command.
                     p: pointer to gpon driver structure, it is used to 
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
static int gponmgr_lib_ioctl(int cmd, void *p)
{
	int fd, ret;
	
	fd = open("/dev/pon", O_RDWR);
    if (fd < 0) {
		printf("Open %s pseudo device failed\n","/dev/pon");
		return GPONMGR_FAIL;
    }

	ret = ioctl(fd, cmd, p);
	close(fd);

	if(ret >= 0) {
		return GPONMGR_SUCCESS;
	} else {
		return GPONMGR_FAIL;
	}
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC act debug level.
 Input Args:	enable: GPONMGR_ENABLE/GPONMGR_DISABLE act debug level.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dbg_level_act(XPON_Mode_t enable)
{
	struct XMCS_DebugLevel_S dbg;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	dbg.mask = MSG_ACT;
	dbg.enable = enable;

	return gponmgr_lib_ioctl(IO_IOS_DBG_LEVEL, &dbg);
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC omci debug level.
 Input Args:	GPONMGR_ENABLE/GPONMGR_DISABLE omci debug level.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dbg_level_omci(XPON_Mode_t enable)
{
	struct XMCS_DebugLevel_S dbg;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	dbg.mask = MSG_OMCI;
	dbg.enable = enable;

	return gponmgr_lib_ioctl(IO_IOS_DBG_LEVEL, &dbg);
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC oam debug level.
 Input Args:	GPONMGR_ENABLE/GPONMGR_DISABLE oam debug level.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dbg_level_oam(XPON_Mode_t enable)
{
	struct XMCS_DebugLevel_S dbg;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	dbg.mask = MSG_OAM;
	dbg.enable = enable;

	return gponmgr_lib_ioctl(IO_IOS_DBG_LEVEL, &dbg);
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC int debug level.
 Input Args:	GPONMGR_ENABLE/GPONMGR_DISABLE int debug level.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dbg_level_int(XPON_Mode_t enable)
{
	struct XMCS_DebugLevel_S dbg;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	dbg.mask = MSG_INT;
	dbg.enable = enable;

	return gponmgr_lib_ioctl(IO_IOS_DBG_LEVEL, &dbg);
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC trace debug level.
 Input Args:	GPONMGR_ENABLE/GPONMGR_DISABLE trace debug level.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dbg_level_trace(XPON_Mode_t enable)
{
	struct XMCS_DebugLevel_S dbg;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	dbg.mask = MSG_TRACE;
	dbg.enable = enable;

	return gponmgr_lib_ioctl(IO_IOS_DBG_LEVEL, &dbg);
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC warning debug level.
 Input Args:	pgponEqdOffset: GPONMGR_ENABLE/GPONMGR_DISABLE warning debug level.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dbg_level_warning(XPON_Mode_t enable)
{
	struct XMCS_DebugLevel_S dbg;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	dbg.mask = MSG_WARN;
	dbg.enable = enable;

	return gponmgr_lib_ioctl(IO_IOS_DBG_LEVEL, &dbg);
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC content debug level.
 Input Args:	GPONMGR_ENABLE/GPONMGR_DISABLE content debug level.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dbg_level_content(XPON_Mode_t enable)
{
	struct XMCS_DebugLevel_S dbg;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	dbg.mask = MSG_CONTENT;
	dbg.enable = enable;

	return gponmgr_lib_ioctl(IO_IOS_DBG_LEVEL, &dbg);
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC debug debug level.
 Input Args:	GPONMGR_ENABLE/GPONMGR_DISABLE debug debug level.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dbg_level_debug(XPON_Mode_t enable)
{
	struct XMCS_DebugLevel_S dbg;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	dbg.mask = MSG_DBG;
	dbg.enable = enable;

	return gponmgr_lib_ioctl(IO_IOS_DBG_LEVEL, &dbg);
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC err debug level.
 Input Args:	GPONMGR_ENABLE/GPONMGR_DISABLE err debug level.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dbg_level_err(XPON_Mode_t enable)
{
	struct XMCS_DebugLevel_S dbg;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	dbg.mask = MSG_ERR;
	dbg.enable = enable;

	return gponmgr_lib_ioctl(IO_IOS_DBG_LEVEL, &dbg);
}

/******************************************************************************
 Descriptor:	It's used to set the EqD offset at O4 state.
 Input Args:	pgponEqdOffset: used to set O4 eqd offset value.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_eqd_offset_o4(unchar gponEqdO4Offset)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

															/* uint cast is used to size alignment */
	return gponmgr_lib_ioctl(GPON_IOS_EQD_OFFSET_O4, (void *)((uint)gponEqdO4Offset));
}

/******************************************************************************
 Descriptor:	It's used to set the EqD offset at O5 state.
 Input Args:	pgponEqdOffset: used to set O5 eqd offset value.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_eqd_offset_o5(unchar gponEqdO5Offset)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

															/* uint cast is used to size alignment */
	return gponmgr_lib_ioctl(GPON_IOS_EQD_OFFSET_O5, (void *)((uint)gponEqdO5Offset));
}

/******************************************************************************
 Descriptor:	It's used to set the EqD offset flag.
 Input Args:	pgponEqdOffset: used to set eqd offset with plus or minus.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_eqd_offset_flag(char gponEqdOffsetflag)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if((gponEqdOffsetflag != '+') && (gponEqdOffsetflag != '-')) {
		return GPONMGR_FAIL;
	}

																/* uint cast is used to size alignment */
	return gponmgr_lib_ioctl(GPON_IOS_EQD_OFFSET_FLAG, (void *)((uint)gponEqdOffsetflag));
}

/******************************************************************************
 Descriptor:	It's used to set GPON MAC counter type.
 Input Args:	type: used to set counter type.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_counter_type(GPON_COUNTER_TYPE_t type)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOS_COUNTER_TYPE, (void *)type);
}

/******************************************************************************
 Descriptor:	It's used to set GPON response time.
 Input Args:	time: used to set GPON MAC response time.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_response_time(ushort time)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

															/* uint cast is used to size alignment */
	return gponmgr_lib_ioctl(GPON_IOS_RESPONSE_TIME, (void *)((uint)time));
}

/******************************************************************************
 Descriptor:	It's used to set GPON MAC internal delay fine tune(BFB64208[15:8]).
 Input Args:	delay: used to set GPON MAC internal delay fine tune.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_internal_delay_fine_tune(unchar delay)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

																		/* uint cast is used to size alignment */
	return gponmgr_lib_ioctl(GPON_IOS_INTERNAL_DELAY_FINE_TUNE, (void *)((uint)delay));
}

/******************************************************************************
 Descriptor:	It's used to set the GPON MAC whether burst mode overhead exceeds 128bytes or not.
 Input Args:	ptype: used to set GPON MAC whether burst mode overhead exceeds 128bytes or not.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_burst_mode_overhead(GPON_BURST_MODE_OVERHEAD_LEN_T type)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOS_BURST_MODE_OVERHEAD_LEN, (void *)type);
}

/******************************************************************************
 Descriptor:	It's used to clear GPON MAC counter.
 Input Args:	clear: clear GPON MAC counter.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_clear_counter(GPON_SW_HW_SELECT_T clear)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOS_CLEAR_COUNTER, (void *)clear);
}

/******************************************************************************
 Descriptor:	It's used to clear GPON MAC serial number.
 Input Args:	psn: serial number.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_sn(char *psn)
{
	struct XMCS_GponSnPasswd_S gponSnPasswd ;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	memcpy(gponSnPasswd.sn, psn, GPON_SN_LENS) ;

	return gponmgr_lib_ioctl(GPON_IOS_SN, (void *)&gponSnPasswd);
}

/******************************************************************************
 Descriptor:	It's used to clear GPON MAC password.
 Input Args:	ppasswd: password.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_passwd(char *ppasswd)
{
	struct XMCS_GponSnPasswd_S gponSnPasswd ;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	memcpy(gponSnPasswd.passwd, ppasswd, GPON_PASSWD_LENS);

	return gponmgr_lib_ioctl(GPON_IOS_PASSWD, (void *)&gponSnPasswd);
}

/******************************************************************************
 Descriptor:	It's used to set when to begin using the new encryption key.
 Input Args:	spf: superframe counter.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_key_switch_time(uint spf)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOS_KEY_SWITCH_TIME, (void *)spf);
}

/******************************************************************************
 Descriptor:	It's used to set the encryption key.
 Input Args:	pkey: 16 unchar array encryption key. It stored 32 hexadecimal digits.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_encrypt_key(unchar *pkey)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOS_ENCRYPT_KEY, (void *)pkey);
}

/******************************************************************************
 Descriptor:	It's used to set Tod switch time.
 Input Args:	pgponTodCfg: ToD parameter structure.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_tod_switch_time(struct XMCS_GponTodCfg_S *pgponTodCfg)
{
	struct XMCS_GponTodCfg_S gponTodCfg;
		
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	memset(&gponTodCfg, 0, sizeof(gponTodCfg)) ;
	if(gponmgr_lib_get_new_tod(&gponTodCfg) == GPONMGR_FAIL) {
		return GPONMGR_FAIL;
	}
	pgponTodCfg->sec= gponTodCfg.sec;
	pgponTodCfg->nanosec= gponTodCfg.nanosec;

	return gponmgr_lib_ioctl(GPON_IOS_TOD_CFG, (void *)pgponTodCfg);
}

/******************************************************************************
 Descriptor:	It's used to set Tod new time.
 Input Args:	pgponTodCfg: ToD parameter structure.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_tod_new_time(struct XMCS_GponTodCfg_S *pgponTodCfg)
{
	struct XMCS_GponTodCfg_S gponTodCfg;
		
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	memset(&gponTodCfg, 0, sizeof(gponTodCfg)) ;
	if(gponmgr_lib_get_tod_switch_time(&gponTodCfg) == GPONMGR_FAIL) {
		return GPONMGR_FAIL;
	}
	pgponTodCfg->superframe = gponTodCfg.superframe;

	return gponmgr_lib_ioctl(GPON_IOS_TOD_CFG, (void *)pgponTodCfg);
}


/******************************************************************************
 Descriptor:	It's used to set ONU activation to1 timer.
 Input Args:	pActTimer: XMCS_GponActTimer_S parameter structure.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_act_timer_to1(uint to1Timer)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOS_ACT_TIMER_TO1, (void *)to1Timer);
}

/******************************************************************************
 Descriptor:	It's used to set ONU activation to2 timer.
 Input Args:	pActTimer: XMCS_GponActTimer_S parameter structure.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_act_timer_to2(uint to2Timer)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOS_ACT_TIMER_TO2, (void *)to2Timer);
}

/******************************************************************************
 Descriptor:	It's used to set dba block size.
 Input Args:	blockSize: used to set dba block size.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dba_block_size(ushort blockSize)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	                                                          /* uint cast is used to size alignment */
	return gponmgr_lib_ioctl(GPON_IOS_DBA_BLOCK_SIZE, (void *)((uint)blockSize));
}

/******************************************************************************
 Descriptor:	It's used to set the GPON Dying Gasp mode.
 Input Args:	mode: used to set dying gasp mode.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dying_gasp_mode(GPON_SW_HW_SELECT_T mode)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOS_DYING_GASP_MODE, (void *)mode);
}

/******************************************************************************
 Descriptor:	It's used to set the GPON Dying Gasp number.
 Input Args:	num: used to set dying gasp number.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dying_gasp_num(uint num)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOS_DYING_GASP_NUM, (void *)num);
}

/******************************************************************************
 Descriptor:	It's used to set software upstream traffic enable or disable.
 Input Args:	mode: used to set upstream traffic.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_up_traffic(XPON_Mode_t mode)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	if((mode != XPON_ENABLE) && mode != XPON_DISABLE) {
		return GPONMGR_FAIL;
	}

	return gponmgr_lib_ioctl(GPON_IOS_UP_TRAFFIC, (void *)mode);
}

/******************************************************************************
 Descriptor:	It's used to set sniffer mode.
 Input Args:	sniffer: used to set sniffer mode.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_sniffer_gtc(GPON_DEV_SNIFFER_MODE_T *sniffer)
{
	int ret = GPONMGR_FAIL;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

#ifdef TCSUPPORT_CPU_EN7521
	sniffer->packet_padding =	XPON_ENABLE;
	/* Set tx */
	sniffer->tx_da =			0x0001;
	sniffer->tx_sa =			0x0002;
	sniffer->tx_ethertype =		0x88b6;
	sniffer->tx_vid =			0x0001;
	sniffer->tx_tpid=			sniffer->lan_port;
	/* Set rx */
	sniffer->rx_da =			0x0011;
	sniffer->rx_sa =			0x0012;
	sniffer->rx_ethertype =		0x88b6;
	sniffer->rx_vid =			0x0001;
	sniffer->rx_tpid=			sniffer->lan_port;
	ret = gponmgr_lib_ioctl(GPON_IOS_SNIFFER_GTC, (void *)sniffer);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to set enable/disable filter extented burst length PLOAM at O5 state.
 Input Args:	enable: used to enable/disable filter.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_ext_bst_len_ploamd_filter(XPON_Mode_t enable)
{
	int ret = GPONMGR_FAIL;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

#ifdef TCSUPPORT_CPU_EN7521
	ret = gponmgr_lib_ioctl(GPON_IOS_EXT_BST_LEN_PLOAMD_FILTER_IN_O5, (void *)enable);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to set enable/disable filter Upstream Overhead PLOAM at O5 state.
 Input Args:	enable: used to enable/disable filter.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_up_overhead_ploamd_filter(XPON_Mode_t enable)
{
	int ret = GPONMGR_FAIL;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

#ifdef TCSUPPORT_CPU_EN7521
	ret = gponmgr_lib_ioctl(GPON_IOS_UP_OVERHEAD_PLOAMD_FILTER_IN_O5, (void *)enable);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to set enable/disable tx data length aligned multiple of 4.
 Input Args:	enable: used to enable/disable aligned multiple of 4.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_tx_4bytes_align(XPON_Mode_t enable)
{
	int ret = GPONMGR_FAIL;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

#ifdef TCSUPPORT_CPU_EN7521
	ret = gponmgr_lib_ioctl(GPON_IOS_TX_4BYTES_ALIGN, (void *)enable);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to enable/disable DBA backdoor.
 Input Args:	enable: used to enable/disable DBA backdoor.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dba_backdoor(XPON_Mode_t enable)
{
	int ret = GPONMGR_FAIL;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

#ifdef TCSUPPORT_CPU_EN7521
	ret = gponmgr_lib_ioctl(GPON_IOS_DBA_BACKDOOR, (void *)enable);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to set DBA backdoor total size.
 Input Args:	total_size: used to set DBA backdoor total size.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dba_backdoor_total(uint total_size)
{
	int ret = GPONMGR_FAIL;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

#ifdef TCSUPPORT_CPU_EN7521
	ret = gponmgr_lib_ioctl(GPON_IOS_DBA_BACKDOOR_TOTAL, (void *)total_size);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to set DBA backdoor green size.
 Input Args:	total_size: used to set DBA backdoor green size.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dba_backdoor_green(uint green_size)
{
	int ret = GPONMGR_FAIL;

#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

#ifdef TCSUPPORT_CPU_EN7521
	ret = gponmgr_lib_ioctl(GPON_IOS_DBA_BACKDOOR_GREEN, (void *)green_size);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to set DBA backdoor yellow size.
 Input Args:	total_size: used to set DBA backdoor yellow size.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dba_backdoor_yellow(uint yellow_size)
{
	int ret = GPONMGR_FAIL;

#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

#ifdef TCSUPPORT_CPU_EN7521
	ret = gponmgr_lib_ioctl(GPON_IOS_DBA_BACKDOOR_YELLOW, (void *)yellow_size);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to enable/disable DBA slight modify.
 Input Args:	enable: used to enable/disable DBA slight modify.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dba_slight_modify(XPON_Mode_t enable)
{
	int ret = GPONMGR_FAIL;

#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

#ifdef TCSUPPORT_CPU_EN7521
	ret = gponmgr_lib_ioctl(GPON_IOS_DBA_SLIGHT_MODIFY, (void *)enable);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to set DBA backdoor total size.
 Input Args:	total_size: used to set DBA slight modify total size.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dba_slight_modify_total(ushort total_size)
{
	int ret = GPONMGR_FAIL;

#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

#ifdef TCSUPPORT_CPU_EN7521
																	   /* uint cast is used to size alignment */
	ret = gponmgr_lib_ioctl(GPON_IOS_DBA_SLIGHT_MODIFY_TOTAL, (void *)((uint)total_size));
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to set DBA backdoor green size.
 Input Args:	total_size: used to set DBA slight modify green size.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dba_slight_modify_green(ushort green_size)
{
	int ret = GPONMGR_FAIL;

#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

#ifdef TCSUPPORT_CPU_EN7521
																	   /* uint cast is used to size alignment */
	ret = gponmgr_lib_ioctl(GPON_IOS_DBA_SLIGHT_MODIFY_GREEN, (void *)((uint)green_size));
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to set DBA backdoor yellow size.
 Input Args:	total_size: used to set DBA slight modify yellow size.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_dba_slight_modify_yellow(ushort yellow_size)
{
	int ret = GPONMGR_FAIL;

#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

#ifdef TCSUPPORT_CPU_EN7521
																		/* uint cast is used to size alignment */
	ret = gponmgr_lib_ioctl(GPON_IOS_DBA_SLIGHT_MODIFY_YELLOW, (void *)((uint)yellow_size));
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to set o3 and o4 ploam control.
 Input Args:	total_size: used to set o3 and o4 ploam control.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_set_o3_o4_ploam_ctrl(GPON_SW_HW_SELECT_T sel)
{
	int ret = GPONMGR_FAIL;

#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

#ifdef TCSUPPORT_CPU_EN7521
	ret = gponmgr_lib_ioctl(GPON_IOS_O3_O4_PLOAM_CTRL, (void *)sel);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to set AES key switch by sw.
 Input Args:	none: 
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_test_aes_key_switch_by_sw(void)
{
	int ret = GPONMGR_FAIL;

#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

#ifdef TCSUPPORT_CPU_EN7521
	ret = gponmgr_lib_ioctl(GPON_IOS_AES_KEY_SWITCH_BY_SW, NULL);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to software reset GPON MAC exclude reg module.
 Input Args:	none: 
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_test_sw_reset(void)
{
	int ret = GPONMGR_FAIL;

#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

#ifdef TCSUPPORT_CPU_EN7521
	ret = gponmgr_lib_ioctl(GPON_IOS_SW_RESET, NULL);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to software resync.
 Input Args:	none: 
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_test_sw_resync(void)
{
	int ret = GPONMGR_FAIL;

#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

#ifdef TCSUPPORT_CPU_EN7521
	ret = gponmgr_lib_ioctl(GPON_IOS_SW_RESYNC, NULL);
#endif

	return ret;
}


/******************************************************************************
 Descriptor:	It's used to send ploam sleep request.
 Input Args:	mode: used to set sleep_request PLOAMu mode.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_test_send_ploam_sleep_request(GPON_PLOAMu_SLEEP_MODE_t mode)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOS_TEST_SEND_PLOAM_SLEEP_REQUEST, (void *)mode);
}

/******************************************************************************
 Descriptor:	It's used to send ploam rei.
 Input Args:	counter: REI PLOAMu error counter.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_test_send_ploam_rei(uint counter)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOS_TEST_SEND_PLOAM_REI, (void *)counter);
}

/******************************************************************************
 Descriptor:	It's used to send ploam Dying Gasp.
 Input Args:	none.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_test_send_ploam_dying_gasp(void)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOS_TEST_SEND_PLOAM_DYING_GASP, NULL);
}

/******************************************************************************
 Descriptor:	It's used to Tod function. 
                 The ToD interrupt will occur after newTime seconds.
 Input Args:	pmode: used to store dying gasp mode.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_test_tod(uint newTime)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOS_TEST_TOD, (void *)newTime);
}

/******************************************************************************
 Descriptor:	It's used to get the GPON MAC debug level.
 Input Args:	pgponDbgLevel: used to store GPON MAC debug level.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_dbg_level(ushort *pgponDbgLevel)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(IO_IOG_DBG_LEVEL, pgponDbgLevel);
}

/******************************************************************************
 Descriptor:	It's used to get gpon detail information.
 Input Args:	pgponOnuInfo: used to store GPON MAC info.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_info(struct XMCS_GponOnuInfo_S *pgponOnuInfo)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOG_ONU_INFO, pgponOnuInfo);
}

/******************************************************************************
 Descriptor:	It's used to get the GPON GEM port information.
 Input Args:	pgponGemInfo: used to store GPON GEM port information.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_gemport(struct XMCS_GemPortInfo_S *pgponGemInfo)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(IF_IOG_GEMPORT_INFO, pgponGemInfo);
}

/******************************************************************************
 Descriptor:	It's used to get the GPON GEM counter information.
 Input Args:	pgponGemCounter: used to store GPON GEM counter information.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_gemcounter(struct XMCS_GponGemCounter_S *pgponGemCounter)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOG_GEM_COUNTER, pgponGemCounter);
}

/******************************************************************************
 Descriptor:	It's used to get the ToD switch time.
 Input Args:	pgponTodCfg: used to store ToD.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_tod_switch_time(struct XMCS_GponTodCfg_S *pgponTodCfg)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOG_TOD_SWITCH_TIME, pgponTodCfg);
}

/******************************************************************************
 Descriptor:	It's used to get the current ToD.
 Input Args:	pgponTodCfg: used to store ToD.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_current_tod(struct XMCS_GponTodCfg_S *pgponTodCfg)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOG_CURRENT_TOD, pgponTodCfg);
}

/******************************************************************************
 Descriptor:	It's used to get the new ToD.
 Input Args:	pgponTodCfg: used to store ToD.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_new_tod(struct XMCS_GponTodCfg_S *pgponTodCfg)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOG_NEW_TOD, pgponTodCfg);
}

/******************************************************************************
 Descriptor:	It's used to get the GPON TCONT information.
 Input Args:	pgponTcontInfo: used to store tcont information.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_tcont(struct XMCS_TcontInfo_S *pgponTcontInfo)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(IF_IOG_TCONT_INFO, pgponTcontInfo);
}

/******************************************************************************
 Descriptor:	It's used to get the EqD detail information.
 Input Args:	pgponEqdOffset: used to store EqD detail information.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_eqd_offset(struct XMCS_EqdOffset_S *pgponEqdOffset)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOG_EQD_OFFSET, pgponEqdOffset);
}

/******************************************************************************
 Descriptor:	It's used to get GPON super frame counter.
 Input Args:	pspf: used to store super frame counter.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_super_frame_counter(uint *pspf)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOG_SUPER_FRAME_COUNTER, pspf);
}

/******************************************************************************
 Descriptor:	It's used to get GPON MAC counter type.
 Input Args:	ptype: used to store GPON MAC counter type.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_counter_type(GPON_COUNTER_TYPE_t *ptype)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOG_COUNTER_TYPE, ptype);
}

/******************************************************************************
 Descriptor:	It's used to get the GPON response time.
 Input Args:	time: used to store GPON MAC response time.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_response_time(ushort *time)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOG_RESPONSE_TIME, time);
}

/******************************************************************************
 Descriptor:	It's used to get GPON MAC internal delay fine tune(BFB64208[15:8]).
 Input Args:	delay: used to store GPON MAC internal delay fine tune.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_internal_delay_fine_tune(unchar *delay)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

																		/* uint cast is used to size alignment */
	return gponmgr_lib_ioctl(GPON_IOG_INTERNAL_DELAY_FINE_TUNE, (void *)((uint)delay));
}

/******************************************************************************
 Descriptor:	It's used to get the GPON MAC burst mode overhead supports more than 
                 128bytes status.
 Input Args:	ptype: used to store GPON_BURST_MODE_OVERHEAD_LEN_T.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_burst_mode_overhead(GPON_BURST_MODE_OVERHEAD_LEN_T *ptype)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOG_BURST_MODE_OVERHEAD_LEN, ptype);
}

/******************************************************************************
 Descriptor:	It's used to get the encryption key info.
 Input Args:	keyInfo: used to store GPON_DEV_ENCRYPT_KEY_INFO_T.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_key_info(GPON_DEV_ENCRYPT_KEY_INFO_T *keyInfo)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOG_ENCRYPT_KEY_INFO, keyInfo);
}

/******************************************************************************
 Descriptor:	It's used to get dba block size.
 Input Args:	pblockSize: used to store dba block size.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_dba_block_size(ushort *pblockSize)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOG_DBA_BLOCK_SIZE, pblockSize);
}

/******************************************************************************
 Descriptor:	It's used to get the GPON Dying Gasp mode.
 Input Args:	pmode: used to store dying gasp mode.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_dying_gasp_mode(GPON_SW_HW_SELECT_T *pmode)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOG_DYING_GASP_MODE, pmode);
}

/******************************************************************************
 Descriptor:	It's used to get the GPON Dying Gasp number.
 Input Args:	pmode: used to store dying gasp mode.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_dying_gasp_num(uint *pnum)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOG_DYING_GASP_NUM, pnum);
}

/******************************************************************************
 Descriptor:	It's used to get software upstream traffic enable or disable.
 Input Args:	pmode: used to store upstream traffic status.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_up_traffic(XPON_Mode_t *pmode)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOG_UP_TRAFFIC, pmode);
}

/******************************************************************************
 Descriptor:	It's used to get sniffer mode.
 Input Args:	sniffer: used to store sniffer mode.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_sniffer_gtc(GPON_DEV_SNIFFER_MODE_T *sniffer)
{
	int ret = GPONMGR_FAIL;
	
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

#ifdef TCSUPPORT_CPU_EN7521
	ret = gponmgr_lib_ioctl(GPON_IOG_SNIFFER_GTC, (void *)sniffer);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to show GPON control and status registers.
 Input Args:	none.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_csr(void)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return gponmgr_lib_ioctl(GPON_IOG_CSR, NULL);
}

/******************************************************************************
 Descriptor:	It's used to get status of filter extented burst length PLOAM at O5 state..
 Input Args:	enable: used to store enable status.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_ext_bst_len_ploamd_filter(XPON_Mode_t *enable)
{
	int ret = GPONMGR_FAIL;

#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif
	
#ifdef TCSUPPORT_CPU_EN7521
	return gponmgr_lib_ioctl(GPON_IOG_EXT_BST_LEN_PLOAMD_FILTER_IN_O5, (void *)enable);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to get status of filter Upstream Overhead PLOAM at O5 state.
 Input Args:	enable: used to store enable status.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_up_overhead_ploamd_filter(XPON_Mode_t *enable)
{
	int ret = GPONMGR_FAIL;

#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif
	
#ifdef TCSUPPORT_CPU_EN7521
	return gponmgr_lib_ioctl(GPON_IOG_UP_OVERHEAD_PLOAMD_FILTER_IN_O5, (void *)enable);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to get status of tx data length aligned multiple of 4.
 Input Args:	enable: used to store enable status.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_tx_4bytes_align(XPON_Mode_t *enable)
{
	int ret = GPONMGR_FAIL;

#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif
	
#ifdef TCSUPPORT_CPU_EN7521
	return gponmgr_lib_ioctl(GPON_IOG_TX_4BYTES_ALIGN, (void *)enable);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to get DBA backdoor configure.
 Input Args:	dba_backdoor: used to store DBA backdoor configure.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_dba_backdoor(GPON_DEV_DBA_BACKDOOR_T *dba_backdoor)
{
	int ret = GPONMGR_FAIL;

#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif
	
#ifdef TCSUPPORT_CPU_EN7521
	return gponmgr_lib_ioctl(GPON_IOG_DBA_BACKDOOR, (void *)dba_backdoor);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to get DBA slight modify configure.
 Input Args:	dba_backdoor: used to store DBA slight modify configure.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_dba_slight_modify(GPON_DEV_SLIGHT_MODIFY_T *dba_slight_modify)
{
	int ret = GPONMGR_FAIL;

#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif
	
#ifdef TCSUPPORT_CPU_EN7521
	return gponmgr_lib_ioctl(GPON_IOG_DBA_SLIGHT_MODIFY, (void *)dba_slight_modify);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to get o3 and o4 ploam control status.
 Input Args:	sel: used to store o3 and o4 ploam control status.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_o3_o4_ploam_ctrl(GPON_SW_HW_SELECT_T *sel)
{
	int ret = GPONMGR_FAIL;

#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif
	
#ifdef TCSUPPORT_CPU_EN7521
	return gponmgr_lib_ioctl(GPON_IOG_O3_O4_PLOAM_CTRL, (void *)sel);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to get tx sync status.
 Input Args:	sel: used to store tx sync status.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_tx_sync(unchar *tx_sync)
{
	int ret = GPONMGR_FAIL;

#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif
	
#ifdef TCSUPPORT_CPU_EN7521
	return gponmgr_lib_ioctl(GPON_IOG_TX_SYNC, (void *)tx_sync);
#endif

	return ret;
}

/******************************************************************************
 Descriptor:	It's used to get interrupt mask.
 Input Args:	mask: used to store tx interrupt mask.
 Ret Value:	success: GPONMGR_SUCCESS
                       fail: GPONMGR_FAIL
******************************************************************************/
int gponmgr_lib_get_int_mask(uint *mask)
{
#if API_LIB_GPONMGR_DBG
	printf("enter %s.\n", __func__);
#endif
	
	return gponmgr_lib_ioctl(GPON_IOG_INT_MASK, (void *)mask);
}

