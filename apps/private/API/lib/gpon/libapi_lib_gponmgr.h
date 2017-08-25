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
#ifndef _API_LIB_GPONMGR_H
#define _API_LIB_GPONMGR_H

/************************************************************************
*                  D A T A	 T Y P E S
************************************************************************/
typedef unsigned char			unchar;
typedef unsigned short			ushort;
typedef unsigned int			uint;
typedef unsigned long			ulong;

/************************************************************************
*                  I N C L U D E S
************************************************************************/
#include <common/drv_debug.h>
#include <xmcs/xmcs_gpon.h>
#include <xmcs/xmcs_if.h>
#include <gpon/gpon_const.h>
#include <gpon/gpon_dev.h>
#include <gpon/gpon_ploam.h>

/************************************************************************
*                  D E F I N E S   &   C O N S T A N T S
************************************************************************/
#define GPONMGR_SUCCESS	(0)
#define GPONMGR_FAIL	(-1)
#define GPONMGR_ENABLE	(1)
#define GPONMGR_DISABLE	(0)

/************************************************************************
*                  M A C R O S
************************************************************************/

/************************************************************************
*                  E X T E R N A L	 D A T A   D E C L A R A T I O N S
************************************************************************/

/************************************************************************
*                  F U N C T I O N   D E F I N I T I O N S
************************************************************************/
/* set */
int gponmgr_lib_set_dbg_level_act(XPON_Mode_t enable);
int gponmgr_lib_set_dbg_level_omci(XPON_Mode_t enable);
int gponmgr_lib_set_dbg_level_oam(XPON_Mode_t enable);
int gponmgr_lib_set_dbg_level_int(XPON_Mode_t enable);
int gponmgr_lib_set_dbg_level_trace(XPON_Mode_t enable);
int gponmgr_lib_set_dbg_level_warning(XPON_Mode_t enable);
int gponmgr_lib_set_dbg_level_content(XPON_Mode_t enable);
int gponmgr_lib_set_dbg_level_debug(XPON_Mode_t enable);
int gponmgr_lib_set_dbg_level_err(XPON_Mode_t enable);
int gponmgr_lib_set_eqd_offset_o4(unchar gponEqdO4Offset);
int gponmgr_lib_set_eqd_offset_o5(unchar gponEqdO5Offset);
int gponmgr_lib_set_eqd_offset_flag(char gponEqdOffsetflag);
int gponmgr_lib_set_counter_type(GPON_COUNTER_TYPE_t type);
int gponmgr_lib_set_response_time(ushort time);
int gponmgr_lib_set_internal_delay_fine_tune(unchar delay);
int gponmgr_lib_set_burst_mode_overhead(GPON_BURST_MODE_OVERHEAD_LEN_T type);
int gponmgr_lib_set_clear_counter(GPON_SW_HW_SELECT_T clear);
int gponmgr_lib_set_sn(char *psn);
int gponmgr_lib_set_passwd(char *ppasswd);
int gponmgr_lib_set_key_switch_time(uint spf);
int gponmgr_lib_set_encrypt_key(unchar *pkey);
int gponmgr_lib_set_tod_switch_time(struct XMCS_GponTodCfg_S *pgponTodCfg);
int gponmgr_lib_set_tod_new_time(struct XMCS_GponTodCfg_S *pgponTodCfg);
int gponmgr_lib_set_act_timer_to1(uint to1Timer);
int gponmgr_lib_set_act_timer_to2(uint to2Timer);
int gponmgr_lib_set_dba_block_size(ushort blockSize);
int gponmgr_lib_set_dying_gasp_mode(GPON_SW_HW_SELECT_T mode);
int gponmgr_lib_set_dying_gasp_num(uint num);
int gponmgr_lib_set_up_traffic(XPON_Mode_t mode);
int gponmgr_lib_set_sniffer_gtc(GPON_DEV_SNIFFER_MODE_T *sniffer);
int gponmgr_lib_set_ext_bst_len_ploamd_filter(XPON_Mode_t enable);
int gponmgr_lib_set_up_overhead_ploamd_filter(XPON_Mode_t enable);
int gponmgr_lib_set_tx_4bytes_align(XPON_Mode_t enable);
int gponmgr_lib_set_dba_backdoor(XPON_Mode_t enable);
int gponmgr_lib_set_dba_backdoor_total(uint total_size);
int gponmgr_lib_set_dba_backdoor_green(uint green_size);
int gponmgr_lib_set_dba_backdoor_yellow(uint yellow_size);
int gponmgr_lib_set_dba_slight_modify(XPON_Mode_t enable);
int gponmgr_lib_set_dba_slight_modify_total(ushort total_size);
int gponmgr_lib_set_dba_slight_modify_green(ushort green_size);
int gponmgr_lib_set_dba_slight_modify_yellow(ushort yellow_size);
int gponmgr_lib_set_dba_backdoor(XPON_Mode_t enable);
int gponmgr_lib_set_dba_backdoor_total(uint total_size);
int gponmgr_lib_set_dba_backdoor_green(uint green_size);
int gponmgr_lib_set_dba_backdoor_yellow(uint yellow_size);
int gponmgr_lib_set_o3_o4_ploam_ctrl(GPON_SW_HW_SELECT_T sel);
int gponmgr_lib_test_aes_key_switch_by_sw(void);
int gponmgr_lib_test_sw_reset(void);
int gponmgr_lib_test_send_ploam_sleep_request(GPON_PLOAMu_SLEEP_MODE_t mode);
int gponmgr_lib_test_send_ploam_rei(uint counter);
int gponmgr_lib_test_send_ploam_dying_gasp(void);
int gponmgr_lib_test_tod(uint newTime);
/* get */
int gponmgr_lib_get_dbg_level(ushort *pgponDbgLevel);
int gponmgr_lib_get_info(struct XMCS_GponOnuInfo_S *gponOnuInfo);
int gponmgr_lib_get_gemport(struct XMCS_GemPortInfo_S *pgponGemInfo);
int gponmgr_lib_get_gemcounter(struct XMCS_GponGemCounter_S *pgponGemCounter);
int gponmgr_lib_get_tod_switch_time(struct XMCS_GponTodCfg_S *pgponTodCfg);
int gponmgr_lib_get_current_tod(struct XMCS_GponTodCfg_S *pgponTodCfg);
int gponmgr_lib_get_new_tod(struct XMCS_GponTodCfg_S *pgponTodCfg);
int gponmgr_lib_get_tcont(struct XMCS_TcontInfo_S *pgponTcontInfo);
int gponmgr_lib_get_eqd_offset(struct XMCS_EqdOffset_S *pgponEqdOffset);
int gponmgr_lib_get_super_frame_counter(uint *pspf);
int gponmgr_lib_get_counter_type(GPON_COUNTER_TYPE_t *ptype);
int gponmgr_lib_get_response_time(ushort *time);
int gponmgr_lib_get_internal_delay_fine_tune(unchar *delay);
int gponmgr_lib_get_burst_mode_overhead(GPON_BURST_MODE_OVERHEAD_LEN_T *type);
int gponmgr_lib_get_key_info(GPON_DEV_ENCRYPT_KEY_INFO_T *keyInfo);
int gponmgr_lib_get_dba_block_size(ushort *pblockSize);
int gponmgr_lib_get_dying_gasp_mode(GPON_SW_HW_SELECT_T *mode);
int gponmgr_lib_get_dying_gasp_num(uint *num);
int gponmgr_lib_get_up_traffic(XPON_Mode_t *pmode);
int gponmgr_lib_get_sniffer_gtc(GPON_DEV_SNIFFER_MODE_T *sniffer);
int gponmgr_lib_get_csr(void);
int gponmgr_lib_get_ext_bst_len_ploamd_filter(XPON_Mode_t *enable);
int gponmgr_lib_get_up_overhead_ploamd_filter(XPON_Mode_t *enable);
int gponmgr_lib_get_tx_4bytes_align(XPON_Mode_t *enable);
int gponmgr_lib_get_dba_backdoor(GPON_DEV_DBA_BACKDOOR_T *dba_backdoor);
int gponmgr_lib_get_dba_slight_modify(GPON_DEV_SLIGHT_MODIFY_T *dba_slight_modify);
int gponmgr_lib_get_o3_o4_ploam_ctrl(GPON_SW_HW_SELECT_T *sel);
int gponmgr_lib_get_tx_sync(unchar *tx_sync);
int gponmgr_lib_get_int_mask(uint *mask);

/************************************************************************
*                  P U B L I C   D A T A
************************************************************************/

/************************************************************************
*                  P R I V A T E   D A T A
************************************************************************/

/************************************************************************
*                  F U N C T I O N   D E C L A R A T I O N S
************************************************************************/

#endif
