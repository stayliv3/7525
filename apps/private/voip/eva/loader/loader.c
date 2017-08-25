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
 *	File:	loader.c
 *	 
 *	Author: Peter Jiang
 *	 		
 *	Last Revision Date: 2015.5.9
 *	 
 *	Description:
 *	load voip drivers according to real slic type (zarlink, silicon..)
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "loader.h"

//#undef printf
//#define printf tcdbg_printf

int get_slic_type (int slic_class, OUT char *slic_type, int size)
{
    int ret = 0;
    char *rtn_p;
    FILE *fp = NULL;
    int count = 0;
    char type[SLIC_TYPE_LEN_MAX] = {0};
	char cmd[128] = {0};
    int len = size > SLIC_TYPE_LEN_MAX ? SLIC_TYPE_LEN_MAX : size;

	printf ("get slic type by %d\n", slic_class);
    /*load slic3_check.ko for slic checking*/
    if (SLIC_CLASS_ZARLINK == slic_class)
    {
        snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_SYS_MOD);
		ret = system (cmd);
        ABNORMAL_CHECK (ret);

        snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_PCM);
        ret |= system (cmd);
        ABNORMAL_CHECK (ret);

        snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_SLIC3_CHECK);
        ret |= system (cmd);
        ABNORMAL_CHECK (ret);
    }
    else if (SLIC_CLASS_SILICON == slic_class)
    {
        snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_SYS_MOD);
        ret |= system (cmd);
        ABNORMAL_CHECK (ret);

        snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_PCM_SILICON);
        ret |= system (cmd);
        ABNORMAL_CHECK (ret);

        snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_SLIC3_CHECK);
        ret |= system (cmd);
        ABNORMAL_CHECK (ret);

    }
    else
    {
        printf ("unknown slic class in loading!\n");
        return LOADER_FAILED;
    }

    if (ret != 0)
    {
        printf ("loading drivers failed!\n");
        return LOADER_FAILED;
    }

    /*open PROC_SLIC3_CHECK in write-only mode, write into "zarlink"*/
    fp = fopen (PROC_SLIC3_CHECK, "w");
    if (fp == NULL) 
    {
        printf ("Can not open file %s\n", PROC_SLIC3_CHECK);
        return LOADER_FAILED;
    }

    if (SLIC_CLASS_ZARLINK == slic_class)
        count = fputs("zarlink\n", fp);
    else if (SLIC_CLASS_SILICON == slic_class)
        count = fputs("silicon\n", fp);
    else
    {
        printf ("unknown slic class in checking!\n");
        return LOADER_FAILED;
    }
	printf ("count %d\n", count);

    if (count <= 0)
    {
        printf ("Write to file %s failed!\n", PROC_SLIC3_CHECK);
        return LOADER_FAILED;
    }

    fflush (fp);
    fclose(fp);

    /*open PROC_SLIC3_CHECK in read-only mode, get result*/
    fp = fopen (PROC_SLIC3_CHECK, "r");
    if (fp == NULL) 
    {
        printf ("Can not open file %s\n", PROC_SLIC3_CHECK);
        return LOADER_FAILED;
    }

    rtn_p = fgets (type, sizeof(type), fp);
    if (rtn_p == NULL)
    {
        printf ("Read from file %s failed!\n", PROC_SLIC3_CHECK);
        return LOADER_FAILED;
    }
    printf ("%s\n", type);
    fclose(fp);

    strncpy (slic_type, type, len);

    /*unload slic3_check.ko after slic checking*/
    if (SLIC_CLASS_ZARLINK == slic_class)
    { 
        snprintf (cmd, sizeof(cmd), "%s %s", RMMOD, M_SLIC3_CHECK);
		ret = system (cmd);
        ABNORMAL_CHECK (ret);

        snprintf (cmd, sizeof(cmd), "%s %s", RMMOD, M_PCM);
        ret |= system (cmd);
        ABNORMAL_CHECK (ret);

        snprintf (cmd, sizeof(cmd), "%s %s", RMMOD, M_SYS_MOD);
        ret |= system (cmd);
        ABNORMAL_CHECK (ret);

    }
    else if (SLIC_CLASS_SILICON == slic_class)
    {
        snprintf (cmd, sizeof(cmd), "%s %s", RMMOD, M_SLIC3_CHECK);
        ret = system (cmd);
        ABNORMAL_CHECK (ret);

        snprintf (cmd, sizeof(cmd), "%s %s", RMMOD, M_PCM_SILICON);
        ret |= system (cmd);
        ABNORMAL_CHECK (ret);

        snprintf (cmd, sizeof(cmd), "%s %s", RMMOD, M_SYS_MOD);
        ret |= system (cmd);
        ABNORMAL_CHECK (ret);

    }
    else
    {
        printf ("unknown slic class in unloading!\n");
        return LOADER_FAILED;
    }

    return LOADER_SUCCESS;
}

int check_zarlink(IN char* slic_type)
{
    int ret = 0;

    if (strstr (slic_type, SLIC_TYPE_ZL88601))
        ret = load_zl88601 ();
    else if (strstr (slic_type, SLIC_TYPE_LE89156))
        ret = load_le89156 ();
    else if (strstr (slic_type, SLIC_TYPE_LE89316))
        ret = load_le89316 ();
    else if (strstr (slic_type, SLIC_TYPE_LE9641))
        ret = load_le9641 ();
    else
    {
        printf ("unknown slic type %s\n", slic_type);
        ret = LOADER_FAILED;
    }

    return ret;
}

