/*********************************************************************
* LEGAL DISCLAIMER
*
* (Header of MediaTek Software/Firmware Release or Documentation)
*
* BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY 
* ACKNOWLEDGES AND AGREES THAT THE SOFTWARE/FIRMWARE AND ITS 
* DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED FROM MEDIATEK AND/OR 
* ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS ONLY. 
* MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR 
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF 
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR 
* NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY 
* WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH 
* MAY BE USED BY, INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK 
* SOFTWARE, AND BUYER AGREES TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY
* WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO NOT BE 
* RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S 
* SPECIFICATION OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
*
* BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND 
* CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED 
* HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE 
* MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR 
* SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE
* AT ISSUE.
*
* THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN 
* ACCORDANCE WITH THE LAWS OF THE STATE OF CALIFORNIA, USA, EXCLUDING
* ITS CONFLICT OF LAWS PRINCIPLES.
**********************************************************************
*/

/*
 *	File:	loader.h
 *	 
 *	Author: Peter.Jiang
 *	 		
 *	Last Revision Date: 2015.5.9
 *	 
 *	Description:
 *	VoIP drivers loader Constant and function prototypes. 
 *
 */

#ifndef _VOIP_LOADER_H_
#define _VOIP_LOADER_H_

#define INSMOD "/sbin/insmod"
#define RMMOD  "/sbin/rmmod"

#define M_SLIC3_CHECK "/lib/modules/slic3_check.ko"
#define PROC_SLIC3_CHECK "/proc/slic/check"

#define M_SYS_MOD "/lib/modules/sys_mod.ko"
#define M_PCM "/lib/modules/pcm.ko"
#define M_LEC "/lib/modules/lec.ko"
#define M_SLIC3 "/lib/modules/slic3.ko"
#define M_FXS3 "/lib/modules/fxs3.ko"
#define M_KSOCKET "/lib/modules/ksocket.ko"
#define M_ORTP "/lib/modules/ortp.ko"
#define M_ACODEC_X "/lib/modules/acodec_x.ko"
#define M_FOIP "/lib/modules/foip.ko"
#define M_OVDSP "/lib/modules/ovdsp.ko"
#define M_PCMDUMP "/lib/modules/pcmDump.ko"

#define M_PCM_SILICON "/lib/modules/pcm_silicon.ko"
#define M_SLIC3_SILICON "/lib/modules/slic3_silicon.ko"
#define M_FXS3_SILICON "/lib/modules/fxs3_silicon.ko"

#define SLIC_TYPE_ZL88601 "zl88601"
#define SLIC_TYPE_LE89156 "le89156"
#define SLIC_TYPE_LE89316 "le89316"
#define SLIC_TYPE_LE9641  "le9641"

#define SLIC_TYPE_SI32176 "si32176"
#define SLIC_TYPE_SI32260 "si32260"

#define ABNORMAL_CHECK(_c_) if ((_c_)!=0) {printf ("system failed at %d(%d:%s)\n", __LINE__, (_c_),strerror(errno)); }

#define OUT
#define IN
#define INOUT

#define SLIC_TYPE_LEN_MAX 32

#define LOADER_SUCCESS 0
#define LOADER_FAILED  -1

typedef enum 
{
    SLIC_CLASS_ZARLINK = 1,
    SLIC_CLASS_SILICON = 2,
}slic_class_e;

int get_slic_type (int slic_class, OUT char *slic_type, int size);
int load_zl88601 ();
int load_le89156 ();
int load_le89316 ();
int load_le9641 ();

int check_zarlink(IN char *slic_type);

int load_si32176 ();
int load_si32260 ();

int check_silicon(IN char *slic_type);

#endif /* End of _VOIP_EVCOM_H_ */

