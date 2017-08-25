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

#include "libapi_lib_qdmamgr.h"


/************************************************************************
*                  D E F I N E S   &   C O N S T A N T S
************************************************************************/
	
#define QDMA_MAGIC							(0xAB)
	
/* Interface IO Command */
#define IO_QDMA_SET_QOS_CONFIG				_IOW(QDMA_MAGIC, 0x01, struct ECNT_QDMA_Data *)
#define IO_QDMA_GET_QOS_CONFIG				_IOR(QDMA_MAGIC, 0x01, struct ECNT_QDMA_Data *)
#define IO_QDMA_SET_TX_RATELIMIT			_IOW(QDMA_MAGIC, 0x02, struct ECNT_QDMA_Data *)
#define IO_QDMA_GET_TX_RATELIMIT			_IOR(QDMA_MAGIC, 0x02, struct ECNT_QDMA_Data *)

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
 Descriptor:	It's used to ioctl to qdma device.
 Input Args:	cmd: ioctl command.
                     p: pointer to qdma driver structure, it is used to 
 Ret Value:	success: QDMAMGR_SUCCESS
                       fail: QDMAMGR_FAIL
******************************************************************************/
static int qdmamgr_lib_ioctl(int cmd, void *p)
{
	int fd, ret;
	
	fd = open(qdma_path, O_RDWR);
    if (fd < 0) {
		printf("Open %s pseudo device failed\n", qdma_path);
		return QDMAMGR_FAIL;
    }

	ret = ioctl(fd, cmd, p);
	close(fd);

	if(ret >= 0) {
		return QDMAMGR_SUCCESS;
	} else {
		return QDMAMGR_FAIL;
	}
}

/******************************************************************************
 Descriptor:	It's used to set the QDMA qos config.
 Input Args:	weightBase & weightScale.
 Ret Value:	success: QDMAMGR_SUCCESS
                     fail: QDMAMGR_FAIL
******************************************************************************/
#if 0
int qdmamgr_lib_set_qos_config(QDMA_TxQosWeightType_t weightBase, QDMA_TxQosWeightScale_t weightScale)
{
	struct ECNT_QDMA_Data qdma_data;
	
#if API_LIB_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	qdma_data.qdma_private.qdma_tx_qos.weightBase = weightBase;
	qdma_data.qdma_private.qdma_tx_qos.weightScale = weightScale;

	return qdmamgr_lib_ioctl(IO_QDMA_SET_QOS_CONFIG, &qdma_data);
}
#else
int qdmamgr_lib_set_qos_config(uint weightBase, uint weightScale)
{	
#if API_LIB_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return qdmamgr_lib_ioctl(IO_QDMA_SET_QOS_CONFIG, NULL);
}

#endif

int qdmamgr_lib_set_tx_ratelimit(uint weightBase, uint weightScale)
{	
#if API_LIB_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	return qdmamgr_lib_ioctl(IO_QDMA_SET_TX_RATELIMIT, NULL);
}

/******************************************************************************
 Descriptor:	It's used to set the QDMA qos config.
 Input Args:	weightBase & weightScale.
 Ret Value: success: QDMAMGR_SUCCESS
					 fail: QDMAMGR_FAIL
******************************************************************************/
#if 0
int qdmamgr_lib_get_qos_config(QDMA_TxQosWeightType_t *pWeightBase, QDMA_TxQosWeightScale_t *pWeightScale)
{
	struct ECNT_QDMA_Data qdma_data;
	int ret = 0 ;
	
#if API_LIB_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif

	ret = qdmamgr_lib_ioctl(IO_QDMA_GET_QOS_CONFIG, &qdma_data);

	*pWeightBase = qdma_data.qdma_private.qdma_tx_qos.weightBase;
	*pWeightScale = qdma_data.qdma_private.qdma_tx_qos.weightScale;

	return ret;
}
#else
int qdmamgr_lib_get_qos_config(uint *pWeightBase, uint *pWeightScale)
{
	int ret = 0 ;	
#if API_LIB_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif
	ret = qdmamgr_lib_ioctl(IO_QDMA_GET_QOS_CONFIG, NULL);
	return ret;
}
#endif

int qdmamgr_lib_get_tx_ratelimit(uint *pWeightBase, uint *pWeightScale)
{
	int ret = 0 ;	
#if API_LIB_QDMAMGR_DBG
	printf("enter %s.\n", __func__);
#endif
	ret = qdmamgr_lib_ioctl(IO_QDMA_GET_TX_RATELIMIT, NULL);
	return ret;
}