int check_silicon(IN char *slic_type)
{
    int ret = 0;

    if (strstr (slic_type, SLIC_TYPE_SI32176))
        ret = load_si32176 ();
    else if (strstr (slic_type, SLIC_TYPE_SI32260))
        ret = load_si32260 ();
    else
    {
        printf ("unknown slic type %s\n", slic_type);
        ret = LOADER_FAILED;
    }

    return ret;
}

static int load_common ()
{
    int ret = 0;
    char cmd[128] = {0};

	printf ("Loading common\n");

    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_KSOCKET);
    ret = system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_ORTP);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_ACODEC_X);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_FOIP);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_OVDSP);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_PCMDUMP);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);

    if (ret == 0)
    	return LOADER_SUCCESS;
    else
        return LOADER_FAILED;
}

int load_zl88601 ()
{
    int ret = 0;
    char cmd[128] = {0};

    printf ("Loading zl88601\n");

    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_SYS_MOD);
    ret = system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_PCM);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_LEC);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_SLIC3);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s slic1=zl88601 slic2=zl88601", INSMOD, M_FXS3);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);

    ret |= load_common ();    
    ABNORMAL_CHECK (ret);

    if (ret == 0)
    	return LOADER_SUCCESS;
    else
        return LOADER_FAILED;

}

int load_le89156 ()
{
    int ret = 0;
    char cmd[128] = {0};
    printf ("Loading le89156\n");

    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_SYS_MOD);
    ret = system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_PCM);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_LEC);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_SLIC3);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s slic1=le89156", INSMOD, M_FXS3);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);

    ret |= load_common ();    
    ABNORMAL_CHECK (ret);

    if (ret == 0)
    	return LOADER_SUCCESS;
    else
        return LOADER_FAILED;

}

int load_le89316 ()
{
    int ret = 0;
    printf ("Loading le89316\n");

    return LOADER_SUCCESS;
}

int load_le9641 ()
{
    int ret = 0;
    char cmd[128] = {0};

    printf ("Loading le9641\n");

    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_SYS_MOD);
    ret = system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_PCM);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_LEC);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_SLIC3);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s slic1=le9641", INSMOD, M_FXS3);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);

    ret |= load_common ();    
    ABNORMAL_CHECK (ret);

    if (ret == 0)
    	return LOADER_SUCCESS;
    else
        return LOADER_FAILED;

}

int load_si32176 ()
{
    int ret = 0;
    char cmd[128] = {0};
    printf ("Loading si32176\n");

    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_SYS_MOD);
    ret = system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_PCM_SILICON);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_LEC);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_SLIC3_SILICON);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s slic1=si32176", INSMOD, M_FXS3_SILICON);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);

    ret |= load_common ();    
    ABNORMAL_CHECK (ret);

    if (ret == 0)
    	return LOADER_SUCCESS;
    else
        return LOADER_FAILED;

}

int load_si32260 ()
{
    int ret = 0;
    char cmd[128] = {0};
    printf ("Loading si32260\n");

    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_SYS_MOD);
    ret = system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_PCM_SILICON);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_LEC);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s", INSMOD, M_SLIC3_SILICON);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);
    snprintf (cmd, sizeof(cmd), "%s %s slic1=si32260 slic2=si32260", INSMOD, M_FXS3_SILICON);
    ret |= system (cmd);
    ABNORMAL_CHECK (ret);

    ret |= load_common ();    
    ABNORMAL_CHECK (ret);

    if (ret == 0)
    	return LOADER_SUCCESS;
    else
        return LOADER_FAILED;

}



int main (int argc, char *argv[])
{
    int ret = 0;
    char slic_type[SLIC_TYPE_LEN_MAX] = {0};
    char cmd[128] = {0};

    /*check zarlink class slic*/
    printf ("checking zarlink...\n");
    ret = get_slic_type (SLIC_CLASS_ZARLINK, slic_type, SLIC_TYPE_LEN_MAX);
 
    if (LOADER_SUCCESS == ret) {
        printf ("[zarlink] %s\n", slic_type);
        ret = check_zarlink (slic_type);

        if (LOADER_SUCCESS == ret)
            return ret;
        }
        else 
        {
            snprintf (cmd, sizeof(cmd), "%s %s", RMMOD, M_SLIC3_CHECK);
            system (cmd);
		
            snprintf (cmd, sizeof(cmd), "%s %s", RMMOD, M_PCM);
            system (cmd);
		
            snprintf (cmd, sizeof(cmd), "%s %s", RMMOD, M_SYS_MOD);
            system (cmd);
	}

    /*check silicon class slic*/
    printf ("checking silicon...\n");
    memset (slic_type, 0, sizeof(slic_type));
    ret = get_slic_type (SLIC_CLASS_SILICON, slic_type, SLIC_TYPE_LEN_MAX);
  
    if (LOADER_SUCCESS == ret) 
    {
        printf ("[silicon] %s\n", slic_type);
        ret = check_silicon (slic_type);
    }
    else
    {
        snprintf (cmd, sizeof(cmd), "%s %s", RMMOD, M_SLIC3_CHECK);
        system (cmd);

        snprintf (cmd, sizeof(cmd), "%s %s", RMMOD, M_PCM_SILICON);
        system (cmd);

        snprintf (cmd, sizeof(cmd), "%s %s", RMMOD, M_SYS_MOD);
        system (cmd);

    }
    return ret;
}

